#include "connectionstorage.h"
#include "olinkremote.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include "olink/remoteregistry.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
#include <Poco/Util/TimerTaskAdapter.h>
#include <chrono>
#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

namespace ApiGear {
namespace PocoImpl {


ConnectionStorage::ConnectionStorage(ApiGear::ObjectLink::RemoteRegistry& registry, const ApiGear::ObjectLink::WriteLogFunc& logFunc)
  :m_registry(registry)
  , m_logFunc(logFunc)
{}

void ConnectionStorage::notifyConnectionClosed()
{
	m_removeConnectionTimer.cancel(true);
	std::unique_lock<std::mutex> lock(m_taskMutex);
	if (m_removeConnectionTask){
		m_removeConnectionTask->cancel();
	}
	m_removeConnectionTask = new Poco::Util::TimerTaskAdapter<ConnectionStorage>(*this, &ConnectionStorage::removeClosedConnection);
	lock.unlock();
	// This function is called by connection itself, therfore to allow it to finish its function, and to be removed properly
	// The  removing the connection is scheduled in 1ms, so it is executed outside this call.
	long startTaskDelayMilliseconds = 1;
	long repeatTaskDelayMilliseconds = 10000;
	m_removeConnectionTimer.schedule(m_removeConnectionTask, startTaskDelayMilliseconds, repeatTaskDelayMilliseconds);
}

void ConnectionStorage::addConnection(std::unique_ptr<Poco::Net::WebSocket> connectionSocket)
{
	auto newConnection = std::make_shared<OLinkRemote>(std::move(connectionSocket), *this, m_registry, m_logFunc);
	std::unique_lock<std::mutex> lock(m_connectionsMutex);
	m_connectionNodes.push_back(newConnection);
	lock.unlock();
}

void ConnectionStorage::closeConnections()
{
	{
		std::unique_lock<std::mutex> taskLock(m_taskMutex);
		if (m_removeConnectionTask){
			m_removeConnectionTask->cancel();
			m_removeConnectionTask.reset();
		}
	}
	// Move connections out under lock, destroy outside to avoid
	// deadlock with removeClosedConnection timer callback.
	std::vector<std::shared_ptr<OLinkRemote>> toDestroy;
	{
		std::unique_lock<std::mutex> connectionLock(m_connectionsMutex);
		std::swap(toDestroy, m_connectionNodes);
	}
	toDestroy.clear();
}

void ConnectionStorage::removeClosedConnection(Poco::Util::TimerTask& /*task*/)
{
	// Move closed connections out under lock, destroy outside to avoid
	// holding m_connectionsMutex during OLinkRemote destruction (which
	// does blocking I/O in SocketWrapper::close).
	std::vector<std::shared_ptr<OLinkRemote>> closedNodes;
	{
		std::unique_lock<std::mutex> lock(m_connectionsMutex);
		auto closedBegin = std::partition(m_connectionNodes.begin(),
			m_connectionNodes.end(),
			[](const auto& element){return !element->isClosed(); });
		closedNodes.assign(std::make_move_iterator(closedBegin), std::make_move_iterator(m_connectionNodes.end()));
		m_connectionNodes.erase(closedBegin, m_connectionNodes.end());
	}
	// closedNodes destroyed here outside the lock
}

}}   //namespace ApiGear::PocoImpl
