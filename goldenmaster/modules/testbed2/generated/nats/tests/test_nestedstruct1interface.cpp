#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed2/generated/core/test_struct_helper.h"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "testbed2/generated/nats/nestedstruct1interfaceclient.h"
#include "testbed2/generated/nats/nestedstruct1interfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::Testbed2;

TEST_CASE("Nats  testbed2 NestedStruct1Interface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implNestedStruct1Interface = std::make_shared<Test::Testbed2::NestedStruct1Interface>();
    auto serviceNestedStruct1Interface = Nats::NestedStruct1InterfaceService::create(implNestedStruct1Interface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceNestedStruct1Interface]() {return  serviceNestedStruct1Interface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientNestedStruct1Interface = Nats::NestedStruct1InterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientNestedStruct1Interface]() {return clientNestedStruct1Interface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientNestedStruct1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(test_value);
        clientNestedStruct1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct1Interface->getProp1() == test_value);
        REQUIRE(clientNestedStruct1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);

        clientNestedStruct1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const Testbed2::NestedStruct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct1Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientNestedStruct1Interface->func1(Testbed2::NestedStruct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct1Interface->func1Async(Testbed2::NestedStruct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct1Interface->func1Async(Testbed2::NestedStruct1(),
            [&finished, &m_wait](NestedStruct1 value)
            {
                REQUIRE(value == Testbed2::NestedStruct1());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }

    serviceNestedStruct1Interface.reset();
    clientNestedStruct1Interface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
