#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/nats/simplearrayinterfaceclient.h"
#include "tb_simple/generated/nats/simplearrayinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("Nats  tb.simple SimpleArrayInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implSimpleArrayInterface = std::make_shared<Test::TbSimple::SimpleArrayInterface>();
    auto serviceSimpleArrayInterface = Nats::SimpleArrayInterfaceService::create(implSimpleArrayInterface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceSimpleArrayInterface]() {return  serviceSimpleArrayInterface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientSimpleArrayInterface = Nats::SimpleArrayInterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientSimpleArrayInterface]() {return clientSimpleArrayInterface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting propBool")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigBool(local_param_bool_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigInt(local_param_int_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt32")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigInt32(local_param_int32_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt32Emitted ]() {return issigInt32Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt64")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigInt64(local_param_int64_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt64Emitted ]() {return issigInt64Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigFloat(local_param_float_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat32")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigFloat32(local_param_floa32_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat32Emitted ]() {return issigFloat32Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat64")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigFloat64(local_param_float64_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat64Emitted ]() {return issigFloat64Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigString")
    {
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

         implSimpleArrayInterface->_getPublisher().publishSigString(local_param_string_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcBool(std::list<bool>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcBoolAsync(std::list<bool>(),
            [&finished, &m_wait](std::list<bool> value)
            {
                REQUIRE(value == std::list<bool>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcInt")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcInt(std::list<int>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcIntAsync(std::list<int>(),
            [&finished, &m_wait](std::list<int> value)
            {
                REQUIRE(value == std::list<int>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcInt32")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcInt32(std::list<int32_t>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt32 async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcInt32Async(std::list<int32_t>(),
            [&finished, &m_wait](std::list<int32_t> value)
            {
                REQUIRE(value == std::list<int32_t>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcInt64")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcInt64(std::list<int64_t>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt64 async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcInt64Async(std::list<int64_t>(),
            [&finished, &m_wait](std::list<int64_t> value)
            {
                REQUIRE(value == std::list<int64_t>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcFloat")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcFloat(std::list<float>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcFloatAsync(std::list<float>(),
            [&finished, &m_wait](std::list<float> value)
            {
                REQUIRE(value == std::list<float>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcFloat32")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcFloat32(std::list<float>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat32 async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcFloat32Async(std::list<float>(),
            [&finished, &m_wait](std::list<float> value)
            {
                REQUIRE(value == std::list<float>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcFloat64")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcFloat64(std::list<double>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat64 async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcFloat64Async(std::list<double>(),
            [&finished, &m_wait](std::list<double> value)
            {
                REQUIRE(value == std::list<double>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcString")
    {
        [[maybe_unused]] auto result = clientSimpleArrayInterface->funcString(std::list<std::string>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcString async")
    {
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
        auto resultFuture = clientSimpleArrayInterface->funcStringAsync(std::list<std::string>(),
            [&finished, &m_wait](std::list<std::string> value)
            {
                REQUIRE(value == std::list<std::string>());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }

    serviceSimpleArrayInterface.reset();
    clientSimpleArrayInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
