#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same2/generated/core/test_struct_helper.h"
#include "tb_same2/implementation/samestruct2interface.h"
#include "tb_same2/generated/nats/samestruct2interfaceclient.h"
#include "tb_same2/generated/nats/samestruct2interfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSame2;

TEST_CASE("Nats  tb.same2 SameStruct2Interface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implSameStruct2Interface = std::make_shared<Test::TbSame2::SameStruct2Interface>();
    auto serviceSameStruct2Interface = Nats::SameStruct2InterfaceService::create(implSameStruct2Interface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceSameStruct2Interface]() {return  serviceSameStruct2Interface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientSameStruct2Interface = Nats::SameStruct2InterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientSameStruct2Interface]() {return clientSameStruct2Interface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientSameStruct2Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame2::Struct2();
        TbSame2::fillTestStruct2(test_value);
        clientSameStruct2Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameStruct2Interface->getProp1() == test_value);
        REQUIRE(clientSameStruct2Interface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientSameStruct2Interface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame2::Struct2();
        TbSame2::fillTestStruct2(test_value);
        clientSameStruct2Interface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameStruct2Interface->getProp2() == test_value);
        REQUIRE(clientSameStruct2Interface->getProp2() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = TbSame2::Struct1();
        TbSame2::fillTestStruct1(local_param1_struct);

        clientSameStruct2Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const TbSame2::Struct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameStruct2Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;
        auto local_param1_struct = TbSame2::Struct1();
        TbSame2::fillTestStruct1(local_param1_struct);
        auto local_param2_struct = TbSame2::Struct2();
        TbSame2::fillTestStruct2(local_param2_struct);

        clientSameStruct2Interface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted, &local_param1_struct, &local_param2_struct](const TbSame2::Struct1& param1, const TbSame2::Struct2& param2)
        {
            REQUIRE(param1 ==local_param1_struct);
            REQUIRE(param2 ==local_param2_struct);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implSameStruct2Interface->_getPublisher().publishSig2(local_param1_struct, local_param2_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientSameStruct2Interface->func1(TbSame2::Struct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct2Interface->func1Async(TbSame2::Struct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Struct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result = clientSameStruct2Interface->func2(TbSame2::Struct1(), TbSame2::Struct2());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct2Interface->func2Async(TbSame2::Struct1(), TbSame2::Struct2());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Struct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    serviceSameStruct2Interface.reset();
    clientSameStruct2Interface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
