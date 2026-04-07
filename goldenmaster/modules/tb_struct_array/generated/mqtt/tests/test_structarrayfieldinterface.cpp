#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_struct_array/generated/core/test_struct_helper.h"
#include "tb_struct_array/implementation/structarrayfieldinterface.h"
#include "tb_struct_array/generated/mqtt/structarrayfieldinterfaceclient.h"
#include "tb_struct_array/generated/mqtt/structarrayfieldinterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{
#if defined(__SANITIZE_THREAD__)
    int timeout = 10000;//in ms - longer for TSan builds
#elif defined(__has_feature)
#   if __has_feature(thread_sanitizer)
    int timeout = 10000;//in ms - longer for TSan builds
#   else
    int timeout = 1000;//in ms
#   endif
#else
    int timeout = 1000;//in ms
#endif
}

using namespace Test;
using namespace Test::TbStructArray;

TEST_CASE("mqtt  tb.struct.array StructArrayFieldInterface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("StructArrayFieldInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("StructArrayFieldInterfacetestClient");

    auto clientStructArrayFieldInterface = std::make_shared<Test::TbStructArray::MQTT::StructArrayFieldInterfaceClient>(mqttclient);
    auto implStructArrayFieldInterface= std::make_shared<Test::TbStructArray::StructArrayFieldInterface>();
    auto serviceStructArrayFieldInterface = std::make_shared<Test::TbStructArray::MQTT::StructArrayFieldInterfaceService>(implStructArrayFieldInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceStructArrayFieldInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceStructArrayFieldInterface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientStructArrayFieldInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
    SECTION("Test setting propStructArray")
    {
        std::atomic<bool> ispropStructArrayChanged = false;
        clientStructArrayFieldInterface->_getPublisher().subscribeToPropStructArrayChanged(
        [&ispropStructArrayChanged, &m_wait ](auto value){
            ispropStructArrayChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = TbStructArray::StructWithArrayOfStructs();
        TbStructArray::fillTestStructWithArrayOfStructs(test_value);
        clientStructArrayFieldInterface->setPropStructArray(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropStructArrayChanged]() {return ispropStructArrayChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayFieldInterface->getPropStructArray() == test_value);
        REQUIRE(clientStructArrayFieldInterface->getPropStructArray() == test_value);
    }
    SECTION("Test setting propEnumArray")
    {
        std::atomic<bool> ispropEnumArrayChanged = false;
        clientStructArrayFieldInterface->_getPublisher().subscribeToPropEnumArrayChanged(
        [&ispropEnumArrayChanged, &m_wait ](auto value){
            ispropEnumArrayChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = TbStructArray::StructWithArrayOfEnums();
        TbStructArray::fillTestStructWithArrayOfEnums(test_value);
        clientStructArrayFieldInterface->setPropEnumArray(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropEnumArrayChanged]() {return ispropEnumArrayChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayFieldInterface->getPropEnumArray() == test_value);
        REQUIRE(clientStructArrayFieldInterface->getPropEnumArray() == test_value);
    }
    SECTION("Test setting propIntArray")
    {
        std::atomic<bool> ispropIntArrayChanged = false;
        clientStructArrayFieldInterface->_getPublisher().subscribeToPropIntArrayChanged(
        [&ispropIntArrayChanged, &m_wait ](auto value){
            ispropIntArrayChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = TbStructArray::StructWithArrayOfInts();
        TbStructArray::fillTestStructWithArrayOfInts(test_value);
        clientStructArrayFieldInterface->setPropIntArray(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntArrayChanged]() {return ispropIntArrayChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayFieldInterface->getPropIntArray() == test_value);
        REQUIRE(clientStructArrayFieldInterface->getPropIntArray() == test_value);
    }
    SECTION("Test setting propMixed")
    {
        std::atomic<bool> ispropMixedChanged = false;
        clientStructArrayFieldInterface->_getPublisher().subscribeToPropMixedChanged(
        [&ispropMixedChanged, &m_wait ](auto value){
            ispropMixedChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = TbStructArray::MixedStruct();
        TbStructArray::fillTestMixedStruct(test_value);
        clientStructArrayFieldInterface->setPropMixed(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropMixedChanged]() {return ispropMixedChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArrayFieldInterface->getPropMixed() == test_value);
        REQUIRE(clientStructArrayFieldInterface->getPropMixed() == test_value);
    }
    SECTION("Test emit sigMixed")
    {
        std::atomic<bool> issigMixedEmitted = false;
        auto local_param_mixed_struct = TbStructArray::MixedStruct();
        TbStructArray::fillTestMixedStruct(local_param_mixed_struct);

        clientStructArrayFieldInterface->_getPublisher().subscribeToSigMixed(
        [&m_wait, &issigMixedEmitted, &local_param_mixed_struct](const TbStructArray::MixedStruct& paramMixed)
        {
            REQUIRE(paramMixed ==local_param_mixed_struct);
            issigMixedEmitted  = true;
            m_wait.notify_all();
        });

         implStructArrayFieldInterface->_getPublisher().publishSigMixed(local_param_mixed_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigMixedEmitted ]() {return issigMixedEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigStructArray")
    {
        std::atomic<bool> issigStructArrayEmitted = false;
        auto local_param_points_struct = TbStructArray::StructWithArrayOfStructs();
        TbStructArray::fillTestStructWithArrayOfStructs(local_param_points_struct);

        clientStructArrayFieldInterface->_getPublisher().subscribeToSigStructArray(
        [&m_wait, &issigStructArrayEmitted, &local_param_points_struct](const TbStructArray::StructWithArrayOfStructs& paramPoints)
        {
            REQUIRE(paramPoints ==local_param_points_struct);
            issigStructArrayEmitted  = true;
            m_wait.notify_all();
        });

         implStructArrayFieldInterface->_getPublisher().publishSigStructArray(local_param_points_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStructArrayEmitted ]() {return issigStructArrayEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcMixed")
    {
        [[maybe_unused]] auto result =  clientStructArrayFieldInterface->funcMixed(TbStructArray::MixedStruct());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcMixed async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayFieldInterface->funcMixedAsync(TbStructArray::MixedStruct());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbStructArray::MixedStruct()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcMixed async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayFieldInterface->funcMixedAsync(TbStructArray::MixedStruct(),[&finished, &m_wait](MixedStruct value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbStructArray::MixedStruct()); 
    }
    SECTION("Test method funcStructArray")
    {
        [[maybe_unused]] auto result =  clientStructArrayFieldInterface->funcStructArray(TbStructArray::StructWithArrayOfStructs());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method funcStructArray async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayFieldInterface->funcStructArrayAsync(TbStructArray::StructWithArrayOfStructs());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbStructArray::StructWithArrayOfStructs()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcStructArray async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArrayFieldInterface->funcStructArrayAsync(TbStructArray::StructWithArrayOfStructs(),[&finished, &m_wait](StructWithArrayOfStructs value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbStructArray::StructWithArrayOfStructs()); 
    }

    mqttservice->disconnect();
    mqttclient->disconnect();
    serviceStructArrayFieldInterface.reset();
    clientStructArrayFieldInterface.reset();
    mqttservice.reset();
    mqttclient.reset();
}
