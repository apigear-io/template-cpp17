
#include "Poco/Net/WebSocket.h"

#include "private/olinkremote.h"
#include "private/requesthandlerfactory.h"
#include "private/iconnectionstorage.h"

#include "olink/remotenode.h"
#include "olink/remoteregistry.h"
#include "utilities/logger.h"
#include "utilities/threadpool.h"

#include <iostream>

namespace{
    // when more than one thread is used per connection,
    // the order of messages(e.g. property set) is not guaranteed
    const size_t workerThreadsPerConnection = 1;
}

namespace ApiGear {
namespace PocoImpl {

OLinkRemote::OLinkRemote(std::unique_ptr<Poco::Net::WebSocket> socket,
                        IConnectionStorage& connectionStorage,
                        ApiGear::ObjectLink::RemoteRegistry& registry,
                        const ApiGear::ObjectLink::WriteLogFunc& logFunc)
    : m_socket(*this, false),
     m_connectionStorage(connectionStorage),
     m_node(ApiGear::ObjectLink::RemoteNode::createRemoteNode(registry))
{
    pool = std::make_unique<ApiGear::Utilities::ThreadPool>(workerThreadsPerConnection);
    m_node->onLog(logFunc);
    m_node->onWrite([this](const std::string& msg) {
        m_socket.writeMessageWithQueue(msg);
    });
    m_socket.changeSocket(std::move(socket));
}

OLinkRemote::~OLinkRemote()
{
    if(!m_socket.isClosed())
    {
        m_socket.close();
    }
}

void OLinkRemote::handleTextMessage(const std::string& msg)
{
    AG_LOG_DEBUG("handleTextMessage " + msg);
    if (m_node)
    {
        pool->enqueue([this, msg] {
            m_node->handleMessage(msg);
        });
    }
}

void OLinkRemote::onConnectionClosedFromNetwork()
{
    m_connectionStorage.notifyConnectionClosed();
}

bool OLinkRemote::isClosed() const
{
    return m_socket.isClosed();
}

}}  //namespace ApiGear::PocoImpl
