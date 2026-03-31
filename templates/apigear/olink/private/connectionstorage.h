#pragma once

#include "iconnectionstorage.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include "olink/core/types.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#include <Poco/Util/Timer.h>
#include <Poco/Util/TimerTask.h>

#include <mutex>
#include <memory>
#include <vector>
#include <future>

namespace ApiGear
{

// Remote registry forward declaration.
namespace ObjectLink
{
class RemoteRegistry;
}

namespace PocoImpl
{

// OlinkRemote forward declaration
class OLinkRemote;

/**
* Implementation of IConnectionStorage, a class for OLinkHost to store connections.
*/
class ConnectionStorage : public IConnectionStorage
{
public:
	/**ctor
	* @param registry A global registry to which network endpoints are added for olink objects.
    * @param logFunc The function to be used for logging inside the objectlink core remote nodes.
	*/
	ConnectionStorage(ApiGear::ObjectLink::RemoteRegistry& registry, const ApiGear::ObjectLink::WriteLogFunc& logFunc);
	/** Close all connections.*/
	void closeConnections();

	/**IConnectionStorage::addConnection implementation*/
	void addConnection(std::unique_ptr<Poco::Net::WebSocket> connectionSocket) override;
	/**IConnectionStorage::notifyConnectionClosed implementation*/
	void notifyConnectionClosed() override;
private:
	/**
	* Removes all connection that are marked as closed.
	* @param task. Parameter is not used. The most recent task is stored as a member to cancel it if necessary.
	*/
	void removeClosedConnection(Poco::Util::TimerTask& task);

	/**A global registry to which network endpoints will be added for olink objects.*/
	ApiGear::ObjectLink::RemoteRegistry& m_registry;
	/** Collection of server connections*/
	std::vector<std::shared_ptr<OLinkRemote>> m_connectionNodes;
	/** Mutex for connection storage*/
	std::mutex m_connectionsMutex;

	/** The timer used to schedule remove closed connection. */
	Poco::Util::Timer m_removeConnectionTimer;
	/** Poco Task to remove closed connection, stored to be canceled if necessary. */
	Poco::Util::TimerTask::Ptr m_removeConnectionTask;
	/** A mutex for the process message*/
	std::mutex m_taskMutex;
	
	/** Logging function for nodes */
	ApiGear::ObjectLink::WriteLogFunc m_logFunc;
};

}}   //namespace ApiGear::PocoImpl
