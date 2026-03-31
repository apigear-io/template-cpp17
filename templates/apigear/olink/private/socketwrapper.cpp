#include "private/socketwrapper.h"
#include "private/isocketuser.h"
#include "utilities/logger.h"

#include <Poco/Util/TimerTaskAdapter.h>
#include <Poco/Net/WebSocket.h>
#include "Poco/Buffer.h"
#include "Poco/Exception.h"

#include <iostream>

namespace
{
    const std::string closeFramePayload = "bye";
    const std::string pingFramePayload = "ping";
    long retryInterval = 500; //Milliseconds
    long smallDelay = 7; //Milliseconds
    uint32_t messagesToSendAtOnce = 400;
}


namespace ApiGear {
namespace PocoImpl {

SocketWrapper::SocketWrapper(ISocketUser& socketUser, bool sendPing)
    : m_socketUser(socketUser),
    m_addPingMessage(sendPing),
    m_disconnectRequested(false)
{
}

SocketWrapper::~SocketWrapper()
{
    close();
}

void SocketWrapper::startReceiving()
{
    auto closedFromNetwork = false;
    do{
        try {
            // receiveFrame requires pocobuffer with initial size 0, as it always extends it with adding frame content.
            Poco::Buffer<char> pocobuffer(0);
            int flags;
            auto canSocketRead = m_socket ? m_socket->poll(Poco::Timespan(10000), Poco::Net::WebSocket::SELECT_READ) : false;
            if (canSocketRead && !m_disconnectRequested && m_socket) {
                std::unique_lock<std::timed_mutex> lock(m_socketMutex);
                auto frameSize = m_socket->receiveFrame(pocobuffer, flags);
                lock.unlock();
                auto messagePayload = std::string(pocobuffer.begin(), static_cast<size_t>(frameSize));
                auto frameOpCode = flags & Poco::Net::WebSocket::FRAME_OP_BITMASK;
                if (frameOpCode == Poco::Net::WebSocket::FRAME_OP_PING){
                    writeMessage(messagePayload, Poco::Net::WebSocket::FRAME_OP_PONG);
                }
                else if (frameOpCode == Poco::Net::WebSocket::FRAME_OP_PONG) {
                    // handle pong
                }
                else if (frameSize == 0 || frameOpCode == Poco::Net::WebSocket::FRAME_OP_CLOSE){
                    AG_LOG_INFO("close connection");
                    closedFromNetwork = true;
                }
                else {
                    m_socketUser.handleTextMessage(messagePayload);
                }
            }
        }
        catch (Poco::Exception& e) {
            closedFromNetwork = true;
            AG_LOG_ERROR("connection closed with exception: "+ std::string(e.what()));
        }
    } while (!closedFromNetwork && !m_disconnectRequested);

    if (closedFromNetwork){
        onClosed();
        m_socketUser.onConnectionClosedFromNetwork();
    }
}

bool SocketWrapper::writeMessage(const std::string& message, int frameOpCode)
{
    bool succeed = false;
    try {
        if (m_socket) {
            std::unique_lock<std::timed_mutex> lock(m_socketMutex);
            m_socket->sendFrame(message.c_str(), static_cast<int>(message.size()), frameOpCode);
            lock.unlock();
            succeed = true;
        }
    }
    catch (std::exception& e) {
        AG_LOG_ERROR("writeMessage Exception: "+ std::string(e.what()));
    }
    return succeed;
}

void SocketWrapper::writeMessageWithQueue(const std::string& msg)
{
    std::unique_lock<std::timed_mutex> lock(m_queueMutex);
    m_queue.push_back(msg);
    lock.unlock();
    scheduleProcessMessages(smallDelay);
}

bool SocketWrapper::isClosed() const
{
    return m_socket == nullptr || m_disconnectRequested;
}

void SocketWrapper::close()
{
    closeQueue();
    m_disconnectRequested = true;
    if (m_receivingDone.valid()){
        m_receivingDone.wait();
    }
    writeMessage(closeFramePayload, Poco::Net::WebSocket::FRAME_OP_CLOSE);
    onClosed();
}

void SocketWrapper::onClosed()
{
    std::unique_lock<std::timed_mutex> lock(m_socketMutex, std::defer_lock);
    if (!lock.try_lock_for(std::chrono::milliseconds(100))) {
        AG_LOG_INFO("Closing socket, some messages may be dropped");
    }
    m_socket.reset();
    lock.unlock();
}

std::unique_ptr<Poco::Net::WebSocket> SocketWrapper::changeSocket(std::unique_ptr<Poco::Net::WebSocket> otherSocket)
{
    if (m_processMessagesTask) {
    std::unique_lock<std::timed_mutex> lock(m_taskMutex);
    m_processMessagesTask->cancel();
    m_processMessagesTask.reset();
    lock.unlock();
}
    m_disconnectRequested = true;
    if (m_socket && m_receivingDone.valid()){
        m_receivingDone.wait();
    }
    std::unique_lock<std::timed_mutex> lock(m_socketMutex);
    std::swap(m_socket, otherSocket);
    lock.unlock();
    if (m_socket){
        // Common default maximum frame size is 1Mb
        m_socket->setMaxPayloadSize(1048576);
        std::future<void> other;
        std::swap(m_receivingDone, other);
        m_receivingDone = std::async(std::launch::async, [this](){startReceiving(); });
        scheduleProcessMessages(smallDelay);
    }
    m_disconnectRequested = false;
    return otherSocket;
}

void SocketWrapper::closeQueue()
{
    if (m_processMessagesTask) {
        std::unique_lock<std::timed_mutex> lock(m_taskMutex);
        m_processMessagesTask->cancel();
        m_processMessagesTask.reset();
        lock.unlock();
    }
    flushMessages();
}


void SocketWrapper::scheduleProcessMessages(long delayMiliseconds)
{
    std::unique_lock<std::timed_mutex> lock(m_taskMutex, std::defer_lock);
    if (lock.try_lock()) // else other thread is scheduling a task currently, so the messages would be sent anyway.
    {
        if (!m_processMessagesTask) {
            m_processMessagesTask = new Poco::Util::TimerTaskAdapter<SocketWrapper>(*this, &SocketWrapper::processMessages);
            m_retryTimer.schedule(m_processMessagesTask, delayMiliseconds, retryInterval);
            lock.unlock();
        }
    }
}

void SocketWrapper::processMessages(Poco::Util::TimerTask& /*task*/)
{
    if (isClosed()) {
        m_socketUser.onNotifyNoSocket();
        return;
    }
    if (m_addPingMessage) {
        writeMessage(pingFramePayload, Poco::Net::WebSocket::FRAME_OP_PING);
    }
    flushMessages();

    std::unique_lock<std::timed_mutex> lock(m_taskMutex);
    m_processMessagesTask->cancel();
    m_processMessagesTask.reset();
    lock.unlock();
    if (!m_queue.empty()){
        scheduleProcessMessages(smallDelay);
    }
}

void SocketWrapper::flushMessages()
{
    if (m_socket)
    {
        std::deque<std::string> copyQueue;

        std::unique_lock<std::timed_mutex> lock(m_queueMutex);
        if (m_queue.size() > messagesToSendAtOnce && !isClosed()){
            copyQueue.insert(copyQueue.begin(), m_queue.begin(), m_queue.begin() + (messagesToSendAtOnce-1));
            m_queue.erase(m_queue.begin(), m_queue.begin() + (messagesToSendAtOnce - 1));
            lock.unlock();
        } else {
            std::swap(copyQueue, m_queue);
            lock.unlock();
        }

        while (!copyQueue.empty()) {
            auto message = copyQueue.front();
            const static std::string log = "write message to socket ";
            AG_LOG_DEBUG(log);
            AG_LOG_DEBUG(message);
            // if we are using JSON we need to use txt message otherwise binary messages
            auto messageSent = writeMessage(message, Poco::Net::WebSocket::FRAME_TEXT);
            if (messageSent) {
                copyQueue.pop_front();
            }
            else {
                if (!isClosed()) {
                    lock.lock();
                    // push again not sent elements to queue front 
                    m_queue.insert(m_queue.begin(), copyQueue.begin(), copyQueue.end());
                    lock.unlock();
                }
                break;
            }
        }
    }
}

}}   //namespace ApiGear::PocoImpl
