#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>
#include <iostream>


#include "tb_same2/generated/core/test_struct_helper.h"
#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/mqtt/sameenum1interfaceclient.h"
#include "tb_same2/generated/mqtt/sameenum1interfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::TbSame2;

TEST_CASE("mqtt  tb.same2 SameEnum1Interface tests")
{
    std::cout<<"starting set up connection" << std::endl;
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("SameEnum1InterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("SameEnum1InterfacetestClient");

    auto clientSameEnum1Interface = std::make_shared<Test::TbSame2::MQTT::SameEnum1InterfaceClient>(mqttclient);
    auto implSameEnum1Interface= std::make_shared<Test::TbSame2::SameEnum1Interface>();
    auto serviceSameEnum1Interface = std::make_shared<Test::TbSame2::MQTT::SameEnum1InterfaceService>(implSameEnum1Interface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceSameEnum1Interface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceSameEnum1Interface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
    std::cout<<"service connected" << std::endl;
 
    std::atomic<bool> is_clientConnected{ false };
    clientSameEnum1Interface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
    std::cout<<"client connected" << std::endl;
  std::cout<<"all set up" << std::endl;
    SECTION("Test setting prop1")
    {
        std::cout<<"SameEnum1Interface Test setting prop1" << std::endl;
        std::atomic<bool> isprop1Changed = false;
        clientSameEnum1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame2::Enum1Enum::value2;
        clientSameEnum1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameEnum1Interface->getProp1() == test_value);
        REQUIRE(clientSameEnum1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::cout<<"SameEnum1Interface Test emit sig1" << std::endl;
        std::atomic<bool> issig1Emitted = false;

        clientSameEnum1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](TbSame2::Enum1Enum param1)
        {
            REQUIRE(param1 == TbSame2::Enum1Enum::value2);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSameEnum1Interface->_getPublisher().publishSig1(TbSame2::Enum1Enum::value2);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SameEnum1Interface Test emit sig1" << std::endl;
    }
    SECTION("Test method func1")
    {
        std::cout<<"SameEnum1Interface Test method func1" << std::endl;
        [[maybe_unused]] auto result =  clientSameEnum1Interface->func1(TbSame2::Enum1Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func1 async")
    {
        std::cout<<"SameEnum1Interface Test async method func1" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum1Interface->func1Async(TbSame2::Enum1Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func1 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum1Interface->func1Async(TbSame2::Enum1Enum::value1,[&finished, &m_wait](Enum1Enum value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Enum1Enum::value1); 
    }
    std::cout<<"start teardown" << std::endl;
    std::atomic<bool> serviceDisconnected{ false };
    mqttservice->subscribeToConnectionStatus([&serviceDisconnected, &m_wait](auto boo) {
        if (!boo)
        {
            serviceDisconnected = true;
            m_wait.notify_all();
        }
        
        });

    mqttservice->disconnect();
    std::cout<<"requested service disconnected" << std::endl;
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout),
        [&serviceDisconnected]() { return serviceDisconnected == true; });
    lock.unlock();
    REQUIRE(serviceDisconnected);
    std::cout<<"service disconnected" << std::endl;
    std::atomic<bool> clientDisonnected{ false };
    mqttclient->subscribeToConnectionStatus([&clientDisonnected, &m_wait](auto boo) {
        if (!boo)
        {
            clientDisonnected = true;
            m_wait.notify_all();
        }
        });

    mqttclient->disconnect();
    std::cout<<"requested client disconnected" << std::endl;
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout),
        [&clientDisonnected]() { return clientDisonnected == true; });
    lock.unlock();
    REQUIRE(clientDisonnected);
    std::cout<<"client disconnected" << std::endl;

    mqttservice.reset();
    mqttclient.reset();
    serviceSameEnum1Interface.reset();
    clientSameEnum1Interface.reset();
    std::cout<<"all ptrs reset, should finish test" << std::endl;
}
