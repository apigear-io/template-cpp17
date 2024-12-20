#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same1/generated/core/test_struct_helper.h"
#include "tb_same1/implementation/sameenum1interface.h"
#include "tb_same1/generated/nats/sameenum1interfaceclient.h"
#include "tb_same1/generated/nats/sameenum1interfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSame1;

TEST_CASE("Nats  tb.same1 SameEnum1Interface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implSameEnum1Interface = std::make_shared<Test::TbSame1::SameEnum1Interface>();
    auto serviceSameEnum1Interface = Nats::SameEnum1InterfaceService::create(implSameEnum1Interface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceSameEnum1Interface]() {return  serviceSameEnum1Interface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientSameEnum1Interface = Nats::SameEnum1InterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientSameEnum1Interface]() {return clientSameEnum1Interface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientSameEnum1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame1::Enum1Enum::value2;
        clientSameEnum1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameEnum1Interface->getProp1() == test_value);
        REQUIRE(clientSameEnum1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;

        clientSameEnum1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](TbSame1::Enum1Enum param1)
        {
            REQUIRE(param1 == TbSame1::Enum1Enum::value2);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameEnum1Interface->_getPublisher().publishSig1(TbSame1::Enum1Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientSameEnum1Interface->func1(TbSame1::Enum1Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum1Interface->func1Async(TbSame1::Enum1Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    serviceSameEnum1Interface.reset();
    clientSameEnum1Interface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
