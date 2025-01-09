#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed2/generated/core/test_struct_helper.h"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/mqtt/nestedstruct3interfaceclient.h"
#include "testbed2/generated/mqtt/nestedstruct3interfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::Testbed2;

TEST_CASE("mqtt  testbed2 NestedStruct3Interface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("NestedStruct3InterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("NestedStruct3InterfacetestClient");

    auto clientNestedStruct3Interface = std::make_shared<Test::Testbed2::MQTT::NestedStruct3InterfaceClient>(mqttclient);
    auto implNestedStruct3Interface= std::make_shared<Test::Testbed2::NestedStruct3Interface>();
    auto serviceNestedStruct3Interface = std::make_shared<Test::Testbed2::MQTT::NestedStruct3InterfaceService>(implNestedStruct3Interface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceNestedStruct3Interface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceNestedStruct3Interface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientNestedStruct3Interface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        std::atomic<bool> isprop1Changed = false;
        clientNestedStruct3Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(test_value);
        clientNestedStruct3Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct3Interface->getProp1() == test_value);
        REQUIRE(clientNestedStruct3Interface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientNestedStruct3Interface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(test_value);
        clientNestedStruct3Interface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct3Interface->getProp2() == test_value);
        REQUIRE(clientNestedStruct3Interface->getProp2() == test_value);
    }
    SECTION("Test setting prop3")
    {
        std::atomic<bool> isprop3Changed = false;
        clientNestedStruct3Interface->_getPublisher().subscribeToProp3Changed(
        [&isprop3Changed, &m_wait ](auto value){
            isprop3Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct3();
        Testbed2::fillTestNestedStruct3(test_value);
        clientNestedStruct3Interface->setProp3(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop3Changed]() {return isprop3Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct3Interface->getProp3() == test_value);
        REQUIRE(clientNestedStruct3Interface->getProp3() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);

        clientNestedStruct3Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const Testbed2::NestedStruct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct3Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);
        auto local_param2_struct = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(local_param2_struct);

        clientNestedStruct3Interface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted, &local_param1_struct, &local_param2_struct](const Testbed2::NestedStruct1& param1, const Testbed2::NestedStruct2& param2)
        {
            REQUIRE(param1 ==local_param1_struct);
            REQUIRE(param2 ==local_param2_struct);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct3Interface->_getPublisher().publishSig2(local_param1_struct, local_param2_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig3")
    {
        std::atomic<bool> issig3Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);
        auto local_param2_struct = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(local_param2_struct);
        auto local_param3_struct = Testbed2::NestedStruct3();
        Testbed2::fillTestNestedStruct3(local_param3_struct);

        clientNestedStruct3Interface->_getPublisher().subscribeToSig3(
        [&m_wait, &issig3Emitted, &local_param1_struct, &local_param2_struct, &local_param3_struct](const Testbed2::NestedStruct1& param1, const Testbed2::NestedStruct2& param2, const Testbed2::NestedStruct3& param3)
        {
            REQUIRE(param1 ==local_param1_struct);
            REQUIRE(param2 ==local_param2_struct);
            REQUIRE(param3 ==local_param3_struct);
            issig3Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct3Interface->_getPublisher().publishSig3(local_param1_struct, local_param2_struct, local_param3_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig3Emitted ]() {return issig3Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result =  clientNestedStruct3Interface->func1(Testbed2::NestedStruct1());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func1Async(Testbed2::NestedStruct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result =  clientNestedStruct3Interface->func2(Testbed2::NestedStruct1(), Testbed2::NestedStruct2());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func2Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func3")
    {
        [[maybe_unused]] auto result =  clientNestedStruct3Interface->func3(Testbed2::NestedStruct1(), Testbed2::NestedStruct2(), Testbed2::NestedStruct3());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func3 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct3Interface->func3Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2(), Testbed2::NestedStruct3());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
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
    serviceNestedStruct3Interface.reset();
    clientNestedStruct3Interface.reset();
}
