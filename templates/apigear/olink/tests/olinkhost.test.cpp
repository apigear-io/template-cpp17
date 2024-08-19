#pragma warning (disable: 4251) 
#pragma warning (disable: 4099) 

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "private/frame.hpp"
#include "private/sourceobjectmock.hpp"
#include "private/test_server/test_server.hpp"

#include "../olinkhost.h"

#include "olink/remoteregistry.h"
#include "olink/core/types.h"
#include "olink/core/protocol.h"

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"

#include "nlohmann/json.hpp"
#include <mutex>
#include <string>
#include <condition_variable>

namespace tests{

namespace {
    // Message converter to translate messages for network format. Same should be used in tested classes.
    ApiGear::ObjectLink::MessageConverter converter(ApiGear::ObjectLink::MessageFormat::JSON);

    Frame receiveFrame (Poco::Net::WebSocket& socket)
    {
        Frame inFrame;
        Poco::Buffer<char> pocobuffer(0);
        auto receivedSize = socket.receiveFrame(pocobuffer, inFrame.flags);
        inFrame.payload = std::string(pocobuffer.begin(), receivedSize);
        return inFrame;
    }

}

    TEST_CASE("OLinkHost tests")
    {
        ApiGear::ObjectLink::RemoteRegistry registry;
        registry.onLog([](auto /*level*/, auto msg){ std::cout << msg << std::endl; });

        auto source1 = std::make_shared<SourceObjectMock>();
        std::string objectId = "tests.sink1";
        ALLOW_CALL(*source1, olinkObjectName()).RETURN(objectId);
        registry.addSource(source1);

        // Common data.
        auto portNumber = 8000;
        auto localHostAddress = "127.0.0.1";
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/ws", Poco::Net::HTTPRequest::HTTP_1_1);
        Poco::Net::HTTPResponse response;

        nlohmann::json initProperties1 = { {"property1", "some_string1" }, { "property2",  92 }, { "property3", true } };
        nlohmann::json initProperties2 = { {"property1", "some_string2" }, { "property2",  29 }, { "property3", false } };

        std::string any_payload = "any";

        ApiGear::PocoImpl::OLinkHost testHost(registry, [](auto /*level*/, auto msg){ std::cout << msg << std::endl; });
        std::condition_variable m_waitForMessageEffects;
        std::mutex m_waitForMessageEffectsMutex;
        std::unique_lock<std::mutex> lock(m_waitForMessageEffectsMutex, std::defer_lock);

        SECTION("Server creates two nodes for link messages from different sessions for same source and sends back init message. Unlink happens before server closes.")
        {
            testHost.listen(portNumber);
            
            Poco::Net::HTTPClientSession clientSession1(localHostAddress, portNumber);
            Poco::Net::HTTPClientSession clientSession2(localHostAddress, portNumber);
            Poco::Net::WebSocket clientSocket1(clientSession1, request, response), clientSocket2(clientSession2, request, response);
            
            auto preparedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(objectId));
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));

            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties1);
            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties2);

            clientSocket1.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));
            clientSocket2.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));
            
            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 2; });
            lock.unlock();
            auto nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 2);
            auto nodeA = nodes[0];
            auto nodeB = nodes[1];
            REQUIRE(nodeA.expired() == false);
            REQUIRE(nodeB.expired() == false);
            REQUIRE(nodeA.lock() != nodeB.lock());

            // Check that server sent init messages
            auto expectedInitMessage1 = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(objectId, initProperties1));
            auto expectedInitMessage2 = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(objectId, initProperties2));
            {
                auto msg1 = receiveFrame(clientSocket1);
                auto checkReceivedMessage = msg1.payload == expectedInitMessage1 || msg1.payload == expectedInitMessage2;
                REQUIRE(checkReceivedMessage);
                REQUIRE(msg1.flags == Poco::Net::WebSocket::FRAME_TEXT);
            }

            {
                auto msg2 = receiveFrame(clientSocket2);
                auto checkReceivedMessage = msg2.payload == expectedInitMessage1 || msg2.payload == expectedInitMessage2;
                REQUIRE(checkReceivedMessage);
                REQUIRE(msg2.flags == Poco::Net::WebSocket::FRAME_TEXT);
            }

            REQUIRE_CALL(*source1, olinkUnlinked(objectId));

            auto unlinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(objectId));
            clientSocket1.sendFrame(unlinkMessage.c_str(), static_cast<int>(unlinkMessage.size()));
            
            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 1; });
            lock.unlock();
            nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 1);
            auto node2 = nodes[0];
            REQUIRE(node2.expired() == false);
            bool nodeDidNotChanged = node2.lock() == nodeA.lock() || node2.lock() == nodeB.lock();
            REQUIRE(nodeDidNotChanged);

            REQUIRE_CALL(*source1, olinkUnlinked(objectId));
            clientSocket2.sendFrame(unlinkMessage.c_str(), static_cast<int>(unlinkMessage.size()));
            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 0; });
            lock.unlock();
            nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 0);
            
            clientSocket1.sendFrame(any_payload.c_str(), static_cast<int>(any_payload.size()),Poco::Net::WebSocket::FRAME_OP_CLOSE);
            clientSocket2.sendFrame(any_payload.c_str(), static_cast<int>(any_payload.size()),Poco::Net::WebSocket::FRAME_OP_CLOSE);
            // Send close Frame
            Poco::Thread::sleep(50);

            testHost.close();
        }

        SECTION("Host close before session closes. Only information sent to clients is close frame.")
        {
            testHost.listen(portNumber);

            Poco::Net::HTTPClientSession clientSession1(localHostAddress, portNumber);
            Poco::Net::WebSocket clientSocket1(clientSession1, request, response);

            auto preparedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(objectId));
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));

            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties1);

            clientSocket1.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));

            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 1; });
            lock.unlock();
            auto nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 1);
            REQUIRE(nodes[0].expired() == false);

            // Check that server sent init messages
            auto expectedInitMessage1 = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(objectId, initProperties1));
            {
                auto msg1 = receiveFrame(clientSocket1);
                REQUIRE(msg1.payload == expectedInitMessage1);
                REQUIRE(msg1.flags == Poco::Net::WebSocket::FRAME_TEXT);
            }

            testHost.close();
            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 0; });
            lock.unlock();
            REQUIRE(registry.getNodes(objectId).size() == 0);
            REQUIRE(registry.getSource(objectId).lock() == source1);

            {
                auto closeFrame = receiveFrame(clientSocket1);
                REQUIRE(closeFrame.flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
            }
        }

        SECTION("Source removal doesn't affect setup. It should inform somehow clients that service is not available.")
        {
            testHost.listen(portNumber);

            Poco::Net::HTTPClientSession clientSession1(localHostAddress, portNumber);
            Poco::Net::WebSocket clientSocket1(clientSession1, request, response);

            auto preparedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(objectId));
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));

            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties1);

            clientSocket1.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));

            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 1; });
            lock.unlock();
            auto nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 1);
            REQUIRE(nodes[0].expired() == false);

            // Check that server sent init messages
            auto expectedInitMessage1 = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(objectId, initProperties1));
            {
                auto msg1 = receiveFrame(clientSocket1);
                REQUIRE(msg1.payload == expectedInitMessage1);
                REQUIRE(msg1.flags == Poco::Net::WebSocket::FRAME_TEXT);
            }
            // start test
            registry.removeSource(objectId);

            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 0; });
            lock.unlock();

            REQUIRE(registry.getNodes(objectId).size() == 0);
            REQUIRE(registry.getSource(objectId).expired());

            // test cleanup
            testHost.close();
            Poco::Thread::sleep(50);

            // Receive close frame on close.
            {
                auto closeFrame = receiveFrame(clientSocket1);
                REQUIRE(closeFrame.flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
            }
        }

        SECTION("One of connections receive close frame")
        {
            testHost.listen(portNumber);

            Poco::Net::HTTPClientSession clientSession1(localHostAddress, portNumber);
            Poco::Net::HTTPClientSession clientSession2(localHostAddress, portNumber);
            Poco::Net::WebSocket clientSocket1(clientSession1, request, response), clientSocket2(clientSession2, request, response);

            auto preparedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(objectId));
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));

            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties1);
            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties2);

            clientSocket1.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));
            clientSocket2.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));


            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 2; });
            lock.unlock();
            auto nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 2);
            auto nodeA = nodes[0];
            auto nodeB = nodes[1];
            REQUIRE(!nodeA.expired());
            REQUIRE(!nodeB.expired());
            REQUIRE(nodeA.lock() != nodeB.lock());

            // Check that server sent init messages
            auto expectedInitMessage1 = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(objectId, initProperties1));
            auto expectedInitMessage2 = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(objectId, initProperties2));
            {
                auto msg1 = receiveFrame(clientSocket1);
                auto checkReceivedMessage = msg1.payload == expectedInitMessage1 || msg1.payload == expectedInitMessage2;
                REQUIRE(checkReceivedMessage);
                REQUIRE(msg1.flags == Poco::Net::WebSocket::FRAME_TEXT);
            }

            {
                auto msg2 = receiveFrame(clientSocket2);
                auto checkReceivedMessage = msg2.payload == expectedInitMessage1 || msg2.payload == expectedInitMessage2;
                REQUIRE(checkReceivedMessage);
                REQUIRE(msg2.flags == Poco::Net::WebSocket::FRAME_TEXT);
            }

            // START TEST
            clientSocket1.sendFrame(any_payload.c_str(), static_cast<int>(any_payload.size()), Poco::Net::WebSocket::FRAME_OP_CLOSE);
            // Send close Frame

            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 1; });
            lock.unlock();
            nodes = registry.getNodes(objectId);
            // Node 2 still works for source
            REQUIRE(nodes.size() == 1);
            auto node2 = nodes[0];
            REQUIRE(!node2.expired());
            bool nodeDidNotChanged = node2.lock() == nodeA.lock() || node2.lock() == nodeB.lock();
            REQUIRE(nodeDidNotChanged);
            // client 2 receives close frame
            testHost.close();
            {
                auto closeFrame = receiveFrame(clientSocket2);
                REQUIRE(closeFrame.flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
            }
        }

        SECTION("Connection receives close frame from one client, and then client is up again")
        {
            testHost.listen(portNumber);

            Poco::Net::HTTPClientSession clientSession1(localHostAddress, portNumber);
            Poco::Net::WebSocket clientSocket1(clientSession1, request, response);

            auto preparedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(objectId));
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));
            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties1);
            clientSocket1.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));

            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 1; });
            lock.unlock();
            auto nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 1);
            REQUIRE(!nodes[0].expired());

            // Check that server sent init message
            auto expectedInitMessage1 = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(objectId, initProperties1));
            {
                auto receivedInit = receiveFrame(clientSocket1);
                REQUIRE(receivedInit.payload == expectedInitMessage1);
                REQUIRE(receivedInit.flags == Poco::Net::WebSocket::FRAME_TEXT);
            }

            // START TEST
            clientSocket1.sendFrame(any_payload.c_str(), static_cast<int>(any_payload.size()), Poco::Net::WebSocket::FRAME_OP_CLOSE);

            // Send close Frame
            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 0; });
            lock.unlock();
            nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 0);

            // Wait after close with opening a new connection
            Poco::Thread::sleep(50);
            //Poco::Net::HTTPClientSession clientSession2(localHostAddress, portNumber);
            Poco::Net::WebSocket clientSocket2(clientSession1, request, response);
            REQUIRE_CALL(*source1, olinkLinked(objectId, ANY(ApiGear::ObjectLink::IRemoteNode*)));
            REQUIRE_CALL(*source1, olinkCollectProperties()).RETURN(initProperties1);
            clientSocket2.sendFrame(preparedLinkMessage.c_str(), static_cast<int>(preparedLinkMessage.size()));

            lock.lock();
            m_waitForMessageEffects.wait_for(lock, std::chrono::milliseconds(500), [&registry, objectId]() {return registry.getNodes(objectId).size() == 1; });
            lock.unlock();
            nodes = registry.getNodes(objectId);
            REQUIRE(nodes.size() == 1);
            REQUIRE(!nodes[0].expired());

            // Check that server sent init message
            REQUIRE(receiveFrame(clientSocket2).payload == expectedInitMessage1);
            // client 2 receives close frame
            testHost.close();
            {
                auto closeFrame = receiveFrame(clientSocket2);
                REQUIRE(closeFrame.flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
            }
        }

    }

}// namespace tests