#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/emptyinterface.h"
#include "tb_simple/generated/mqtt/emptyinterfaceclient.h"
#include "tb_simple/generated/mqtt/emptyinterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("mqtt  tb.simple EmptyInterface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("EmptyInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("EmptyInterfacetestClient");

    auto clientEmptyInterface = std::make_shared<Test::TbSimple::MQTT::EmptyInterfaceClient>(mqttclient);
    auto implEmptyInterface= std::make_shared<Test::TbSimple::EmptyInterface>();
    auto serviceEmptyInterface = std::make_shared<Test::TbSimple::MQTT::EmptyInterfaceService>(implEmptyInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceEmptyInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceEmptyInterface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientEmptyInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
    serviceEmptyInterface.reset();
    clientEmptyInterface.reset();
}
