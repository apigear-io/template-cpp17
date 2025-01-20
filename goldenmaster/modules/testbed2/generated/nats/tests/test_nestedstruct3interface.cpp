#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed2/generated/core/test_struct_helper.h"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/nats/nestedstruct3interfaceclient.h"
#include "testbed2/generated/nats/nestedstruct3interfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::Testbed2;

TEST_CASE("Nats  testbed2 NestedStruct3Interface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implNestedStruct3Interface = std::make_shared<Test::Testbed2::NestedStruct3Interface>();
    auto serviceNestedStruct3Interface = Nats::NestedStruct3InterfaceService::create(implNestedStruct3Interface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceNestedStruct3Interface]() {return  serviceNestedStruct3Interface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientNestedStruct3Interface = Nats::NestedStruct3InterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientNestedStruct3Interface]() {return clientNestedStruct3Interface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientNestedStruct3Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(test_value);
        clientNestedStruct3Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct3Interface->getProp1() == test_value);
        REQUIRE(clientNestedStruct3Interface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientNestedStruct3Interface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(test_value);
        clientNestedStruct3Interface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct3Interface->getProp2() == test_value);
        REQUIRE(clientNestedStruct3Interface->getProp2() == test_value);
    }
    SECTION("Test setting prop3")
    {
        std::atomic<bool> isprop3Changed = false;
        clientNestedStruct3Interface->_getPublisher().subscribeToProp3Changed(
        [&isprop3Changed, &m_wait ](auto value){
            isprop3Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct3();
        Testbed2::fillTestNestedStruct3(test_value);
        clientNestedStruct3Interface->setProp3(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop3Changed]() {return isprop3Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct3Interface->getProp3() == test_value);
        REQUIRE(clientNestedStruct3Interface->getProp3() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);

        clientNestedStruct3Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const Testbed2::NestedStruct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct3Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);
        auto local_param2_struct = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(local_param2_struct);

        clientNestedStruct3Interface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted, &local_param1_struct, &local_param2_struct](const Testbed2::NestedStruct1& param1, const Testbed2::NestedStruct2& param2)
        {
            REQUIRE(param1 ==local_param1_struct);
            REQUIRE(param2 ==local_param2_struct);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct3Interface->_getPublisher().publishSig2(local_param1_struct, local_param2_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig3")
    {
        std::atomic<bool> issig3Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);
        auto local_param2_struct = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(local_param2_struct);
        auto local_param3_struct = Testbed2::NestedStruct3();
        Testbed2::fillTestNestedStruct3(local_param3_struct);

        clientNestedStruct3Interface->_getPublisher().subscribeToSig3(
        [&m_wait, &issig3Emitted, &local_param1_struct, &local_param2_struct, &local_param3_struct](const Testbed2::NestedStruct1& param1, const Testbed2::NestedStruct2& param2, const Testbed2::NestedStruct3& param3)
        {
            REQUIRE(param1 ==local_param1_struct);
            REQUIRE(param2 ==local_param2_struct);
            REQUIRE(param3 ==local_param3_struct);
            issig3Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct3Interface->_getPublisher().publishSig3(local_param1_struct, local_param2_struct, local_param3_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig3Emitted ]() {return issig3Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientNestedStruct3Interface->func1(Testbed2::NestedStruct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func1Async(Testbed2::NestedStruct1());
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
        auto resultFuture = clientNestedStruct3Interface->func1Async(Testbed2::NestedStruct1(),
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
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result = clientNestedStruct3Interface->func2(Testbed2::NestedStruct1(), Testbed2::NestedStruct2());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func2Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func2Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2(),
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
    SECTION("Test method func3")
    {
        [[maybe_unused]] auto result = clientNestedStruct3Interface->func3(Testbed2::NestedStruct1(), Testbed2::NestedStruct2(), Testbed2::NestedStruct3());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func3 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func3Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2(), Testbed2::NestedStruct3());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func3 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func3Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2(), Testbed2::NestedStruct3(),
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

    serviceNestedStruct3Interface.reset();
    clientNestedStruct3Interface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
