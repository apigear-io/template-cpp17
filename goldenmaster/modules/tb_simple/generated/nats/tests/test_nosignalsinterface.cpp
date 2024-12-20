#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/nats/nosignalsinterfaceclient.h"
#include "tb_simple/generated/nats/nosignalsinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("Nats  tb.simple NoSignalsInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implNoSignalsInterface = std::make_shared<Test::TbSimple::NoSignalsInterface>();
    auto serviceNoSignalsInterface = Nats::NoSignalsInterfaceService::create(implNoSignalsInterface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceNoSignalsInterface]() {return  serviceNoSignalsInterface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientNoSignalsInterface = Nats::NoSignalsInterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientNoSignalsInterface]() {return clientNoSignalsInterface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting propBool")
    {
        std::atomic<bool> ispropBoolChanged = false;
        clientNoSignalsInterface->_getPublisher().subscribeToPropBoolChanged(
        [&ispropBoolChanged, &m_wait ](auto value){
            ispropBoolChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = true;
        clientNoSignalsInterface->setPropBool(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropBoolChanged]() {return ispropBoolChanged  == true; }));
        lock.unlock();
        REQUIRE(implNoSignalsInterface->getPropBool() == test_value);
        REQUIRE(clientNoSignalsInterface->getPropBool() == test_value);
    }
    SECTION("Test setting propInt")
    {
        std::atomic<bool> ispropIntChanged = false;
        clientNoSignalsInterface->_getPublisher().subscribeToPropIntChanged(
        [&ispropIntChanged, &m_wait ](auto value){
            ispropIntChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientNoSignalsInterface->setPropInt(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntChanged]() {return ispropIntChanged  == true; }));
        lock.unlock();
        REQUIRE(implNoSignalsInterface->getPropInt() == test_value);
        REQUIRE(clientNoSignalsInterface->getPropInt() == test_value);
    }
    SECTION("Test method funcVoid")
    {
        clientNoSignalsInterface->funcVoid();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcVoid async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNoSignalsInterface->funcVoidAsync();
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        resultFuture.wait();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result = clientNoSignalsInterface->funcBool(false);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNoSignalsInterface->funcBoolAsync(false);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == false); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    serviceNoSignalsInterface.reset();
    clientNoSignalsInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
