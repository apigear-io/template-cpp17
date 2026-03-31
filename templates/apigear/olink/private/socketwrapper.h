#pragma once

#include "apigear_olink.h"

#include <Poco/Net/WebSocket.h>

#include <atomic>
#include <memory>
#include <future>


#include <Poco/URI.h>
#include <Poco/Util/Timer.h>
#include <Poco/Util/TimerTask.h>

#include <atomic>
#include <deque>
#include <memory>
#include <map>

namespace ApiGear {


namespace PocoImpl {

class ISocketUser;

/**
* A helper class for wrapping POCO::WebSocket.
* Adds receiving message in a separate thread.
* Adds thread safety for writing and reading through socket.
* Allows sending messages with sending queue (with some delay up to small number of milliseconds) or sending directly.
*/
class APIGEAR_OLINK_EXPORT  SocketWrapper
{
public:

    /**
    * ctor
    * @param socketUser A user that will be notified about events defined as ISocketUser API.
    * @param sendPing. Set to true if your socket should send ping each time it sends portion of queued messages.
    */
    SocketWrapper(ISocketUser& socketUser, bool sendPing);

    ~SocketWrapper();

    /** 
    * Sends message through the socket.
    * If the connection is not working, message will not be stored to resend.
    * @param message a message in network format to be send as it is.
    * @param the frame opcode. Use FRAME_TEXT or FRAME_BINARY for regular text messages
    *   see Poco::Net::WebSocket Frame Opcodes for more info.
    * @return true if message was sent, false otherwise.
    */
    bool writeMessage(const std::string& message, int frameOpCode);
    /**
    * Use this method to send pack of messages.
    * Messages are queued for up to few milliseconds and sent. 
    * If the connection is not working, message are stored and send when connection is back.
    * @param message a message in network format to be send as it is. Destined for regular text messages.
        The opcode is not a parameter.
    */
    void writeMessageWithQueue(const std::string& msg);
    /**
    * Checks if connection is in closed state
    * @return true if connection is in closed state, false if it is up and running.
    */
    bool isClosed() const;
    
    /**
    * Requests closing connection with sending a close frame and puts the class in closed state.
    * From now the messages cannot be received and send, connection cannot be restored.
    * This is final state from which socket cannot recover, only a new socket can be given to SocketWrapper to wrap and use.
    * see SocketWrapper::changeSocket function
    */
    void close();

    /**
    * Use this function to set new socket that SocketWrapper is wrapping.
    * @param otherSocket. A socket that SocketWrapper is about to wrap and take ownership of.
    * @return A socket that SocketWrapper was wrapping before this function call, and which ownership is
    *   given away to a caller. May be empty if no socket was used before or if connection is already closed. 
    */
    std::unique_ptr<Poco::Net::WebSocket> changeSocket(std::unique_ptr<Poco::Net::WebSocket> otherSocket);

private:
    /**
    * Receives messages from clients. Blocking function, run in a separate thread.
    */
    void startReceiving();
    /** Helper function to finalize closing socket and cleans up resources. */
    void onClosed();

    /* Sends all queued messages and sends close frame*/
    void closeQueue();
    /**
    * Processes queued messages.
    * @param task. Parameter is not used. The function uses most recent task stored as a member.
    */
    void processMessages(Poco::Util::TimerTask& task);
    /** Schedules a process messages task.
        @param delayMiliseconds. A delay with which task is scheduled.
    */
    void scheduleProcessMessages(long delayMiliseconds);

    /** 
    * Sends stored messages
    * If queue is very long, only part of messages is sent in one loop, and rest is scheduled to be sent with next task.
    * allowing socket to receive incoming messages in the meantime and sending ping messages.
    */
    void flushMessages();

    /** The websocket used for connection.*/
    std::unique_ptr<Poco::Net::WebSocket> m_socket;
    /** A mutex for the socket */
    std::timed_mutex m_socketMutex;
    /** A user that will be notified about events defined as ISocketUser API. */
    ISocketUser& m_socketUser;
    /** True if socket should send ping messages. */
    bool m_addPingMessage;
    /** Flag handled between the threads with information that the connection should be closed. */
    std::atomic<bool> m_disconnectRequested;
    /** Result of receiveInLoop. Used to wait for end of its work after m_stopConnection is set to true*/
    std::future<void> m_receivingDone;

    /** The timer used for to process messages. */
    Poco::Util::Timer m_retryTimer;
    /** Poco Task that handles processing messages */
    Poco::Util::TimerTask::Ptr m_processMessagesTask;
    /** A mutex for the process messages task */
    std::timed_mutex m_taskMutex;
    /** Messages queue, store messages to send also before the connection is set. */
    std::deque<std::string> m_queue;
    /** A mutex for the message queue */
    std::timed_mutex m_queueMutex;
};

}}   //namespace ApiGear::PocoImpl
