#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_names/generated/core/test_struct_helper.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/nats/namesclient.h"
#include "tb_names/generated/nats/namesservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbNames;

TEST_CASE("Nats  tb.names NamEs tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implNamEs = std::make_shared<Test::TbNames::NamEs>();
    auto serviceNamEs = Nats::Nam_EsService::create(implNamEs, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceNamEs]() {return  serviceNamEs->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientNamEs = Nats::Nam_EsClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientNamEs]() {return clientNamEs->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting Switch")
    {
        std::atomic<bool> isSwitchChanged = false;
        clientNamEs->_getPublisher().subscribeToSwitchChanged(
        [&isSwitchChanged, &m_wait ](auto value){
            isSwitchChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = true;
        clientNamEs->setSwitch(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isSwitchChanged]() {return isSwitchChanged  == true; }));
        lock.unlock();
        REQUIRE(implNamEs->getSwitch() == test_value);
        REQUIRE(clientNamEs->getSwitch() == test_value);
    }
    SECTION("Test setting SOME_PROPERTY")
    {
        std::atomic<bool> isSOME_PROPERTYChanged = false;
        clientNamEs->_getPublisher().subscribeToSomePropertyChanged(
        [&isSOME_PROPERTYChanged, &m_wait ](auto value){
            isSOME_PROPERTYChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientNamEs->setSomeProperty(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isSOME_PROPERTYChanged]() {return isSOME_PROPERTYChanged  == true; }));
        lock.unlock();
        REQUIRE(implNamEs->getSomeProperty() == test_value);
        REQUIRE(clientNamEs->getSomeProperty() == test_value);
    }
    SECTION("Test setting Some_Poperty2")
    {
        std::atomic<bool> isSome_Poperty2Changed = false;
        clientNamEs->_getPublisher().subscribeToSomePoperty2Changed(
        [&isSome_Poperty2Changed, &m_wait ](auto value){
            isSome_Poperty2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientNamEs->setSomePoperty2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isSome_Poperty2Changed]() {return isSome_Poperty2Changed  == true; }));
        lock.unlock();
        REQUIRE(implNamEs->getSomePoperty2() == test_value);
        REQUIRE(clientNamEs->getSomePoperty2() == test_value);
    }
    SECTION("Test emit SOME_SIGNAL")
    {
        std::atomic<bool> isSOME_SIGNALEmitted = false;

        clientNamEs->_getPublisher().subscribeToSomeSignal(
        [&m_wait, &isSOME_SIGNALEmitted](bool SOME_PARAM)
        {
            REQUIRE(SOME_PARAM == true);
            isSOME_SIGNALEmitted  = true;
            m_wait.notify_all();
        });

         implNamEs->_getPublisher().publishSomeSignal(true);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isSOME_SIGNALEmitted ]() {return isSOME_SIGNALEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit Some_Signal2")
    {
        std::atomic<bool> isSome_Signal2Emitted = false;

        clientNamEs->_getPublisher().subscribeToSomeSignal2(
        [&m_wait, &isSome_Signal2Emitted](bool Some_Param)
        {
            REQUIRE(Some_Param == true);
            isSome_Signal2Emitted  = true;
            m_wait.notify_all();
        });

         implNamEs->_getPublisher().publishSomeSignal2(true);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isSome_Signal2Emitted ]() {return isSome_Signal2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method SOME_FUNCTION")
    {
        clientNamEs->sOME_FUNCTION(false);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method SOME_FUNCTION async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNamEs->sOME_FUNCTIONAsync(false);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        resultFuture.wait();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method SOME_FUNCTION async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNamEs->sOME_FUNCTIONAsync(false,
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
    SECTION("Test method Some_Function2")
    {
        clientNamEs->some_Function2(false);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method Some_Function2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNamEs->some_Function2Async(false);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        resultFuture.wait();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method Some_Function2 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNamEs->some_Function2Async(false,
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

    serviceNamEs.reset();
    clientNamEs.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
