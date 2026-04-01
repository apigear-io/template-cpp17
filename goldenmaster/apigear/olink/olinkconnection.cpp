#include <Poco/Util/TimerTaskAdapter.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/WebSocket.h>

#include "olinkconnection.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include "olink/clientregistry.h"
#include "olink/iobjectsink.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
#include "utilities/logger.h"
#include "utilities/threadpool.h"

#include <memory>
#include <vector>

using namespace ApiGear::PocoImpl;

namespace{
    const std::string jsonContentType = "application/json";
    const std::string defaultGatewayUrl = "ws://localhost:8000/ws";
    // when more than one thread is used per connection,
    // the order of messages(e.g. property set) is not guaranteed
    const size_t workerThreadsPerConnection = 1;

    long tryReconnectDelay = 500; //Milliseconds
    long repeatTaskInterval = 10000; //Milliseconds
    bool sendPing = false;
}

OlinkConnection::OlinkConnection(ApiGear::ObjectLink::ClientRegistry& registry)
    : m_node(ApiGear::ObjectLink::ClientNode::create(registry)),
    m_socket(*this, sendPing),
    m_isConnecting(false)
{
    pool = std::make_unique<ApiGear::Utilities::ThreadPool>(workerThreadsPerConnection);
    auto writeFunction = [this](const auto& msg) {
        m_socket.writeMessageWithQueue(msg);
    };
    m_node->onWrite(writeFunction);
}

void OlinkConnection::onConnectionClosedFromNetwork()
{
    onDisconnected();
    std::unique_lock<std::mutex> lock(m_reconnectMutex);
    if (m_reconnectTask) {
        m_reconnectTask->cancel();
    }
    // Poco::Util::Timer takes ownership via TimerTask::Ptr (AutoPtr).
    m_reconnectTask = new Poco::Util::TimerTaskAdapter<OlinkConnection>(*this, &OlinkConnection::reconnect);
    lock.unlock();

    m_reconnectTimer.schedule(m_reconnectTask, tryReconnectDelay, repeatTaskInterval);
}

void OlinkConnection::onNotifyNoSocket(){
    std::unique_lock<std::mutex> lock(m_reconnectMutex);
    if (m_reconnectTask) {
        m_reconnectTask->cancel();
    }
    // Poco::Util::Timer takes ownership via TimerTask::Ptr (AutoPtr).
    m_reconnectTask = new Poco::Util::TimerTaskAdapter<OlinkConnection>(*this, &OlinkConnection::reconnect);
    lock.unlock();
    // This function is called by socket wrapper, therefore to allow it to finish its function, and to be proceed properly
    // The  re-connecting is scheduled in 1ms, so it is executed outside this call.
    long startTaskDelayMilliseconds = 1;
    m_reconnectTimer.schedule(m_reconnectTask, startTaskDelayMilliseconds, repeatTaskInterval);
}

OlinkConnection::~OlinkConnection()
{
    // Copy under lock, then iterate outside — disconnectAndUnlink may do network I/O.
    decltype(m_objectLinkStatus) copyObjectLinkStatus;
    {
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        copyObjectLinkStatus = m_objectLinkStatus;
    }
    for(auto& object : copyObjectLinkStatus){
        disconnectAndUnlink(object.first);
    }
    if (!m_socket.isClosed()){
        m_socket.close();
    }
    onDisconnected();
}

void OlinkConnection::connectAndLinkObject(std::shared_ptr<ApiGear::ObjectLink::IObjectSink> object)
{
    if (!object){
        AG_LOG_WARNING("could not link an object, because it is not valid");
        return;
    }

    m_node->registry().addSink(object);
    if (!m_socket.isClosed()){
        m_node->linkRemote(object->olinkObjectName());
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        m_objectLinkStatus[object->olinkObjectName()] = LinkStatus::Linked;
    }
    else
    {
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        m_objectLinkStatus[object->olinkObjectName()] = LinkStatus::NotLinked;
    }
}

void OlinkConnection::disconnectAndUnlink(const std::string& objectId)
{
    bool shouldUnlink = false;
    {
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        auto objectStatus = m_objectLinkStatus.find(objectId);
        if (objectStatus != m_objectLinkStatus.end()) {
            shouldUnlink = (objectStatus->second != LinkStatus::NotLinked);
            m_objectLinkStatus.erase(objectStatus);
        }
    }
    if (shouldUnlink) {
        m_node->unlinkRemote(objectId);
    }
    m_node->registry().removeSink(objectId);
}

void OlinkConnection::connectToHost(Poco::URI url)
{
    if(url.empty()) {
        m_serverUrl = Poco::URI(defaultGatewayUrl);
        AG_LOG_DEBUG("No host url provided");
    } else {
        m_serverUrl = url;
    }
    
    if(m_socket.isClosed() && !m_isConnecting) {
        AG_LOG_INFO("Connecting to host " + url.toString());
        try {
            m_isConnecting = true;
            Poco::Net::HTTPClientSession session(m_serverUrl.getHost(), m_serverUrl.getPort());
            Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/ws", Poco::Net::HTTPMessage::HTTP_1_1);
            request.setKeepAlive(true);
            request.setContentType(jsonContentType);
            Poco::Net::HTTPResponse response;
            auto socket = std::make_unique<Poco::Net::WebSocket>(session, request, response);
            m_socket.changeSocket(std::move(socket));
            onConnected();

        } catch (std::exception &e) {
            m_socket.close();
            AG_LOG_ERROR("Exception " + std::string(e.what()));
        }
        m_isConnecting = false;
    }
}

void OlinkConnection::disconnect() {
    AG_LOG_DEBUG("request to disconnect socket");
    if (m_reconnectTask) {
        m_reconnectTask->cancel();
    }
    // Collect objects to unlink under lock, then unlink outside lock (may do network I/O).
    std::vector<std::string> objectsToUnlink;
    {
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        for (const auto& object : m_objectLinkStatus){
            if (object.second != LinkStatus::NotLinked){
                objectsToUnlink.push_back(object.first);
            }
        }
    }
    for (const auto& objectId : objectsToUnlink){
        m_node->unlinkRemote(objectId);
    }

    m_socket.close();
    onDisconnected();
}

std::shared_ptr<ApiGear::ObjectLink::ClientNode> OlinkConnection::node()
{
    return m_node;
}

void OlinkConnection::onConnected()
{
    AG_LOG_INFO("socket connected");
    // Collect object names under lock, then link outside (may do network I/O).
    std::vector<std::string> objectNames;
    {
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        objectNames.reserve(m_objectLinkStatus.size());
        for (const auto& object : m_objectLinkStatus)
        {
            objectNames.push_back(object.first);
        }
    }
    for (const auto& name : objectNames)
    {
        m_node->linkRemote(name);
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        m_objectLinkStatus[name] = LinkStatus::Linked;
    }
}

void OlinkConnection::onDisconnected()
{
    {
        std::lock_guard<std::mutex> lock(m_objectLinkStatusMutex);
        for (auto& object : m_objectLinkStatus)
        {
            object.second = LinkStatus::NotLinked;
        }
    }
    AG_LOG_INFO("socket disconnected");
}

void OlinkConnection::handleTextMessage(const std::string &message)
{
    pool->enqueue([this, message] {
        m_node->handleMessage(message);
    });
}

void OlinkConnection::reconnect(Poco::Util::TimerTask& /*task*/)
{
    connectToHost(m_serverUrl);
}
