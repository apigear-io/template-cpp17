#pragma warning (disable: 4251) 
#pragma warning (disable: 4099) 

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "olink/clientregistry.h"
#include "olink/core/types.h"
#include "olink/core/protocol.h"

#include "private/frame.hpp"
#include "private/sinkobjectmock.hpp"
#include "private/test_server/test_server.hpp"

#include "../olinkconnection.h"

#include "nlohmann/json.hpp"
#include <thread>
#include <algorithm>
#include <chrono>
#include <condition_variable>

namespace tests{

namespace {
    // Message converter to translate messages for network format. Same should be used in tested classes.
    ApiGear::ObjectLink::MessageConverter converter(ApiGear::ObjectLink::MessageFormat::JSON);
    const std::string any_payload = "any";

    int getMessageIndex(const std::vector<Frame>& container, const std::string& payload)
    {
        auto iter = std::find_if(container.begin(),
            container.end(),
            [&payload](auto& element){return element.payload == payload; });
        return iter != container.end()? std::distance(container.begin(), iter) : int(-1);
    }

    bool checkMessageInContainer(const std::vector<Frame>& container, const std::string& payload)
    {
       return std::find_if(container.begin(),
                           container.end(),
                           [&payload](auto& element){return element.payload == payload; })
           != container.end();
    }

}

TEST_CASE("OlinkConnection tests")
{
    auto portNumber = 8000;
    auto localHostAddress = "ws://127.0.0.1:" + std::to_string(portNumber);

    bool skipPingMessages = true;
    TestServer server(portNumber, skipPingMessages);
    ApiGear::ObjectLink::ClientRegistry registry;
    auto testOlinkConnection = std::make_shared<ApiGear::PocoImpl::OlinkConnection>(registry);

    auto sink1 = std::make_shared<SinkObjectMock>();
    std::string sink1Id = "tests.sink1";
    ALLOW_CALL(*sink1, olinkObjectName()).RETURN(sink1Id);

    std::condition_variable m_messageArrived;
    std::mutex m_messageArrivedMutex;
    std::unique_lock<std::mutex> lock(m_messageArrivedMutex, std::defer_lock);

    SECTION("Connect to host when sink is added and server is running. On teardown first disconnect sink then the client")
    {
        server.start();

        testOlinkConnection->connectToHost(Poco::URI(localHostAddress));
        testOlinkConnection->connectAndLinkObject(sink1);
        REQUIRE(registry.getSink(sink1Id).lock() == sink1);
        REQUIRE(registry.getNode(sink1Id).lock() == testOlinkConnection->node());

        // Check that server received link message
        auto expectedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(sink1Id));

        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        auto msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        REQUIRE(msgs[0].payload == expectedLinkMessage);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_TEXT);

        // Send init message from server and check it is delivered and decoded
        nlohmann::json initProperties = { {"property1", "some_string" }, { "property2",  9 }, { "property3", false } };
        REQUIRE_CALL(*sink1, olinkOnInit(sink1Id, initProperties, testOlinkConnection->node().get()));

        auto preparedInitMessage = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(sink1Id, initProperties));
        server.sendFrame(preparedInitMessage);
        // Wait for init message to be delivered and handled before the sink will be released
        Poco::Thread::sleep(30);

        // Remove sink: unlink, detach from node, remove from registry.
        REQUIRE_CALL(*sink1, olinkOnRelease());
        testOlinkConnection->disconnectAndUnlink(sink1Id);
        REQUIRE(registry.getSink(sink1Id).lock() == nullptr);
        REQUIRE(registry.getNode(sink1Id).lock() == nullptr);

        //Check the unlink message
        auto expectedUnlinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(sink1Id));
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        REQUIRE(msgs[0].payload == expectedUnlinkMessage);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_TEXT);

        testOlinkConnection->disconnect();
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() > 0);
        // Check close frame was sent
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
        server.stop();
    }

    SECTION("Add sink after connecting to host. On teardown disconnect the client from server first. ")
    {
        server.start();
        // Connect sink
        testOlinkConnection->connectAndLinkObject(sink1);
        REQUIRE(registry.getSink(sink1Id).lock() == sink1);
        // Node will be added to registry after it is linked - so connection needs to be established first.
        REQUIRE(registry.getNode(sink1Id).lock() == nullptr);

        // Connect to server
        testOlinkConnection->connectToHost(Poco::URI(localHostAddress));
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        auto msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        // expect the link message to be received on server side 
        auto expectedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(sink1Id));
        REQUIRE(msgs[0].payload == expectedLinkMessage);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_TEXT);
        REQUIRE(registry.getNode(sink1Id).lock() == testOlinkConnection->node());

        // Send from server init message
        nlohmann::json initProperties = { {"property1", "some_string" }, { "property2",  9 }, { "property3", false } };

        std::atomic<bool> isInitReceived{ false };
        auto setInitReceived = [&isInitReceived]() {isInitReceived = true; };

        REQUIRE_CALL(*sink1, olinkOnInit(sink1Id, initProperties, testOlinkConnection->node().get())).SIDE_EFFECT(setInitReceived(););
        auto preparedInitMessage = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(sink1Id, initProperties));
        server.sendFrame(preparedInitMessage);
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&isInitReceived]() {return isInitReceived == true; });
        lock.unlock();


        // Stop connection
        REQUIRE_CALL(*sink1, olinkOnRelease());
        testOlinkConnection->disconnect();

        // Sink stays in registry in case user wants to reconnect.
        REQUIRE(registry.getSink(sink1Id).lock() == sink1);
        REQUIRE(registry.getNode(sink1Id).lock() == nullptr);

        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 2; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        auto expectedUnlinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(sink1Id));
        REQUIRE(msgs.size() == 2);
        REQUIRE(msgs[0].payload == expectedUnlinkMessage);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_TEXT);
        // Check close frame was sent
        REQUIRE(msgs[1].flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);

        testOlinkConnection->disconnectAndUnlink(sink1Id);
        REQUIRE(registry.getSink(sink1Id).lock() == nullptr);
        server.stop();
    }

    SECTION("Disconnect and reconnect scenario")
    {
        auto sink2 = std::make_shared<SinkObjectMock>();
        std::string sink2Id = "tests.sink2";
        ALLOW_CALL(*sink2, olinkObjectName()).RETURN(sink2Id);

        server.start();
        testOlinkConnection->connectAndLinkObject(sink1);
        testOlinkConnection->connectAndLinkObject(sink2);

        // Connect to server
        testOlinkConnection->connectToHost(Poco::URI(localHostAddress));
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 2; });
        lock.unlock();
        auto msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 2);
        // expect the link message to be received on server side 
        auto expectedLinkMessage1 = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(sink1Id));
        auto expectedLinkMessage2 = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(sink2Id));

        REQUIRE(checkMessageInContainer(msgs, expectedLinkMessage1));
        REQUIRE(checkMessageInContainer(msgs, expectedLinkMessage2));

        // Disconnect
        REQUIRE_CALL(*sink1, olinkOnRelease());
        REQUIRE_CALL(*sink2, olinkOnRelease());
        testOlinkConnection->disconnect();

        // Check unlink and close connection messages.
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 3; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 3);
        auto expectedUnlinkMessage1 = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(sink1Id));
        auto expectedUnlinkMessage2 = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(sink2Id));

        REQUIRE(checkMessageInContainer(msgs, expectedUnlinkMessage1));
        REQUIRE(checkMessageInContainer(msgs, expectedUnlinkMessage2));
        REQUIRE(msgs[2].flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);

        // Remove sink2 during disconnected
        testOlinkConnection->disconnectAndUnlink(sink2Id);

        // Connect again, node sends link message only for sink1.
        testOlinkConnection->connectToHost(Poco::URI(localHostAddress));
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        REQUIRE(checkMessageInContainer(msgs, expectedLinkMessage1));

        //Test teardown and cleanup
        REQUIRE_CALL(*sink1, olinkOnRelease());
        testOlinkConnection->disconnectAndUnlink(sink1Id);
        testOlinkConnection.reset();

        lock.lock();
        //  Unlink and a close frame.
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 2; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 2);
        REQUIRE(checkMessageInContainer(msgs, expectedUnlinkMessage1));
        REQUIRE(msgs[1].flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);

        server.stop();
    }

    SECTION("Cleanup resources olink connection destruction.")
    {
        server.start();
        // Connect sink
        testOlinkConnection->connectAndLinkObject(sink1);
        REQUIRE(registry.getSink(sink1Id).lock() == sink1);


        // Connect to server
        testOlinkConnection->connectToHost(Poco::URI(localHostAddress));
        // Wait for message to be sent with queue flush on tick, and action after sent happen.
        Poco::Thread::sleep(11);
        REQUIRE(registry.getNode(sink1Id).lock() == testOlinkConnection->node());
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        auto msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        // expect the link message to be received on server side 
        auto expectedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(sink1Id));
        REQUIRE(msgs[0].payload == expectedLinkMessage);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_TEXT);

        REQUIRE_CALL(*sink1, olinkOnRelease());
        testOlinkConnection.reset();
        REQUIRE(registry.getSink(sink1Id).lock() == nullptr);
        REQUIRE(registry.getNode(sink1Id).lock() == nullptr);

        // Check unlink was sent
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 2; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 2);
        auto expectedUnlinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(sink1Id));
        REQUIRE(msgs.size() == 2);
        REQUIRE(msgs[0].payload == expectedUnlinkMessage);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_TEXT);
        // Check close frame was sent
        REQUIRE(msgs[1].flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
        server.stop();
    }

    SECTION("Server sends close frame and then is up again")
    {
        server.start();

        testOlinkConnection->connectToHost(Poco::URI(localHostAddress));
        testOlinkConnection->connectAndLinkObject(sink1);
        REQUIRE(registry.getSink(sink1Id).lock() == sink1);
        REQUIRE(registry.getNode(sink1Id).lock() == testOlinkConnection->node());

        // Check that server received link message
        auto expectedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(sink1Id));

        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        auto msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        REQUIRE(msgs[0].payload == expectedLinkMessage);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_TEXT);

        // Send init message from server and check it is delivered and decoded
        nlohmann::json initProperties = { {"property1", "some_string" }, { "property2",  9 }, { "property3", false } };
        REQUIRE_CALL(*sink1, olinkOnInit(sink1Id, initProperties, testOlinkConnection->node().get()));

        auto preparedInitMessage = converter.toString(ApiGear::ObjectLink::Protocol::initMessage(sink1Id, initProperties));
        server.sendFrame(preparedInitMessage);
        // Wait for init message to be delivered and handled before the sink will be released
        Poco::Thread::sleep(30);


        //send close frame from server side
        server.sendFrame(any_payload, Poco::Net::WebSocket::FRAME_OP_CLOSE);
        // Wait for init message to be delivered and handled before the sink will be released
        Poco::Thread::sleep(30);
        // wait for re-connection
        Poco::Thread::sleep(1001);
        // Cleanup
        REQUIRE_CALL(*sink1, olinkOnRelease());
        testOlinkConnection->disconnectAndUnlink(sink1Id);
        auto expectedUnlinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(sink1Id));

        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 2; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 2);
        // Expect socket re-connects, and sends link message on re-connection
        REQUIRE(msgs[0].payload == expectedLinkMessage);
        //Check the unlink message
        REQUIRE(msgs[1].payload == expectedUnlinkMessage);

         testOlinkConnection->disconnect();
         lock.lock();
         m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
         lock.unlock();
         msgs = server.getReceivedFrames();
         REQUIRE(msgs.size() == 1);
         // Check close frame was sent
         REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
         server.stop();
    }

    SECTION("queuing messages when connection is lost")
    {
        server.start();
        testOlinkConnection->connectToHost(Poco::URI(localHostAddress));
        testOlinkConnection->connectAndLinkObject(sink1);

        // Check that server received link message
        auto expectedLinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::linkMessage(sink1Id));
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        auto msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        REQUIRE(checkMessageInContainer(msgs, expectedLinkMessage));

        // Start test - Close connection with close frame
        server.sendFrame(any_payload, Poco::Net::WebSocket::FRAME_OP_CLOSE);
        Poco::Thread::sleep(30);

        auto propertyName = "property2";
        auto propertyId = ApiGear::ObjectLink::Name::createMemberId(sink1Id, propertyName);
        auto node = testOlinkConnection->node();

        auto sendTenSetPropertyMessages = [&propertyId, node](int startingPropertyValue)
        {
            for (auto number = startingPropertyValue; number < startingPropertyValue +10; number++)
            {
                node->setRemoteProperty(propertyId, { number });
            }
        };
        sendTenSetPropertyMessages(0);
        Poco::Thread::sleep(10); // add some delay between messages series
        auto future1 = std::async(std::launch::async, [sendTenSetPropertyMessages](){sendTenSetPropertyMessages(10);});
        auto future2 = std::async(std::launch::async, [sendTenSetPropertyMessages](){sendTenSetPropertyMessages(20);});
        auto future3 = std::async(std::launch::async, [sendTenSetPropertyMessages](){sendTenSetPropertyMessages(30);});
        Poco::Thread::sleep(11); // add some delay between messages series
        auto future4 = std::async(std::launch::async, [sendTenSetPropertyMessages](){sendTenSetPropertyMessages(40);});
        auto future5 = std::async(std::launch::async, [sendTenSetPropertyMessages](){sendTenSetPropertyMessages(50);});
        auto future6 = std::async(std::launch::async, [sendTenSetPropertyMessages](){sendTenSetPropertyMessages(60);});
        auto future7 = std::async(std::launch::async, [sendTenSetPropertyMessages](){sendTenSetPropertyMessages(70);});

        // wait for re-connection
        Poco::Thread::sleep(501);

        lock.lock();
        // 80 messages and a link message
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 81; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 81);
        // Expect socket re-connects, and sends change property messages and link message
        for (auto i = 0; i< 80; i++)
        {
            auto changePropertyRequest = converter.toString(ApiGear::ObjectLink::Protocol::setPropertyMessage(propertyId, {i}));
            REQUIRE(checkMessageInContainer(msgs, changePropertyRequest));
        }

        REQUIRE(checkMessageInContainer(msgs, expectedLinkMessage));
        auto expectedLinkMesageIndex = getMessageIndex(msgs, expectedLinkMessage);
        // Currently the Link message is sent when connection is back,
        // Most probably all the other messages requested to be sent during disconnected time will be already scheduled to send
        // and Link message will be the last scheduled as a last one.
        // The effect is that there will be some (all?) messages that reach the server before client is linked.
        REQUIRE(expectedLinkMesageIndex > 0);
        REQUIRE(expectedLinkMesageIndex < msgs.size());


        // Cleanup
        REQUIRE_CALL(*sink1, olinkOnRelease());
        testOlinkConnection->disconnectAndUnlink(sink1Id);
        auto expectedUnlinkMessage = converter.toString(ApiGear::ObjectLink::Protocol::unlinkMessage(sink1Id));
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        REQUIRE(checkMessageInContainer(msgs, expectedUnlinkMessage));

        testOlinkConnection->disconnect();
        lock.lock();
        m_messageArrived.wait_for(lock, std::chrono::milliseconds(500), [&server]() {return server.getReceivedFramesNumber() == 1; });
        lock.unlock();
        msgs = server.getReceivedFrames();
        REQUIRE(msgs.size() == 1);
        REQUIRE(msgs[0].flags == Poco::Net::WebSocket::FRAME_OP_CLOSE);
        server.stop();
    }

}
}
