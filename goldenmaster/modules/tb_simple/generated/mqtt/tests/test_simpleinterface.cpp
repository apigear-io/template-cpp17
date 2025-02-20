#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>
#include <iostream>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/mqtt/simpleinterfaceclient.h"
#include "tb_simple/generated/mqtt/simpleinterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("mqtt  tb.simple SimpleInterface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("SimpleInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("SimpleInterfacetestClient");

    auto clientSimpleInterface = std::make_shared<Test::TbSimple::MQTT::SimpleInterfaceClient>(mqttclient);
    auto implSimpleInterface= std::make_shared<Test::TbSimple::SimpleInterface>();
    auto serviceSimpleInterface = std::make_shared<Test::TbSimple::MQTT::SimpleInterfaceService>(implSimpleInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceSimpleInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceSimpleInterface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientSimpleInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        std::cout<<"SimpleInterface Test setting propBool" << std::endl;
        std::atomic<bool> ispropBoolChanged = false;
        clientSimpleInterface->_getPublisher().subscribeToPropBoolChanged(
        [&ispropBoolChanged, &m_wait ](auto value){
            ispropBoolChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = true;
        clientSimpleInterface->setPropBool(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropBoolChanged]() {return ispropBoolChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropBool() == test_value);
        REQUIRE(clientSimpleInterface->getPropBool() == test_value);
    }
    SECTION("Test setting propInt")
    {
        std::cout<<"SimpleInterface Test setting propInt" << std::endl;
        std::atomic<bool> ispropIntChanged = false;
        clientSimpleInterface->_getPublisher().subscribeToPropIntChanged(
        [&ispropIntChanged, &m_wait ](auto value){
            ispropIntChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientSimpleInterface->setPropInt(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntChanged]() {return ispropIntChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropInt() == test_value);
        REQUIRE(clientSimpleInterface->getPropInt() == test_value);
    }
    SECTION("Test setting propInt32")
    {
        std::cout<<"SimpleInterface Test setting propInt32" << std::endl;
        std::atomic<bool> ispropInt32Changed = false;
        clientSimpleInterface->_getPublisher().subscribeToPropInt32Changed(
        [&ispropInt32Changed, &m_wait ](auto value){
            ispropInt32Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientSimpleInterface->setPropInt32(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropInt32Changed]() {return ispropInt32Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropInt32() == test_value);
        REQUIRE(clientSimpleInterface->getPropInt32() == test_value);
    }
    SECTION("Test setting propInt64")
    {
        std::cout<<"SimpleInterface Test setting propInt64" << std::endl;
        std::atomic<bool> ispropInt64Changed = false;
        clientSimpleInterface->_getPublisher().subscribeToPropInt64Changed(
        [&ispropInt64Changed, &m_wait ](auto value){
            ispropInt64Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1LL;
        clientSimpleInterface->setPropInt64(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropInt64Changed]() {return ispropInt64Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropInt64() == test_value);
        REQUIRE(clientSimpleInterface->getPropInt64() == test_value);
    }
    SECTION("Test setting propFloat")
    {
        std::cout<<"SimpleInterface Test setting propFloat" << std::endl;
        std::atomic<bool> ispropFloatChanged = false;
        clientSimpleInterface->_getPublisher().subscribeToPropFloatChanged(
        [&ispropFloatChanged, &m_wait ](auto value){
            ispropFloatChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = 1.1f;
        clientSimpleInterface->setPropFloat(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloatChanged]() {return ispropFloatChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropFloat() == test_value);
        REQUIRE(clientSimpleInterface->getPropFloat() == test_value);
    }
    SECTION("Test setting propFloat32")
    {
        std::cout<<"SimpleInterface Test setting propFloat32" << std::endl;
        std::atomic<bool> ispropFloat32Changed = false;
        clientSimpleInterface->_getPublisher().subscribeToPropFloat32Changed(
        [&ispropFloat32Changed, &m_wait ](auto value){
            ispropFloat32Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1.1f;
        clientSimpleInterface->setPropFloat32(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloat32Changed]() {return ispropFloat32Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropFloat32() == test_value);
        REQUIRE(clientSimpleInterface->getPropFloat32() == test_value);
    }
    SECTION("Test setting propFloat64")
    {
        std::cout<<"SimpleInterface Test setting propFloat64" << std::endl;
        std::atomic<bool> ispropFloat64Changed = false;
        clientSimpleInterface->_getPublisher().subscribeToPropFloat64Changed(
        [&ispropFloat64Changed, &m_wait ](auto value){
            ispropFloat64Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1.1;
        clientSimpleInterface->setPropFloat64(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloat64Changed]() {return ispropFloat64Changed  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropFloat64() == test_value);
        REQUIRE(clientSimpleInterface->getPropFloat64() == test_value);
    }
    SECTION("Test setting propString")
    {
        std::cout<<"SimpleInterface Test setting propString" << std::endl;
        std::atomic<bool> ispropStringChanged = false;
        clientSimpleInterface->_getPublisher().subscribeToPropStringChanged(
        [&ispropStringChanged, &m_wait ](auto value){
            ispropStringChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::string("xyz");
        clientSimpleInterface->setPropString(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropStringChanged]() {return ispropStringChanged  == true; }));
        lock.unlock();
        REQUIRE(implSimpleInterface->getPropString() == test_value);
        REQUIRE(clientSimpleInterface->getPropString() == test_value);
    }
    SECTION("Test emit sigBool")
    {
        std::cout<<"SimpleInterface Test emit sigBool" << std::endl;
        std::atomic<bool> issigBoolEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted](bool paramBool)
        {
            REQUIRE(paramBool == true);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigBool(true);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigBool" << std::endl;
    }
    SECTION("Test emit sigInt")
    {
        std::cout<<"SimpleInterface Test emit sigInt" << std::endl;
        std::atomic<bool> issigIntEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigInt(
        [&m_wait, &issigIntEmitted](int paramInt)
        {
            REQUIRE(paramInt == 1);
            issigIntEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigInt(1);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigInt" << std::endl;
    }
    SECTION("Test emit sigInt32")
    {
        std::cout<<"SimpleInterface Test emit sigInt32" << std::endl;
        std::atomic<bool> issigInt32Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigInt32(
        [&m_wait, &issigInt32Emitted](int32_t paramInt32)
        {
            REQUIRE(paramInt32 == 1);
            issigInt32Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigInt32(1);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt32Emitted ]() {return issigInt32Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigInt32" << std::endl;
    }
    SECTION("Test emit sigInt64")
    {
        std::cout<<"SimpleInterface Test emit sigInt64" << std::endl;
        std::atomic<bool> issigInt64Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigInt64(
        [&m_wait, &issigInt64Emitted](int64_t paramInt64)
        {
            REQUIRE(paramInt64 == 1LL);
            issigInt64Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigInt64(1LL);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt64Emitted ]() {return issigInt64Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigInt64" << std::endl;
    }
    SECTION("Test emit sigFloat")
    {
        std::cout<<"SimpleInterface Test emit sigFloat" << std::endl;
        std::atomic<bool> issigFloatEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigFloat(
        [&m_wait, &issigFloatEmitted](float paramFloat)
        {
            REQUIRE(paramFloat == 1.1f);
            issigFloatEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigFloat(1.1f);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigFloat" << std::endl;
    }
    SECTION("Test emit sigFloat32")
    {
        std::cout<<"SimpleInterface Test emit sigFloat32" << std::endl;
        std::atomic<bool> issigFloat32Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigFloat32(
        [&m_wait, &issigFloat32Emitted](float paramFloat32)
        {
            REQUIRE(paramFloat32 == 1.1f);
            issigFloat32Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigFloat32(1.1f);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat32Emitted ]() {return issigFloat32Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigFloat32" << std::endl;
    }
    SECTION("Test emit sigFloat64")
    {
        std::cout<<"SimpleInterface Test emit sigFloat64" << std::endl;
        std::atomic<bool> issigFloat64Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigFloat64(
        [&m_wait, &issigFloat64Emitted](double paramFloat64)
        {
            REQUIRE(paramFloat64 == 1.1);
            issigFloat64Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigFloat64(1.1);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat64Emitted ]() {return issigFloat64Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigFloat64" << std::endl;
    }
    SECTION("Test emit sigString")
    {
        std::cout<<"SimpleInterface Test emit sigString" << std::endl;
        std::atomic<bool> issigStringEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigString(
        [&m_wait, &issigStringEmitted](const std::string& paramString)
        {
            REQUIRE(paramString == std::string("xyz"));
            issigStringEmitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implSimpleInterface->_getPublisher().publishSigString(std::string("xyz"));
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed SimpleInterface Test emit sigString" << std::endl;
    }
    SECTION("Test method funcNoReturnValue")
    {
        std::cout<<"SimpleInterface Test method funcNoReturnValue" << std::endl;
         clientSimpleInterface->funcNoReturnValue(false);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcNoReturnValue async")
    {
        std::cout<<"SimpleInterface Test async method funcNoReturnValue" << std::endl;
        auto resultFuture = clientSimpleInterface->funcNoReturnValueAsync(false);
        // The void function only sends request. It does not wait for the actual function on server side to be finished.
    }

    SECTION("Test method funcNoReturnValue async with callback")
    {
        auto resultFuture = clientSimpleInterface->funcNoReturnValueAsync(false,[](){/* you can add a callback, but it will be called right after sending the request. It does not wait for the actual function on server side to be finished. */ });
    }
    SECTION("Test method funcBool")
    {
        std::cout<<"SimpleInterface Test method funcBool" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcBool(false);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcBool async")
    {
        std::cout<<"SimpleInterface Test async method funcBool" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcBoolAsync(false);
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
        auto resultFuture = clientSimpleInterface->funcBoolAsync(false,[&finished, &m_wait](bool value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == false); 
    }
    SECTION("Test method funcInt")
    {
        std::cout<<"SimpleInterface Test method funcInt" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcInt(0);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt async")
    {
        std::cout<<"SimpleInterface Test async method funcInt" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcIntAsync(0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcIntAsync(0,[&finished, &m_wait](int value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
    }
    SECTION("Test method funcInt32")
    {
        std::cout<<"SimpleInterface Test method funcInt32" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcInt32(0);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt32 async")
    {
        std::cout<<"SimpleInterface Test async method funcInt32" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcInt32Async(0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt32 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcInt32Async(0,[&finished, &m_wait](int32_t value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
    }
    SECTION("Test method funcInt64")
    {
        std::cout<<"SimpleInterface Test method funcInt64" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcInt64(0LL);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcInt64 async")
    {
        std::cout<<"SimpleInterface Test async method funcInt64" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcInt64Async(0LL);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0LL); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt64 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcInt64Async(0LL,[&finished, &m_wait](int64_t value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0LL); 
    }
    SECTION("Test method funcFloat")
    {
        std::cout<<"SimpleInterface Test method funcFloat" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcFloat(0.0f);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat async")
    {
        std::cout<<"SimpleInterface Test async method funcFloat" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcFloatAsync(0.0f);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0.0f); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcFloatAsync(0.0f,[&finished, &m_wait](float value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0.0f); 
    }
    SECTION("Test method funcFloat32")
    {
        std::cout<<"SimpleInterface Test method funcFloat32" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcFloat32(0.0f);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat32 async")
    {
        std::cout<<"SimpleInterface Test async method funcFloat32" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcFloat32Async(0.0f);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0.0f); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat32 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcFloat32Async(0.0f,[&finished, &m_wait](float value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0.0f); 
    }
    SECTION("Test method funcFloat64")
    {
        std::cout<<"SimpleInterface Test method funcFloat64" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcFloat64(0.0);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcFloat64 async")
    {
        std::cout<<"SimpleInterface Test async method funcFloat64" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcFloat64Async(0.0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0.0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat64 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcFloat64Async(0.0,[&finished, &m_wait](double value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0.0); 
    }
    SECTION("Test method funcString")
    {
        std::cout<<"SimpleInterface Test method funcString" << std::endl;
        [[maybe_unused]] auto result =  clientSimpleInterface->funcString(std::string());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcString async")
    {
        std::cout<<"SimpleInterface Test async method funcString" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcStringAsync(std::string());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::string()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcString async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcStringAsync(std::string(),[&finished, &m_wait](std::string value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::string()); 
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
    serviceSimpleInterface.reset();
    clientSimpleInterface.reset();
}
