#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>
#include <iostream>


#include "tb_same1/generated/core/test_struct_helper.h"
#include "tb_same1/implementation/samestruct1interface.h"
#include "tb_same1/generated/mqtt/samestruct1interfaceclient.h"
#include "tb_same1/generated/mqtt/samestruct1interfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::TbSame1;

TEST_CASE("mqtt  tb.same1 SameStruct1Interface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("SameStruct1InterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("SameStruct1InterfacetestClient");

    auto clientSameStruct1Interface = std::make_shared<Test::TbSame1::MQTT::SameStruct1InterfaceClient>(mqttclient);
    auto implSameStruct1Interface= std::make_shared<Test::TbSame1::SameStruct1Interface>();
    auto serviceSameStruct1Interface = std::make_shared<Test::TbSame1::MQTT::SameStruct1InterfaceService>(implSameStruct1Interface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceSameStruct1Interface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceSameStruct1Interface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientSameStruct1Interface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
    SECTION("Test setting prop1")
    {
        std::cout<<"SameStruct1Interface Test setting prop1" << std::endl;
        std::atomic<bool> isprop1Changed = false;
        clientSameStruct1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame1::Struct1();
        TbSame1::fillTestStruct1(test_value);
        clientSameStruct1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameStruct1Interface->getProp1() == test_value);
        REQUIRE(clientSameStruct1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::cout<<"SameStruct1Interface Test emit sig1" << std::endl;
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = TbSame1::Struct1();
        TbSame1::fillTestStruct1(local_param1_struct);

        clientSameStruct1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const TbSame1::Struct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSameStruct1Interface->_getPublisher().publishSig1(local_param1_struct);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SameStruct1Interface Test emit sig1" << std::endl;
    }
    SECTION("Test method func1")
    {
        std::cout<<"SameStruct1Interface Test method func1" << std::endl;
        [[maybe_unused]] auto result =  clientSameStruct1Interface->func1(TbSame1::Struct1());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func1 async")
    {
        std::cout<<"SameStruct1Interface Test async method func1" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct1Interface->func1Async(TbSame1::Struct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Struct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func1 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct1Interface->func1Async(TbSame1::Struct1(),[&finished, &m_wait](Struct1 value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Struct1()); 
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
    serviceSameStruct1Interface.reset();
    clientSameStruct1Interface.reset();
}
