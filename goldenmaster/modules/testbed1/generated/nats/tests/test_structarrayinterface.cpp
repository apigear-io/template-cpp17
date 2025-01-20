#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed1/generated/core/test_struct_helper.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/nats/structarrayinterfaceclient.h"
#include "testbed1/generated/nats/structarrayinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::Testbed1;

TEST_CASE("Nats  testbed1 StructArrayInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implStructArrayInterface = std::make_shared<Test::Testbed1::StructArrayInterface>();
    auto serviceStructArrayInterface = Nats::StructArrayInterfaceService::create(implStructArrayInterface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceStructArrayInterface]() {return  serviceStructArrayInterface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientStructArrayInterface = Nats::StructArrayInterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientStructArrayInterface]() {return clientStructArrayInterface->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting propBool")
    {
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

         implStructArrayInterface->_getPublisher().publishSigBool(local_param_bool_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt")
    {
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

         implStructArrayInterface->_getPublisher().publishSigInt(local_param_int_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat")
    {
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

         implStructArrayInterface->_getPublisher().publishSigFloat(local_param_float_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigString")
    {
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

         implStructArrayInterface->_getPublisher().publishSigString(local_param_string_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result = clientStructArrayInterface->funcBool(std::list<Testbed1::StructBool>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcBoolAsync(std::list<Testbed1::StructBool>());
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
        auto resultFuture = clientStructArrayInterface->funcBoolAsync(std::list<Testbed1::StructBool>(),
            [&finished, &m_wait](StructBool value)
            {
                REQUIRE(value == Testbed1::StructBool());
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
        [[maybe_unused]] auto result = clientStructArrayInterface->funcInt(std::list<Testbed1::StructInt>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcIntAsync(std::list<Testbed1::StructInt>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructBool()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcIntAsync(std::list<Testbed1::StructInt>(),
            [&finished, &m_wait](StructBool value)
            {
                REQUIRE(value == Testbed1::StructBool());
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
        [[maybe_unused]] auto result = clientStructArrayInterface->funcFloat(std::list<Testbed1::StructFloat>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcFloatAsync(std::list<Testbed1::StructFloat>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructBool()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcFloatAsync(std::list<Testbed1::StructFloat>(),
            [&finished, &m_wait](StructBool value)
            {
                REQUIRE(value == Testbed1::StructBool());
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
        [[maybe_unused]] auto result = clientStructArrayInterface->funcString(std::list<Testbed1::StructString>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcString async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcStringAsync(std::list<Testbed1::StructString>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed1::StructBool()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcString async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayInterface->funcStringAsync(std::list<Testbed1::StructString>(),
            [&finished, &m_wait](StructBool value)
            {
                REQUIRE(value == Testbed1::StructBool());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }

    serviceStructArrayInterface.reset();
    clientStructArrayInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
