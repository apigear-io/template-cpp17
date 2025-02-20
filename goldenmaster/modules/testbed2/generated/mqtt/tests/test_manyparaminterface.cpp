#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>
#include <iostream>


#include "testbed2/generated/core/test_struct_helper.h"
#include "testbed2/implementation/manyparaminterface.h"
#include "testbed2/generated/mqtt/manyparaminterfaceclient.h"
#include "testbed2/generated/mqtt/manyparaminterfaceservice.h"


#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 2000;//in ms
}

using namespace Test;
using namespace Test::Testbed2;

TEST_CASE("mqtt  testbed2 ManyParamInterface tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("ManyParamInterfacetestServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("ManyParamInterfacetestClient");

    auto clientManyParamInterface = std::make_shared<Test::Testbed2::MQTT::ManyParamInterfaceClient>(mqttclient);
    auto implManyParamInterface= std::make_shared<Test::Testbed2::ManyParamInterface>();
    auto serviceManyParamInterface = std::make_shared<Test::Testbed2::MQTT::ManyParamInterfaceService>(implManyParamInterface, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = serviceManyParamInterface->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (serviceManyParamInterface->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    clientManyParamInterface->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
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
        std::cout<<"ManyParamInterface Test setting prop1" << std::endl;
        std::atomic<bool> isprop1Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp1() == test_value);
        REQUIRE(clientManyParamInterface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::cout<<"ManyParamInterface Test setting prop2" << std::endl;
        std::atomic<bool> isprop2Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp2() == test_value);
        REQUIRE(clientManyParamInterface->getProp2() == test_value);
    }
    SECTION("Test setting prop3")
    {
        std::cout<<"ManyParamInterface Test setting prop3" << std::endl;
        std::atomic<bool> isprop3Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp3Changed(
        [&isprop3Changed, &m_wait ](auto value){
            isprop3Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp3(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop3Changed]() {return isprop3Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp3() == test_value);
        REQUIRE(clientManyParamInterface->getProp3() == test_value);
    }
    SECTION("Test setting prop4")
    {
        std::cout<<"ManyParamInterface Test setting prop4" << std::endl;
        std::atomic<bool> isprop4Changed = false;
        clientManyParamInterface->_getPublisher().subscribeToProp4Changed(
        [&isprop4Changed, &m_wait ](auto value){
            isprop4Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = 1;
        clientManyParamInterface->setProp4(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop4Changed]() {return isprop4Changed  == true; }));
        lock.unlock();
        REQUIRE(implManyParamInterface->getProp4() == test_value);
        REQUIRE(clientManyParamInterface->getProp4() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::cout<<"ManyParamInterface Test emit sig1" << std::endl;
        std::atomic<bool> issig1Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](int param1)
        {
            REQUIRE(param1 == 1);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implManyParamInterface->_getPublisher().publishSig1(1);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed ManyParamInterface Test emit sig1" << std::endl;
    }
    SECTION("Test emit sig2")
    {
        std::cout<<"ManyParamInterface Test emit sig2" << std::endl;
        std::atomic<bool> issig2Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted](int param1, int param2)
        {
            REQUIRE(param1 == 1);
            REQUIRE(param2 == 1);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implManyParamInterface->_getPublisher().publishSig2(1, 1);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed ManyParamInterface Test emit sig2" << std::endl;
    }
    SECTION("Test emit sig3")
    {
        std::cout<<"ManyParamInterface Test emit sig3" << std::endl;
        std::atomic<bool> issig3Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig3(
        [&m_wait, &issig3Emitted](int param1, int param2, int param3)
        {
            REQUIRE(param1 == 1);
            REQUIRE(param2 == 1);
            REQUIRE(param3 == 1);
            issig3Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implManyParamInterface->_getPublisher().publishSig3(1, 1, 1);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig3Emitted ]() {return issig3Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed ManyParamInterface Test emit sig3" << std::endl;
    }
    SECTION("Test emit sig4")
    {
        std::cout<<"ManyParamInterface Test emit sig4" << std::endl;
        std::atomic<bool> issig4Emitted = false;

        clientManyParamInterface->_getPublisher().subscribeToSig4(
        [&m_wait, &issig4Emitted](int param1, int param2, int param3, int param4)
        {
            REQUIRE(param1 == 1);
            REQUIRE(param2 == 1);
            REQUIRE(param3 == 1);
            REQUIRE(param4 == 1);
            issig4Emitted  = true;
            m_wait.notify_all();
        });

         std::cout<<"publishing signal" << std::endl;
         implManyParamInterface->_getPublisher().publishSig4(1, 1, 1, 1);
        std::cout<<"will wait for the singal" << std::endl;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig4Emitted ]() {return issig4Emitted   == true; }));
        lock.unlock();
        std::cout<<"TEST ENDED, disconnect will be performed ManyParamInterface Test emit sig4" << std::endl;
    }
    SECTION("Test method func1")
    {
        std::cout<<"ManyParamInterface Test method func1" << std::endl;
        [[maybe_unused]] auto result =  clientManyParamInterface->func1(0);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func1 async")
    {
        std::cout<<"ManyParamInterface Test async method func1" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func1Async(0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func1 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func1Async(0,[&finished, &m_wait](int value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
    }
    SECTION("Test method func2")
    {
        std::cout<<"ManyParamInterface Test method func2" << std::endl;
        [[maybe_unused]] auto result =  clientManyParamInterface->func2(0, 0);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func2 async")
    {
        std::cout<<"ManyParamInterface Test async method func2" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func2Async(0, 0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func2 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func2Async(0, 0,[&finished, &m_wait](int value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
    }
    SECTION("Test method func3")
    {
        std::cout<<"ManyParamInterface Test method func3" << std::endl;
        [[maybe_unused]] auto result =  clientManyParamInterface->func3(0, 0, 0);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func3 async")
    {
        std::cout<<"ManyParamInterface Test async method func3" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func3Async(0, 0, 0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func3 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func3Async(0, 0, 0,[&finished, &m_wait](int value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
    }
    SECTION("Test method func4")
    {
        std::cout<<"ManyParamInterface Test method func4" << std::endl;
        [[maybe_unused]] auto result =  clientManyParamInterface->func4(0, 0, 0, 0);
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method func4 async")
    {
        std::cout<<"ManyParamInterface Test async method func4" << std::endl;
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func4Async(0, 0, 0, 0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func4 async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientManyParamInterface->func4Async(0, 0, 0, 0,[&finished, &m_wait](int value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == 0); 
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
    serviceManyParamInterface.reset();
    clientManyParamInterface.reset();
}
