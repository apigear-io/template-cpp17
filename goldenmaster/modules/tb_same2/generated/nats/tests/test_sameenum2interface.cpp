#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same2/generated/core/test_struct_helper.h"
#include "tb_same2/implementation/sameenum2interface.h"
#include "tb_same2/generated/nats/sameenum2interfaceclient.h"
#include "tb_same2/generated/nats/sameenum2interfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSame2;

TEST_CASE("Nats  tb.same2 SameEnum2Interface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implSameEnum2Interface = std::make_shared<Test::TbSame2::SameEnum2Interface>();
    auto serviceSameEnum2Interface = Nats::SameEnum2InterfaceService::create(implSameEnum2Interface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceSameEnum2Interface]() {return  serviceSameEnum2Interface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientSameEnum2Interface = Nats::SameEnum2InterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientSameEnum2Interface]() {return clientSameEnum2Interface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientSameEnum2Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame2::Enum1Enum::value2;
        clientSameEnum2Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameEnum2Interface->getProp1() == test_value);
        REQUIRE(clientSameEnum2Interface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientSameEnum2Interface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame2::Enum2Enum::value2;
        clientSameEnum2Interface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameEnum2Interface->getProp2() == test_value);
        REQUIRE(clientSameEnum2Interface->getProp2() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;

        clientSameEnum2Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](TbSame2::Enum1Enum param1)
        {
            REQUIRE(param1 == TbSame2::Enum1Enum::value2);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameEnum2Interface->_getPublisher().publishSig1(TbSame2::Enum1Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;

        clientSameEnum2Interface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted](TbSame2::Enum1Enum param1, TbSame2::Enum2Enum param2)
        {
            REQUIRE(param1 == TbSame2::Enum1Enum::value2);
            REQUIRE(param2 == TbSame2::Enum2Enum::value2);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implSameEnum2Interface->_getPublisher().publishSig2(TbSame2::Enum1Enum::value2, TbSame2::Enum2Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientSameEnum2Interface->func1(TbSame2::Enum1Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum2Interface->func1Async(TbSame2::Enum1Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result = clientSameEnum2Interface->func2(TbSame2::Enum1Enum::value1, TbSame2::Enum2Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum2Interface->func2Async(TbSame2::Enum1Enum::value1, TbSame2::Enum2Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    serviceSameEnum2Interface.reset();
    clientSameEnum2Interface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
