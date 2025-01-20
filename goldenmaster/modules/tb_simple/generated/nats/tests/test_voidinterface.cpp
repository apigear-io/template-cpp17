#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/nats/voidinterfaceclient.h"
#include "tb_simple/generated/nats/voidinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("Nats  tb.simple VoidInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implVoidInterface = std::make_shared<Test::TbSimple::VoidInterface>();
    auto serviceVoidInterface = Nats::VoidInterfaceService::create(implVoidInterface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceVoidInterface]() {return  serviceVoidInterface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientVoidInterface = Nats::VoidInterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientVoidInterface]() {return clientVoidInterface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test emit sigVoid")
    {
        std::atomic<bool> issigVoidEmitted = false;

        clientVoidInterface->_getPublisher().subscribeToSigVoid(
        [&m_wait, &issigVoidEmitted]()
        {
            issigVoidEmitted  = true;
            m_wait.notify_all();
        });

         implVoidInterface->_getPublisher().publishSigVoid();
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigVoidEmitted ]() {return issigVoidEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcVoid")
    {
        clientVoidInterface->funcVoid();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcVoid async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientVoidInterface->funcVoidAsync();
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
        auto resultFuture = clientVoidInterface->funcVoidAsync(
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

    serviceVoidInterface.reset();
    clientVoidInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
