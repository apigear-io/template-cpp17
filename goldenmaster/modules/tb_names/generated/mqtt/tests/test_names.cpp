#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_names/generated/core/test_struct_helper.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/mqtt/namesclient.h"
#include "tb_names/generated/mqtt/namesservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::TbNames;

TEST_CASE("mqtt  tb.names NamEs tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("NamEstestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("NamEstestClient");

    auto clientNamEs = std::make_shared<Test::TbNames::MQTT::Nam_EsClient>(mqttclient);
    auto implNamEs= std::make_shared<Test::TbNames::NamEs>();
    auto serviceNamEs = std::make_shared<Test::TbNames::MQTT::Nam_EsService>(implNamEs, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceNamEs->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceNamEs->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientNamEs->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_clientConnected = true;
                m_wait.notify_all();
            }
        });

    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_clientConnected]() {return is_clientConnected  == true; });
    lock.unlock();
    REQUIRE(is_clientConnected);
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
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method SOME_FUNCTION async")
    {
        auto resultFuture = clientNamEs->sOME_FUNCTIONAsync(false);
        // The void function only sends request. It does not wait for the actual function on server side to be finished.
    }
    SECTION("Test method Some_Function2")
    {
         clientNamEs->some_Function2(false);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method Some_Function2 async")
    {
        auto resultFuture = clientNamEs->some_Function2Async(false);
        // The void function only sends request. It does not wait for the actual function on server side to be finished.
    }

    std::atomic<bool> serviceDisconnected{ false };
    mqttservice->subscribeToConnectionStatus([&serviceDisconnected, &m_wait](auto boo) {
        if (!boo)
        {
            serviceDisconnected = true;
            m_wait.notify_all();
        }
        
        });

    mqttservice->disconnect();

    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout),
        [&serviceDisconnected]() { return serviceDisconnected == true; });
    lock.unlock();
    REQUIRE(serviceDisconnected);

    std::atomic<bool> clientDisonnected{ false };
    mqttclient->subscribeToConnectionStatus([&clientDisonnected, &m_wait](auto boo) {
        if (!boo)
        {
            clientDisonnected = true;
            m_wait.notify_all();
        }
        });

    mqttclient->disconnect();

    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout),
        [&clientDisonnected]() { return clientDisonnected == true; });
    lock.unlock();
    REQUIRE(clientDisonnected);

    mqttservice.reset();
    mqttclient.reset();
    serviceNamEs.reset();
    clientNamEs.reset();
}
