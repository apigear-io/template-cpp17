#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>
#include <iostream>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/mqtt/simplearrayinterfaceclient.h"
#include "tb_simple/generated/mqtt/simplearrayinterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("mqtt  tb.simple SimpleArrayInterface tests")
{
    std::cout<<"starting set up connection" << std::endl;
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("SimpleArrayInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("SimpleArrayInterfacetestClient");

    auto clientSimpleArrayInterface = std::make_shared<Test::TbSimple::MQTT::SimpleArrayInterfaceClient>(mqttclient);
    auto implSimpleArrayInterface= std::make_shared<Test::TbSimple::SimpleArrayInterface>();
    auto serviceSimpleArrayInterface = std::make_shared<Test::TbSimple::MQTT::SimpleArrayInterfaceService>(implSimpleArrayInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceSimpleArrayInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceSimpleArrayInterface->_is_ready() == true)
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
    clientSimpleArrayInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        std::cout<<"SimpleArrayInterface Test setting propBool" << std::endl;
        std::atomic<bool> ispropBoolChanged = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropBoolChanged(
        [&ispropBoolChanged, &m_wait ](auto value){
            ispropBoolChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<bool>();  
        test_value.push_back(true);
        clientSimpleArrayInterface->setPropBool(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropBoolChanged]() {return ispropBoolChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropBool() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropBool() == test_value);
    }
    SECTION("Test setting propInt")
    {
        std::cout<<"SimpleArrayInterface Test setting propInt" << std::endl;
        std::atomic<bool> ispropIntChanged = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropIntChanged(
        [&ispropIntChanged, &m_wait ](auto value){
            ispropIntChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<int>();  
        test_value.push_back(1);
        clientSimpleArrayInterface->setPropInt(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntChanged]() {return ispropIntChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropInt() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropInt() == test_value);
    }
    SECTION("Test setting propInt32")
    {
        std::cout<<"SimpleArrayInterface Test setting propInt32" << std::endl;
        std::atomic<bool> ispropInt32Changed = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropInt32Changed(
        [&ispropInt32Changed, &m_wait ](auto value){
            ispropInt32Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<int32_t>();  
        test_value.push_back(1);
        clientSimpleArrayInterface->setPropInt32(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropInt32Changed]() {return ispropInt32Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropInt32() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropInt32() == test_value);
    }
    SECTION("Test setting propInt64")
    {
        std::cout<<"SimpleArrayInterface Test setting propInt64" << std::endl;
        std::atomic<bool> ispropInt64Changed = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropInt64Changed(
        [&ispropInt64Changed, &m_wait ](auto value){
            ispropInt64Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<int64_t>();  
        test_value.push_back(1LL);
        clientSimpleArrayInterface->setPropInt64(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropInt64Changed]() {return ispropInt64Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropInt64() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropInt64() == test_value);
    }
    SECTION("Test setting propFloat")
    {
        std::cout<<"SimpleArrayInterface Test setting propFloat" << std::endl;
        std::atomic<bool> ispropFloatChanged = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropFloatChanged(
        [&ispropFloatChanged, &m_wait ](auto value){
            ispropFloatChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<float>();  
        test_value.push_back(1.1f);
        clientSimpleArrayInterface->setPropFloat(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloatChanged]() {return ispropFloatChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropFloat() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropFloat() == test_value);
    }
    SECTION("Test setting propFloat32")
    {
        std::cout<<"SimpleArrayInterface Test setting propFloat32" << std::endl;
        std::atomic<bool> ispropFloat32Changed = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropFloat32Changed(
        [&ispropFloat32Changed, &m_wait ](auto value){
            ispropFloat32Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<float>();  
        test_value.push_back(1.1f);
        clientSimpleArrayInterface->setPropFloat32(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloat32Changed]() {return ispropFloat32Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropFloat32() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropFloat32() == test_value);
    }
    SECTION("Test setting propFloat64")
    {
        std::cout<<"SimpleArrayInterface Test setting propFloat64" << std::endl;
        std::atomic<bool> ispropFloat64Changed = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropFloat64Changed(
        [&ispropFloat64Changed, &m_wait ](auto value){
            ispropFloat64Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<double>();  
        test_value.push_back(1.1);
        clientSimpleArrayInterface->setPropFloat64(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloat64Changed]() {return ispropFloat64Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropFloat64() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropFloat64() == test_value);
    }
    SECTION("Test setting propString")
    {
        std::cout<<"SimpleArrayInterface Test setting propString" << std::endl;
        std::atomic<bool> ispropStringChanged = false;
        clientSimpleArrayInterface->_getPublisher().subscribeToPropStringChanged(
        [&ispropStringChanged, &m_wait ](auto value){
            ispropStringChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<std::string>();  
        test_value.push_back(std::string("xyz"));
        clientSimpleArrayInterface->setPropString(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropStringChanged]() {return ispropStringChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleArrayInterface->getPropString() == test_value);
        REQUIRE(clientSimpleArrayInterface->getPropString() == test_value);
    }
    SECTION("Test emit sigBool")
    {
        std::cout<<"SimpleArrayInterface Test emit sigBool" << std::endl;
        std::atomic<bool> issigBoolEmitted = false;
        auto local_param_bool_array = std::list<bool>();
        local_param_bool_array.push_back(true);

        clientSimpleArrayInterface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted, &local_param_bool_array](const std::list<bool>& paramBool)
        {
            REQUIRE(paramBool == local_param_bool_array);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigBool(local_param_bool_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigBool" << std::endl;
    }
    SECTION("Test emit sigInt")
    {
        std::cout<<"SimpleArrayInterface Test emit sigInt" << std::endl;
        std::atomic<bool> issigIntEmitted = false;
        auto local_param_int_array = std::list<int>();
        local_param_int_array.push_back(1);

        clientSimpleArrayInterface->_getPublisher().subscribeToSigInt(
        [&m_wait, &issigIntEmitted, &local_param_int_array](const std::list<int>& paramInt)
        {
            REQUIRE(paramInt == local_param_int_array);
            issigIntEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigInt(local_param_int_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigInt" << std::endl;
    }
    SECTION("Test emit sigInt32")
    {
        std::cout<<"SimpleArrayInterface Test emit sigInt32" << std::endl;
        std::atomic<bool> issigInt32Emitted = false;
        auto local_param_int32_array = std::list<int32_t>();
        local_param_int32_array.push_back(1);

        clientSimpleArrayInterface->_getPublisher().subscribeToSigInt32(
        [&m_wait, &issigInt32Emitted, &local_param_int32_array](const std::list<int32_t>& paramInt32)
        {
            REQUIRE(paramInt32 == local_param_int32_array);
            issigInt32Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigInt32(local_param_int32_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt32Emitted ]() {return issigInt32Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigInt32" << std::endl;
    }
    SECTION("Test emit sigInt64")
    {
        std::cout<<"SimpleArrayInterface Test emit sigInt64" << std::endl;
        std::atomic<bool> issigInt64Emitted = false;
        auto local_param_int64_array = std::list<int64_t>();
        local_param_int64_array.push_back(1LL);

        clientSimpleArrayInterface->_getPublisher().subscribeToSigInt64(
        [&m_wait, &issigInt64Emitted, &local_param_int64_array](const std::list<int64_t>& paramInt64)
        {
            REQUIRE(paramInt64 == local_param_int64_array);
            issigInt64Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigInt64(local_param_int64_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt64Emitted ]() {return issigInt64Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigInt64" << std::endl;
    }
    SECTION("Test emit sigFloat")
    {
        std::cout<<"SimpleArrayInterface Test emit sigFloat" << std::endl;
        std::atomic<bool> issigFloatEmitted = false;
        auto local_param_float_array = std::list<float>();
        local_param_float_array.push_back(1.1f);

        clientSimpleArrayInterface->_getPublisher().subscribeToSigFloat(
        [&m_wait, &issigFloatEmitted, &local_param_float_array](const std::list<float>& paramFloat)
        {
            REQUIRE(paramFloat == local_param_float_array);
            issigFloatEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigFloat(local_param_float_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigFloat" << std::endl;
    }
    SECTION("Test emit sigFloat32")
    {
        std::cout<<"SimpleArrayInterface Test emit sigFloat32" << std::endl;
        std::atomic<bool> issigFloat32Emitted = false;
        auto local_param_floa32_array = std::list<float>();
        local_param_floa32_array.push_back(1.1f);

        clientSimpleArrayInterface->_getPublisher().subscribeToSigFloat32(
        [&m_wait, &issigFloat32Emitted, &local_param_floa32_array](const std::list<float>& paramFloa32)
        {
            REQUIRE(paramFloa32 == local_param_floa32_array);
            issigFloat32Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigFloat32(local_param_floa32_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat32Emitted ]() {return issigFloat32Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigFloat32" << std::endl;
    }
    SECTION("Test emit sigFloat64")
    {
        std::cout<<"SimpleArrayInterface Test emit sigFloat64" << std::endl;
        std::atomic<bool> issigFloat64Emitted = false;
        auto local_param_float64_array = std::list<double>();
        local_param_float64_array.push_back(1.1);

        clientSimpleArrayInterface->_getPublisher().subscribeToSigFloat64(
        [&m_wait, &issigFloat64Emitted, &local_param_float64_array](const std::list<double>& paramFloat64)
        {
            REQUIRE(paramFloat64 == local_param_float64_array);
            issigFloat64Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigFloat64(local_param_float64_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat64Emitted ]() {return issigFloat64Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigFloat64" << std::endl;
    }
    SECTION("Test emit sigString")
    {
        std::cout<<"SimpleArrayInterface Test emit sigString" << std::endl;
        std::atomic<bool> issigStringEmitted = false;
        auto local_param_string_array = std::list<std::string>();
        local_param_string_array.push_back(std::string("xyz"));

        clientSimpleArrayInterface->_getPublisher().subscribeToSigString(
        [&m_wait, &issigStringEmitted, &local_param_string_array](const std::list<std::string>& paramString)
        {
            REQUIRE(paramString == local_param_string_array);
            issigStringEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleArrayInterface->_getPublisher().publishSigString(local_param_string_array);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleArrayInterface Test emit sigString" << std::endl;
    }
    SECTION("Test method funcBool")
    {
        std::cout<<"SimpleArrayInterface Test method funcBool" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcBool(std::list<bool>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcBool async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcBool" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcBoolAsync(std::list<bool>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<bool>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcBool async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcBoolAsync(std::list<bool>(),[&finished, &m_wait](std::list<bool> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<bool>()); 
    }
    SECTION("Test method funcInt")
    {
        std::cout<<"SimpleArrayInterface Test method funcInt" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcInt(std::list<int>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcInt" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcIntAsync(std::list<int>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<int>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcIntAsync(std::list<int>(),[&finished, &m_wait](std::list<int> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<int>()); 
    }
    SECTION("Test method funcInt32")
    {
        std::cout<<"SimpleArrayInterface Test method funcInt32" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcInt32(std::list<int32_t>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt32 async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcInt32" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcInt32Async(std::list<int32_t>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<int32_t>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt32 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcInt32Async(std::list<int32_t>(),[&finished, &m_wait](std::list<int32_t> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<int32_t>()); 
    }
    SECTION("Test method funcInt64")
    {
        std::cout<<"SimpleArrayInterface Test method funcInt64" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcInt64(std::list<int64_t>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt64 async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcInt64" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcInt64Async(std::list<int64_t>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<int64_t>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt64 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcInt64Async(std::list<int64_t>(),[&finished, &m_wait](std::list<int64_t> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<int64_t>()); 
    }
    SECTION("Test method funcFloat")
    {
        std::cout<<"SimpleArrayInterface Test method funcFloat" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcFloat(std::list<float>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcFloat" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcFloatAsync(std::list<float>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<float>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcFloatAsync(std::list<float>(),[&finished, &m_wait](std::list<float> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<float>()); 
    }
    SECTION("Test method funcFloat32")
    {
        std::cout<<"SimpleArrayInterface Test method funcFloat32" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcFloat32(std::list<float>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat32 async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcFloat32" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcFloat32Async(std::list<float>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<float>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat32 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcFloat32Async(std::list<float>(),[&finished, &m_wait](std::list<float> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<float>()); 
    }
    SECTION("Test method funcFloat64")
    {
        std::cout<<"SimpleArrayInterface Test method funcFloat64" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcFloat64(std::list<double>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat64 async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcFloat64" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcFloat64Async(std::list<double>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<double>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat64 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcFloat64Async(std::list<double>(),[&finished, &m_wait](std::list<double> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<double>()); 
    }
    SECTION("Test method funcString")
    {
        std::cout<<"SimpleArrayInterface Test method funcString" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleArrayInterface->funcString(std::list<std::string>());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcString async")
    {
        std::cout<<"SimpleArrayInterface Test async method funcString" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcStringAsync(std::list<std::string>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<std::string>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcString async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleArrayInterface->funcStringAsync(std::list<std::string>(),[&finished, &m_wait](std::list<std::string> value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<std::string>()); 
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
    serviceSimpleArrayInterface.reset();
    clientSimpleArrayInterface.reset();
    std::cout<<"all ptrs reset, should finish test" << std::endl;
}
