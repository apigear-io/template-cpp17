#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/mqtt/nosignalsinterfaceclient.h"
#include "tb_simple/generated/mqtt/nosignalsinterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{
#if defined(__SANITIZE_THREAD__)
    int timeout = 10000;//in ms - longer for TSan builds
#elif defined(__has_feature)
#   if __has_feature(thread_sanitizer)
    int timeout = 10000;//in ms - longer for TSan builds
#   else
    int timeout = 1000;//in ms
#   endif
#else
    int timeout = 1000;//in ms
#endif
}

using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("mqtt  tb.simple NoSignalsInterface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("NoSignalsInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("NoSignalsInterfacetestClient");

    auto clientNoSignalsInterface = std::make_shared<Test::TbSimple::MQTT::NoSignalsInterfaceClient>(mqttclient);
    auto implNoSignalsInterface= std::make_shared<Test::TbSimple::NoSignalsInterface>();
    auto serviceNoSignalsInterface = std::make_shared<Test::TbSimple::MQTT::NoSignalsInterfaceService>(implNoSignalsInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceNoSignalsInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceNoSignalsInterface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientNoSignalsInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcVoid async")
    {
        auto resultFuture = clientNoSignalsInterface->funcVoidAsync();
        // The void function only sends request. It does not wait for the actual function on server side to be finished.
    }

    SECTION("Test method funcVoid async with callback")
    {
        auto resultFuture = clientNoSignalsInterface->funcVoidAsync([](){/* you can add a callback, but it will be called right after sending the request. It does not wait for the actual function on server side to be finished. */ });
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result =  clientNoSignalsInterface->funcBool(false);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
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

    SECTION("Test method funcBool async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNoSignalsInterface->funcBoolAsync(false,[&finished, &m_wait](bool value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == false); 
    }

    mqttservice->disconnect();
    mqttclient->disconnect();
    serviceNoSignalsInterface.reset();
    clientNoSignalsInterface.reset();
    mqttservice.reset();
    mqttclient.reset();
}
