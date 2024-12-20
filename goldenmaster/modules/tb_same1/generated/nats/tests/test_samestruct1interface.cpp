#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same1/generated/core/test_struct_helper.h"
#include "tb_same1/implementation/samestruct1interface.h"
#include "tb_same1/generated/nats/samestruct1interfaceclient.h"
#include "tb_same1/generated/nats/samestruct1interfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSame1;

TEST_CASE("Nats  tb.same1 SameStruct1Interface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implSameStruct1Interface = std::make_shared<Test::TbSame1::SameStruct1Interface>();
    auto serviceSameStruct1Interface = Nats::SameStruct1InterfaceService::create(implSameStruct1Interface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceSameStruct1Interface]() {return  serviceSameStruct1Interface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientSameStruct1Interface = Nats::SameStruct1InterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientSameStruct1Interface]() {return clientSameStruct1Interface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientSameStruct1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame1::Struct1();
        TbSame1::fillTestStruct1(test_value);
        clientSameStruct1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameStruct1Interface->getProp1() == test_value);
        REQUIRE(clientSameStruct1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = TbSame1::Struct1();
        TbSame1::fillTestStruct1(local_param1_struct);

        clientSameStruct1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const TbSame1::Struct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameStruct1Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientSameStruct1Interface->func1(TbSame1::Struct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct1Interface->func1Async(TbSame1::Struct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Struct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    serviceSameStruct1Interface.reset();
    clientSameStruct1Interface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
