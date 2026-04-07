#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/mqtt/voidinterfaceclient.h"
#include "tb_simple/generated/mqtt/voidinterfaceservice.h"


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

TEST_CASE("mqtt  tb.simple VoidInterface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("VoidInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("VoidInterfacetestClient");

    auto clientVoidInterface = std::make_shared<Test::TbSimple::MQTT::VoidInterfaceClient>(mqttclient);
    auto implVoidInterface= std::make_shared<Test::TbSimple::VoidInterface>();
    auto serviceVoidInterface = std::make_shared<Test::TbSimple::MQTT::VoidInterfaceService>(implVoidInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceVoidInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceVoidInterface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientVoidInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcVoid async")
    {
        auto resultFuture = clientVoidInterface->funcVoidAsync();
        // The void function only sends request. It does not wait for the actual function on server side to be finished.
    }

    SECTION("Test method funcVoid async with callback")
    {
        auto resultFuture = clientVoidInterface->funcVoidAsync([](){/* you can add a callback, but it will be called right after sending the request. It does not wait for the actual function on server side to be finished. */ });
    }

    mqttservice->disconnect();
    mqttclient->disconnect();
    serviceVoidInterface.reset();
    clientVoidInterface.reset();
    mqttservice.reset();
    mqttclient.reset();
}
