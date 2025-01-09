#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed1/generated/core/test_struct_helper.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/mqtt/structinterfaceclient.h"
#include "testbed1/generated/mqtt/structinterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::Testbed1;

TEST_CASE("mqtt  testbed1 StructInterface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("StructInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("StructInterfacetestClient");

    auto clientStructInterface = std::make_shared<Test::Testbed1::MQTT::StructInterfaceClient>(mqttclient);
    auto implStructInterface= std::make_shared<Test::Testbed1::StructInterface>();
    auto serviceStructInterface = std::make_shared<Test::Testbed1::MQTT::StructInterfaceService>(implStructInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceStructInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceStructInterface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientStructInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        clientStructInterface->_getPublisher().subscribeToPropBoolChanged(
        [&ispropBoolChanged, &m_wait ](auto value){
            ispropBoolChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructBool();
        Testbed1::fillTestStructBool(test_value);
        clientStructInterface->setPropBool(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropBoolChanged]() {return ispropBoolChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructInterface->getPropBool() == test_value);
        REQUIRE(clientStructInterface->getPropBool() == test_value);
    }
    SECTION("Test setting propInt")
    {
        std::atomic<bool> ispropIntChanged = false;
        clientStructInterface->_getPublisher().subscribeToPropIntChanged(
        [&ispropIntChanged, &m_wait ](auto value){
            ispropIntChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructInt();
        Testbed1::fillTestStructInt(test_value);
        clientStructInterface->setPropInt(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntChanged]() {return ispropIntChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructInterface->getPropInt() == test_value);
        REQUIRE(clientStructInterface->getPropInt() == test_value);
    }
    SECTION("Test setting propFloat")
    {
        std::atomic<bool> ispropFloatChanged = false;
        clientStructInterface->_getPublisher().subscribeToPropFloatChanged(
        [&ispropFloatChanged, &m_wait ](auto value){
            ispropFloatChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructFloat();
        Testbed1::fillTestStructFloat(test_value);
        clientStructInterface->setPropFloat(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloatChanged]() {return ispropFloatChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructInterface->getPropFloat() == test_value);
        REQUIRE(clientStructInterface->getPropFloat() == test_value);
    }
    SECTION("Test setting propString")
    {
        std::atomic<bool> ispropStringChanged = false;
        clientStructInterface->_getPublisher().subscribeToPropStringChanged(
        [&ispropStringChanged, &m_wait ](auto value){
            ispropStringChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructString();
        Testbed1::fillTestStructString(test_value);
        clientStructInterface->setPropString(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropStringChanged]() {return ispropStringChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructInterface->getPropString() == test_value);
        REQUIRE(clientStructInterface->getPropString() == test_value);
    }
    SECTION("Test emit sigBool")
    {
        std::atomic<bool> issigBoolEmitted = false;
        auto local_param_bool_struct = Testbed1::StructBool();
        Testbed1::fillTestStructBool(local_param_bool_struct);

        clientStructInterface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted, &local_param_bool_struct](const Testbed1::StructBool& paramBool)
        {
            REQUIRE(paramBool ==local_param_bool_struct);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         implStructInterface->_getPublisher().publishSigBool(local_param_bool_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt")
    {
        std::atomic<bool> issigIntEmitted = false;
        auto local_param_int_struct = Testbed1::StructInt();
        Testbed1::fillTestStructInt(local_param_int_struct);

        clientStructInterface->_getPublisher().subscribeToSigInt(
        [&m_wait, &issigIntEmitted, &local_param_int_struct](const Testbed1::StructInt& paramInt)
        {
            REQUIRE(paramInt ==local_param_int_struct);
            issigIntEmitted  = true;
            m_wait.notify_all();
        });

         implStructInterface->_getPublisher().publishSigInt(local_param_int_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat")
    {
        std::atomic<bool> issigFloatEmitted = false;
        auto local_param_float_struct = Testbed1::StructFloat();
        Testbed1::fillTestStructFloat(local_param_float_struct);

        clientStructInterface->_getPublisher().subscribeToSigFloat(
        [&m_wait, &issigFloatEmitted, &local_param_float_struct](const Testbed1::StructFloat& paramFloat)
        {
            REQUIRE(paramFloat ==local_param_float_struct);
            issigFloatEmitted  = true;
            m_wait.notify_all();
        });

         implStructInterface->_getPublisher().publishSigFloat(local_param_float_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigString")
    {
        std::atomic<bool> issigStringEmitted = false;
        auto local_param_string_struct = Testbed1::StructString();
        Testbed1::fillTestStructString(local_param_string_struct);

        clientStructInterface->_getPublisher().subscribeToSigString(
        [&m_wait, &issigStringEmitted, &local_param_string_struct](const Testbed1::StructString& paramString)
        {
            REQUIRE(paramString ==local_param_string_struct);
            issigStringEmitted  = true;
            m_wait.notify_all();
        });

         implStructInterface->_getPublisher().publishSigString(local_param_string_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result =  clientStructInterface->funcBool(Testbed1::StructBool());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcBool async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcBoolAsync(Testbed1::StructBool());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructBool()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcBool async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcBoolAsync(Testbed1::StructBool(),[&finished, &m_wait](StructBool value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructBool()); 
    }
    SECTION("Test method funcInt")
    {
        [[maybe_unused]] auto result =  clientStructInterface->funcInt(Testbed1::StructInt());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcIntAsync(Testbed1::StructInt());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructInt()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcIntAsync(Testbed1::StructInt(),[&finished, &m_wait](StructInt value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructInt()); 
    }
    SECTION("Test method funcFloat")
    {
        [[maybe_unused]] auto result =  clientStructInterface->funcFloat(Testbed1::StructFloat());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcFloatAsync(Testbed1::StructFloat());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructFloat()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcFloatAsync(Testbed1::StructFloat(),[&finished, &m_wait](StructFloat value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructFloat()); 
    }
    SECTION("Test method funcString")
    {
        [[maybe_unused]] auto result =  clientStructInterface->funcString(Testbed1::StructString());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcString async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcStringAsync(Testbed1::StructString());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructString()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcString async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructInterface->funcStringAsync(Testbed1::StructString(),[&finished, &m_wait](StructString value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructString()); 
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
    serviceStructInterface.reset();
    clientStructInterface.reset();
}
