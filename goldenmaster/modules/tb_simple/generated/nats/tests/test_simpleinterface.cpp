#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/nats/simpleinterfaceclient.h"
#include "tb_simple/generated/nats/simpleinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("Nats  tb.simple SimpleInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implSimpleInterface = std::make_shared<Test::TbSimple::SimpleInterface>();
    auto serviceSimpleInterface = Nats::SimpleInterfaceService::create(implSimpleInterface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceSimpleInterface]() {return  serviceSimpleInterface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientSimpleInterface = Nats::SimpleInterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientSimpleInterface]() {return clientSimpleInterface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting propBool")
    {
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
        std::atomic<bool> issigBoolEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted](bool paramBool)
        {
            REQUIRE(paramBool == true);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigBool(true);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt")
    {
        std::atomic<bool> issigIntEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigInt(
        [&m_wait, &issigIntEmitted](int paramInt)
        {
            REQUIRE(paramInt == 1);
            issigIntEmitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigInt(1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt32")
    {
        std::atomic<bool> issigInt32Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigInt32(
        [&m_wait, &issigInt32Emitted](int32_t paramInt32)
        {
            REQUIRE(paramInt32 == 1);
            issigInt32Emitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigInt32(1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt32Emitted ]() {return issigInt32Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt64")
    {
        std::atomic<bool> issigInt64Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigInt64(
        [&m_wait, &issigInt64Emitted](int64_t paramInt64)
        {
            REQUIRE(paramInt64 == 1LL);
            issigInt64Emitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigInt64(1LL);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigInt64Emitted ]() {return issigInt64Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat")
    {
        std::atomic<bool> issigFloatEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigFloat(
        [&m_wait, &issigFloatEmitted](float paramFloat)
        {
            REQUIRE(paramFloat == 1.1f);
            issigFloatEmitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigFloat(1.1f);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat32")
    {
        std::atomic<bool> issigFloat32Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigFloat32(
        [&m_wait, &issigFloat32Emitted](float paramFloa32)
        {
            REQUIRE(paramFloa32 == 1.1f);
            issigFloat32Emitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigFloat32(1.1f);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat32Emitted ]() {return issigFloat32Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat64")
    {
        std::atomic<bool> issigFloat64Emitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigFloat64(
        [&m_wait, &issigFloat64Emitted](double paramFloat64)
        {
            REQUIRE(paramFloat64 == 1.1);
            issigFloat64Emitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigFloat64(1.1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloat64Emitted ]() {return issigFloat64Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigString")
    {
        std::atomic<bool> issigStringEmitted = false;

        clientSimpleInterface->_getPublisher().subscribeToSigString(
        [&m_wait, &issigStringEmitted](const std::string& paramString)
        {
            REQUIRE(paramString == std::string("xyz"));
            issigStringEmitted  = true;
            m_wait.notify_all();
        });

         implSimpleInterface->_getPublisher().publishSigString(std::string("xyz"));
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcNoReturnValue")
    {
        clientSimpleInterface->funcNoReturnValue(false);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcNoReturnValue async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcNoReturnValueAsync(false);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        resultFuture.wait();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcNoReturnValue async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSimpleInterface->funcNoReturnValueAsync(false,
            [&finished, &m_wait]()
            { 
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result = clientSimpleInterface->funcBool(false);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool async")
    {
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
        auto resultFuture = clientSimpleInterface->funcBoolAsync(false,
            [&finished, &m_wait](bool value)
            {
                REQUIRE(value == false);
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
        [[maybe_unused]] auto result = clientSimpleInterface->funcInt(0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt async")
    {
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
        auto resultFuture = clientSimpleInterface->funcIntAsync(0,
            [&finished, &m_wait](int value)
            {
                REQUIRE(value == 0);
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
        [[maybe_unused]] auto result = clientSimpleInterface->funcInt32(0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt32 async")
    {
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
        auto resultFuture = clientSimpleInterface->funcInt32Async(0,
            [&finished, &m_wait](int32_t value)
            {
                REQUIRE(value == 0);
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
        [[maybe_unused]] auto result = clientSimpleInterface->funcInt64(0LL);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt64 async")
    {
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
        auto resultFuture = clientSimpleInterface->funcInt64Async(0LL,
            [&finished, &m_wait](int64_t value)
            {
                REQUIRE(value == 0LL);
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
        [[maybe_unused]] auto result = clientSimpleInterface->funcFloat(0.0f);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat async")
    {
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
        auto resultFuture = clientSimpleInterface->funcFloatAsync(0.0f,
            [&finished, &m_wait](float value)
            {
                REQUIRE(value == 0.0f);
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
        [[maybe_unused]] auto result = clientSimpleInterface->funcFloat32(0.0f);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat32 async")
    {
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
        auto resultFuture = clientSimpleInterface->funcFloat32Async(0.0f,
            [&finished, &m_wait](float value)
            {
                REQUIRE(value == 0.0f);
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
        [[maybe_unused]] auto result = clientSimpleInterface->funcFloat64(0.0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat64 async")
    {
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
        auto resultFuture = clientSimpleInterface->funcFloat64Async(0.0,
            [&finished, &m_wait](double value)
            {
                REQUIRE(value == 0.0);
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
        [[maybe_unused]] auto result = clientSimpleInterface->funcString(std::string());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcString async")
    {
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
        auto resultFuture = clientSimpleInterface->funcStringAsync(std::string(),
            [&finished, &m_wait](std::string value)
            {
                REQUIRE(value == std::string());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }

    serviceSimpleInterface.reset();
    clientSimpleInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
