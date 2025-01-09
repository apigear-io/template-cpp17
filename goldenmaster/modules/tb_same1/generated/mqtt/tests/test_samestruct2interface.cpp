#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same1/generated/core/test_struct_helper.h"
#include "tb_same1/implementation/samestruct2interface.h"
#include "tb_same1/generated/mqtt/samestruct2interfaceclient.h"
#include "tb_same1/generated/mqtt/samestruct2interfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::TbSame1;

TEST_CASE("mqtt  tb.same1 SameStruct2Interface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("SameStruct2InterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("SameStruct2InterfacetestClient");

    auto clientSameStruct2Interface = std::make_shared<Test::TbSame1::MQTT::SameStruct2InterfaceClient>(mqttclient);
    auto implSameStruct2Interface= std::make_shared<Test::TbSame1::SameStruct2Interface>();
    auto serviceSameStruct2Interface = std::make_shared<Test::TbSame1::MQTT::SameStruct2InterfaceService>(implSameStruct2Interface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceSameStruct2Interface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceSameStruct2Interface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientSameStruct2Interface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        clientSameStruct2Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame1::Struct2();
        TbSame1::fillTestStruct2(test_value);
        clientSameStruct2Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameStruct2Interface->getProp1() == test_value);
        REQUIRE(clientSameStruct2Interface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientSameStruct2Interface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame1::Struct2();
        TbSame1::fillTestStruct2(test_value);
        clientSameStruct2Interface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameStruct2Interface->getProp2() == test_value);
        REQUIRE(clientSameStruct2Interface->getProp2() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = TbSame1::Struct1();
        TbSame1::fillTestStruct1(local_param1_struct);

        clientSameStruct2Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const TbSame1::Struct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameStruct2Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;
        auto local_param1_struct = TbSame1::Struct1();
        TbSame1::fillTestStruct1(local_param1_struct);
        auto local_param2_struct = TbSame1::Struct2();
        TbSame1::fillTestStruct2(local_param2_struct);

        clientSameStruct2Interface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted, &local_param1_struct, &local_param2_struct](const TbSame1::Struct1& param1, const TbSame1::Struct2& param2)
        {
            REQUIRE(param1 ==local_param1_struct);
            REQUIRE(param2 ==local_param2_struct);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implSameStruct2Interface->_getPublisher().publishSig2(local_param1_struct, local_param2_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result =  clientSameStruct2Interface->func1(TbSame1::Struct1());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct2Interface->func1Async(TbSame1::Struct1());
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
        auto resultFuture = clientSameStruct2Interface->func1Async(TbSame1::Struct1(),[&finished, &m_wait](Struct1 value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Struct1()); 
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result =  clientSameStruct2Interface->func2(TbSame1::Struct1(), TbSame1::Struct2());
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct2Interface->func2Async(TbSame1::Struct1(), TbSame1::Struct2());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Struct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func2 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct2Interface->func2Async(TbSame1::Struct1(), TbSame1::Struct2(),[&finished, &m_wait](Struct1 value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

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
    serviceSameStruct2Interface.reset();
    clientSameStruct2Interface.reset();
}
