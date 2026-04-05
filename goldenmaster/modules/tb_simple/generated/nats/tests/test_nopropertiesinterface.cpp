#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/nats/nopropertiesinterfaceclient.h"
#include "tb_simple/generated/nats/nopropertiesinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("Nats  tb.simple NoPropertiesInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();
    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implNoPropertiesInterface = std::make_shared<Test::TbSimple::NoPropertiesInterface>();
    auto serviceNoPropertiesInterface = Nats::NoPropertiesInterfaceService::create(implNoPropertiesInterface, service);

    std::atomic<bool> is_serviceReady{ false };
    serviceNoPropertiesInterface->_subscribeForIsReady([&is_serviceReady, &m_wait](auto is_ready)
        {
            if (is_ready)
            {
                is_serviceReady = true;
                m_wait.notify_all();
            }
        });
    if (serviceNoPropertiesInterface->_is_ready())
    {
        is_serviceReady = true;
    }
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceReady]() {return is_serviceReady == true; }));
    lock.unlock();
    service->flush();

    auto clientNoPropertiesInterface = Nats::NoPropertiesInterfaceClient::create(client);

    std::atomic<bool> is_clientReady{ false };
    clientNoPropertiesInterface->_subscribeForIsReady([&is_clientReady, &m_wait](auto is_ready)
        {
            if (is_ready)
            {
                is_clientReady = true;
                m_wait.notify_all();
            }
        });
    if (clientNoPropertiesInterface->_is_ready())
    {
        is_clientReady = true;
    }
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_clientReady]() {return is_clientReady == true; }));
    lock.unlock();
    client->flush();
    SECTION("Test emit sigVoid")
    {
        std::atomic<bool> issigVoidEmitted = false;

        clientNoPropertiesInterface->_getPublisher().subscribeToSigVoid(
        [&m_wait, &issigVoidEmitted]()
        {
            issigVoidEmitted  = true;
            m_wait.notify_all();
        });

         implNoPropertiesInterface->_getPublisher().publishSigVoid();
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigVoidEmitted ]() {return issigVoidEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigBool")
    {
        std::atomic<bool> issigBoolEmitted = false;

        clientNoPropertiesInterface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted](bool paramBool)
        {
            REQUIRE(paramBool == true);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         implNoPropertiesInterface->_getPublisher().publishSigBool(true);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcVoid")
    {
        clientNoPropertiesInterface->funcVoid();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcVoid async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNoPropertiesInterface->funcVoidAsync();
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        resultFuture.wait();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcVoid async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNoPropertiesInterface->funcVoidAsync(
            [&finished, &m_wait]()
            { 
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result = clientNoPropertiesInterface->funcBool(false);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNoPropertiesInterface->funcBoolAsync(false);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == false); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNoPropertiesInterface->funcBoolAsync(false,
            [&finished, &m_wait](bool value)
            {
                REQUIRE(value == false);
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }

    serviceNoPropertiesInterface.reset();
    clientNoPropertiesInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
