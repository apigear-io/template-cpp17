#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>
#include <iostream>


#include "testbed1/generated/core/test_struct_helper.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/mqtt/structarrayinterfaceclient.h"
#include "testbed1/generated/mqtt/structarrayinterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::Testbed1;

TEST_CASE("mqtt  testbed1 StructArrayInterface tests")
{
    std::cout<<"starting set up connection" << std::endl;
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("StructArrayInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("StructArrayInterfacetestClient");

    auto clientStructArrayInterface = std::make_shared<Test::Testbed1::MQTT::StructArrayInterfaceClient>(mqttclient);
    auto implStructArrayInterface= std::make_shared<Test::Testbed1::StructArrayInterface>();
    auto serviceStructArrayInterface = std::make_shared<Test::Testbed1::MQTT::StructArrayInterfaceService>(implStructArrayInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceStructArrayInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceStructArrayInterface->_is_ready() == true)
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
    clientStructArrayInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
    SECTION("Test setting propBool")
    {
        std::cout<<"StructArrayInterface Test setting propBool" << std::endl;
        std::atomic<bool> ispropBoolChanged = false;
        clientStructArrayInterface->_getPublisher().subscribeToPropBoolChanged(
        [&ispropBoolChanged, &m_wait ](auto value){
            ispropBoolChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<Testbed1::StructBool>();
        auto element = Testbed1::StructBool();
        Testbed1::fillTestStructBool(element);
        test_value.push_back(element);
        clientStructArrayInterface->setPropBool(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropBoolChanged]() {return ispropBoolChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayInterface->getPropBool() == test_value);
        REQUIRE(clientStructArrayInterface->getPropBool() == test_value);
    }
    SECTION("Test setting propInt")
    {
        std::cout<<"StructArrayInterface Test setting propInt" << std::endl;
        std::atomic<bool> ispropIntChanged = false;
        clientStructArrayInterface->_getPublisher().subscribeToPropIntChanged(
        [&ispropIntChanged, &m_wait ](auto value){
            ispropIntChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<Testbed1::StructInt>();
        auto element = Testbed1::StructInt();
        Testbed1::fillTestStructInt(element);
        test_value.push_back(element);
        clientStructArrayInterface->setPropInt(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntChanged]() {return ispropIntChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayInterface->getPropInt() == test_value);
        REQUIRE(clientStructArrayInterface->getPropInt() == test_value);
    }
    SECTION("Test setting propFloat")
    {
        std::cout<<"StructArrayInterface Test setting propFloat" << std::endl;
        std::atomic<bool> ispropFloatChanged = false;
        clientStructArrayInterface->_getPublisher().subscribeToPropFloatChanged(
        [&ispropFloatChanged, &m_wait ](auto value){
            ispropFloatChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<Testbed1::StructFloat>();
        auto element = Testbed1::StructFloat();
        Testbed1::fillTestStructFloat(element);
        test_value.push_back(element);
        clientStructArrayInterface->setPropFloat(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloatChanged]() {return ispropFloatChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayInterface->getPropFloat() == test_value);
        REQUIRE(clientStructArrayInterface->getPropFloat() == test_value);
    }
    SECTION("Test setting propString")
    {
        std::cout<<"StructArrayInterface Test setting propString" << std::endl;
        std::atomic<bool> ispropStringChanged = false;
        clientStructArrayInterface->_getPublisher().subscribeToPropStringChanged(
        [&ispropStringChanged, &m_wait ](auto value){
            ispropStringChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<Testbed1::StructString>();
        auto element = Testbed1::StructString();
        Testbed1::fillTestStructString(element);
        test_value.push_back(element);
        clientStructArrayInterface->setPropString(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropStringChanged]() {return ispropStringChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayInterface->getPropString() == test_value);
        REQUIRE(clientStructArrayInterface->getPropString() == test_value);
    }
    SECTION("Test emit sigBool")
    {
        std::cout<<"StructArrayInterface Test emit sigBool" << std::endl;
        std::atomic<bool> issigBoolEmitted = false;
        auto local_param_bool_array = std::list<Testbed1::StructBool>();
        auto element_paramBool = Testbed1::StructBool();
        Testbed1::fillTestStructBool(element_paramBool);
        local_param_bool_array.push_back(element_paramBool);

        clientStructArrayInterface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted, &local_param_bool_array](const std::list<Testbed1::StructBool>& paramBool)
        {
            REQUIRE(paramBool == local_param_bool_array);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implStructArrayInterface->_getPublisher().publishSigBool(local_param_bool_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed StructArrayInterface Test emit sigBool" << std::endl;
    }
    SECTION("Test emit sigInt")
    {
        std::cout<<"StructArrayInterface Test emit sigInt" << std::endl;
        std::atomic<bool> issigIntEmitted = false;
        auto local_param_int_array = std::list<Testbed1::StructInt>();
        auto element_paramInt = Testbed1::StructInt();
        Testbed1::fillTestStructInt(element_paramInt);
        local_param_int_array.push_back(element_paramInt);

        clientStructArrayInterface->_getPublisher().subscribeToSigInt(
        [&m_wait, &issigIntEmitted, &local_param_int_array](const std::list<Testbed1::StructInt>& paramInt)
        {
            REQUIRE(paramInt == local_param_int_array);
            issigIntEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implStructArrayInterface->_getPublisher().publishSigInt(local_param_int_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed StructArrayInterface Test emit sigInt" << std::endl;
    }
    SECTION("Test emit sigFloat")
    {
        std::cout<<"StructArrayInterface Test emit sigFloat" << std::endl;
        std::atomic<bool> issigFloatEmitted = false;
        auto local_param_float_array = std::list<Testbed1::StructFloat>();
        auto element_paramFloat = Testbed1::StructFloat();
        Testbed1::fillTestStructFloat(element_paramFloat);
        local_param_float_array.push_back(element_paramFloat);

        clientStructArrayInterface->_getPublisher().subscribeToSigFloat(
        [&m_wait, &issigFloatEmitted, &local_param_float_array](const std::list<Testbed1::StructFloat>& paramFloat)
        {
            REQUIRE(paramFloat == local_param_float_array);
            issigFloatEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implStructArrayInterface->_getPublisher().publishSigFloat(local_param_float_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed StructArrayInterface Test emit sigFloat" << std::endl;
    }
    SECTION("Test emit sigString")
    {
        std::cout<<"StructArrayInterface Test emit sigString" << std::endl;
        std::atomic<bool> issigStringEmitted = false;
        auto local_param_string_array = std::list<Testbed1::StructString>();
        auto element_paramString = Testbed1::StructString();
        Testbed1::fillTestStructString(element_paramString);
        local_param_string_array.push_back(element_paramString);

        clientStructArrayInterface->_getPublisher().subscribeToSigString(
        [&m_wait, &issigStringEmitted, &local_param_string_array](const std::list<Testbed1::StructString>& paramString)
        {
            REQUIRE(paramString == local_param_string_array);
            issigStringEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implStructArrayInterface->_getPublisher().publishSigString(local_param_string_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed StructArrayInterface Test emit sigString" << std::endl;
    }
    SECTION("Test method funcBool")
    {
        std::cout<<"StructArrayInterface Test method funcBool" << std::endl;
        [[maybe_unused]] auto result =  clientStructArrayInterface->funcBool(std::list<Testbed1::StructBool>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcBool async")
    {
        std::cout<<"StructArrayInterface Test async method funcBool" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcBoolAsync(std::list<Testbed1::StructBool>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructBool>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcBool async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcBoolAsync(std::list<Testbed1::StructBool>(),[&finished, &m_wait](std::list<StructBool> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructBool>()); 
    }
    SECTION("Test method funcInt")
    {
        std::cout<<"StructArrayInterface Test method funcInt" << std::endl;
        [[maybe_unused]] auto result =  clientStructArrayInterface->funcInt(std::list<Testbed1::StructInt>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt async")
    {
        std::cout<<"StructArrayInterface Test async method funcInt" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcIntAsync(std::list<Testbed1::StructInt>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructInt>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcIntAsync(std::list<Testbed1::StructInt>(),[&finished, &m_wait](std::list<StructInt> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructInt>()); 
    }
    SECTION("Test method funcFloat")
    {
        std::cout<<"StructArrayInterface Test method funcFloat" << std::endl;
        [[maybe_unused]] auto result =  clientStructArrayInterface->funcFloat(std::list<Testbed1::StructFloat>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat async")
    {
        std::cout<<"StructArrayInterface Test async method funcFloat" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcFloatAsync(std::list<Testbed1::StructFloat>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructFloat>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcFloatAsync(std::list<Testbed1::StructFloat>(),[&finished, &m_wait](std::list<StructFloat> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructFloat>()); 
    }
    SECTION("Test method funcString")
    {
        std::cout<<"StructArrayInterface Test method funcString" << std::endl;
        [[maybe_unused]] auto result =  clientStructArrayInterface->funcString(std::list<Testbed1::StructString>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcString async")
    {
        std::cout<<"StructArrayInterface Test async method funcString" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcStringAsync(std::list<Testbed1::StructString>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructString>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcString async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcStringAsync(std::list<Testbed1::StructString>(),[&finished, &m_wait](std::list<StructString> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructString>()); 
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
    serviceStructArrayInterface.reset();
    clientStructArrayInterface.reset();
    std::cout<<"all ptrs reset, should finish test" << std::endl;
}
