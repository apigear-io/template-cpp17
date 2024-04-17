#pragma once

#include "isocketuser.h"
#include "socketwrapper.h"

#include "olink/remotenode.h"
#include "olink/consolelogger.h"

#include <Poco/Net/WebSocket.h>

#include <memory>
#include <mutex>

namespace ApiGear {

namespace Utilities {
    class ThreadPool;
}

namespace ObjectLink {
// Forward declaration of RemoteRegistry
class RemoteRegistry;
} // namespace ObjectLink

namespace PocoImpl {
// Forward declaration of IConnectionStorage
class IConnectionStorage;

/**
* ServerConnection provides network implementation for connection.
* It receives messages for given websocket and allows writing messages to it.
*/
class OLinkRemote : public ISocketUser
{
public:
    /**
    * ctor
    * @param socket A socket used for this connection.
    * @param connectionStorage Storage that needs to be informed if client ended the connection.
    * @param registry. A global registry to which network endpoints are added for olink objects.
    * @param logFunc The function to be used for logging inside the objectlink core remote nodes.
    */
    explicit OLinkRemote(std::unique_ptr<Poco::Net::WebSocket> socket,
                        IConnectionStorage& connectionStorage,
                        ApiGear::ObjectLink::RemoteRegistry& registry,
                        const ApiGear::ObjectLink::WriteLogFunc& logFunc);
    /**dtor*/
    ~OLinkRemote();

    /** 
    * Checks if connection is in closed state
    * @return true if connection is in closed state, false if it is up and running.
    */
    bool isClosed() const;

    /**
    * ISocketUser::handleTextMessage implementation.
    * Handler for raw message received.
    */
    void handleTextMessage(const std::string& msg) override;

    /** 
    * ISocketUser::onConnectionClosedFromNetwork implementation
    * A callback to inform the socket user that connection was closed with close frame received from network.
    */
    void onConnectionClosedFromNetwork() override;
private:
    /**A socket used for this connection.*/
    SocketWrapper m_socket;
    /**Storage that needs to be informed if client ended the connection.*/
    IConnectionStorage& m_connectionStorage;

    /** 
    *   An abstract connection endpoint for services, network implementation independent.
    *   may serve several services associated with this node by the unique objectId given in link message.
    */
    std::shared_ptr<ApiGear::ObjectLink::RemoteNode> m_node;
};
}}   //namespace ApiGear::PocoImpl
