#pragma once

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/NetException.h"
#include <iostream>
#include <memory>
#include <functional>

#include "tests/private/frame.hpp"
#include "tests/private/test_server/iframestorage.hpp"

namespace tests
{

// Poco::Net::Server keeps ownership of this object.
// Runs the handleRequest in a separate thread.
// Creates and holds a socket for connection.
// Allows to set behavior for receiving and sending frames.
class TestServerRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	TestServerRequestHandler(IFrameStorage& frameStorage)
		:m_frameStorage(frameStorage)
	{}

	// Called by a server. Creates and holds a socket for connection.
	// Allows to set behavior for receiving and sending frames.
	// @param request A request from a client, contains information about a client.
	// @param response Will be returned to a client. Allows handling errors. Not relevant for test server purpose.
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override
	{
		try
		{
			socket = std::shared_ptr<Poco::Net::WebSocket>(new Poco::Net::WebSocket(request, response));
			setWriteFunctionForFrameStorage(socket);

			bool stop = false;
			// receive messages in loop 
			do
			{
				Poco::Buffer<char> pocobuffer(0);
				Frame inFrame;
				auto receivedSize = socket->receiveFrame(pocobuffer, inFrame.flags);
				inFrame.payload = std::string(pocobuffer.begin(), receivedSize);
				bool isCloseFrame = (inFrame.flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_CLOSE;
				if (receivedSize != 0 || isCloseFrame)
				{
					m_frameStorage.storeFrame(inFrame);
				}
				stop = receivedSize == 0 || isCloseFrame;		
			} while (!stop);
			socket.reset();
		}
		catch (Poco::Net::WebSocketException& /*exc*/)
		{
			std::cout << "ERROR handleRequest exception " << std::endl;
		}
	}

	// Sets a function in frame storage to send frames .
	// @param weakSocket A weak pointer to an initialized socket for a connection with client.
	void setWriteFunctionForFrameStorage(std::weak_ptr<Poco::Net::WebSocket> weakSocket)
	{
		m_frameStorage.setRequestSendFunction(
			[weakSocket](Frame outFrame)
			{
				auto socket = weakSocket.lock();
				if (socket)
				{
					socket->sendFrame(outFrame.payload.c_str(), static_cast<int>(outFrame.payload.size()), outFrame.flags);
				}
			});
	}

	// Socket for connection with client.
	std::shared_ptr<Poco::Net::WebSocket> socket;
	// The frames owner. Stores incoming frames and sends outgoing frames.
	IFrameStorage& m_frameStorage;
};

} //namespace tests
