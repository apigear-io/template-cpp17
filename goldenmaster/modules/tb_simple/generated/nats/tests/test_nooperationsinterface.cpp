#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/nooperationsinterface.h"
#include "tb_simple/generated/nats/nooperationsinterfaceclient.h"
#include "tb_simple/generated/nats/nooperationsinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("Nats  tb.simple NoOperationsInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();
    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implNoOperationsInterface = std::make_shared<Test::TbSimple::NoOperationsInterface>();
    auto serviceNoOperationsInterface = Nats::NoOperationsInterfaceService::create(implNoOperationsInterface, service);

    std::atomic<bool> is_serviceReady{ false };
    serviceNoOperationsInterface->_subscribeForIsReady([&is_serviceReady, &m_wait](auto is_ready)
        {
            if (is_ready)
            {
                is_serviceReady = true;
                m_wait.notify_all();
            }
        });
    if (serviceNoOperationsInterface->_is_ready())
    {
        is_serviceReady = true;
    }
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceReady]() {return is_serviceReady == true; }));
    lock.unlock();
    service->flush();

    auto clientNoOperationsInterface = Nats::NoOperationsInterfaceClient::create(client);

    std::atomic<bool> is_clientReady{ false };
    clientNoOperationsInterface->_subscribeForIsReady([&is_clientReady, &m_wait](auto is_ready)
        {
            if (is_ready)
            {
                is_clientReady = true;
                m_wait.notify_all();
            }
        });
    if (clientNoOperationsInterface->_is_ready())
    {
        is_clientReady = true;
    }
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_clientReady]() {return is_clientReady == true; }));
    lock.unlock();
    client->flush();
    SECTION("Test setting propBool")
    {
        std::atomic<bool> ispropBoolChanged = false;
        clientNoOperationsInterface->_getPublisher().subscribeToPropBoolChanged(
        [&ispropBoolChanged, &m_wait ](auto value){
            ispropBoolChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = true;
        clientNoOperationsInterface->setPropBool(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropBoolChanged]() {return ispropBoolChanged  == true; }));
        lock.unlock();
        REQUIRE(implNoOperationsInterface->getPropBool() == test_value);
        REQUIRE(clientNoOperationsInterface->getPropBool() == test_value);
    }
    SECTION("Test setting propInt")
    {
        std::atomic<bool> ispropIntChanged = false;
        clientNoOperationsInterface->_getPublisher().subscribeToPropIntChanged(
        [&ispropIntChanged, &m_wait ](auto value){
            ispropIntChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientNoOperationsInterface->setPropInt(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntChanged]() {return ispropIntChanged  == true; }));
        lock.unlock();
        REQUIRE(implNoOperationsInterface->getPropInt() == test_value);
        REQUIRE(clientNoOperationsInterface->getPropInt() == test_value);
    }
    SECTION("Test emit sigVoid")
    {
        std::atomic<bool> issigVoidEmitted = false;

        clientNoOperationsInterface->_getPublisher().subscribeToSigVoid(
        [&m_wait, &issigVoidEmitted]()
        {
            issigVoidEmitted  = true;
            m_wait.notify_all();
        });

         implNoOperationsInterface->_getPublisher().publishSigVoid();
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigVoidEmitted ]() {return issigVoidEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigBool")
    {
        std::atomic<bool> issigBoolEmitted = false;

        clientNoOperationsInterface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted](bool paramBool)
        {
            REQUIRE(paramBool == true);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         implNoOperationsInterface->_getPublisher().publishSigBool(true);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
    }

    serviceNoOperationsInterface.reset();
    clientNoOperationsInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
