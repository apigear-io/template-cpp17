#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed2/generated/core/test_struct_helper.h"
#include "testbed2/implementation/manyparaminterface.h"
#include "testbed2/generated/nats/manyparaminterfaceclient.h"
#include "testbed2/generated/nats/manyparaminterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::Testbed2;

TEST_CASE("Nats  testbed2 ManyParamInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implManyParamInterface = std::make_shared<Test::Testbed2::ManyParamInterface>();
    auto serviceManyParamInterface = Nats::ManyParamInterfaceService::create(implManyParamInterface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceManyParamInterface]() {return  serviceManyParamInterface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientManyParamInterface = Nats::ManyParamInterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientManyParamInterface]() {return clientManyParamInterface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp1() == test_value);
        REQUIRE(clientManyParamInterface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp2() == test_value);
        REQUIRE(clientManyParamInterface->getProp2() == test_value);
    }
    SECTION("Test setting prop3")
    {
        std::atomic<bool> isprop3Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp3Changed(
        [&isprop3Changed, &m_wait ](auto value){
            isprop3Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp3(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop3Changed]() {return isprop3Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp3() == test_value);
        REQUIRE(clientManyParamInterface->getProp3() == test_value);
    }
    SECTION("Test setting prop4")
    {
        std::atomic<bool> isprop4Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp4Changed(
        [&isprop4Changed, &m_wait ](auto value){
            isprop4Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp4(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop4Changed]() {return isprop4Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp4() == test_value);
        REQUIRE(clientManyParamInterface->getProp4() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](int param1)
        {
            REQUIRE(param1 == 1);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implManyParamInterface->_getPublisher().publishSig1(1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted](int param1, int param2)
        {
            REQUIRE(param1 == 1);
            REQUIRE(param2 == 1);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implManyParamInterface->_getPublisher().publishSig2(1, 1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig3")
    {
        std::atomic<bool> issig3Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig3(
        [&m_wait, &issig3Emitted](int param1, int param2, int param3)
        {
            REQUIRE(param1 == 1);
            REQUIRE(param2 == 1);
            REQUIRE(param3 == 1);
            issig3Emitted  = true;
            m_wait.notify_all();
        });

         implManyParamInterface->_getPublisher().publishSig3(1, 1, 1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig3Emitted ]() {return issig3Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig4")
    {
        std::atomic<bool> issig4Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig4(
        [&m_wait, &issig4Emitted](int param1, int param2, int param3, int param4)
        {
            REQUIRE(param1 == 1);
            REQUIRE(param2 == 1);
            REQUIRE(param3 == 1);
            REQUIRE(param4 == 1);
            issig4Emitted  = true;
            m_wait.notify_all();
        });

         implManyParamInterface->_getPublisher().publishSig4(1, 1, 1, 1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig4Emitted ]() {return issig4Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientManyParamInterface->func1(0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func1Async(0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func1Async(0,
            [&finished, &m_wait](int value)
            {
                REQUIRE(value == 0);
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result = clientManyParamInterface->func2(0, 0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func2Async(0, 0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func2Async(0, 0,
            [&finished, &m_wait](int value)
            {
                REQUIRE(value == 0);
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method func3")
    {
        [[maybe_unused]] auto result = clientManyParamInterface->func3(0, 0, 0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func3 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func3Async(0, 0, 0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func3 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func3Async(0, 0, 0,
            [&finished, &m_wait](int value)
            {
                REQUIRE(value == 0);
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method func4")
    {
        [[maybe_unused]] auto result = clientManyParamInterface->func4(0, 0, 0, 0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func4 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func4Async(0, 0, 0, 0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func4 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func4Async(0, 0, 0, 0,
            [&finished, &m_wait](int value)
            {
                REQUIRE(value == 0);
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }

    serviceManyParamInterface.reset();
    clientManyParamInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
