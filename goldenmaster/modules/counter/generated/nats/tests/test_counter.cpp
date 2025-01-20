#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "counter/generated/core/test_struct_helper.h"
#include "counter/implementation/counter.h"
#include "counter/generated/nats/counterclient.h"
#include "counter/generated/nats/counterservice.h"

#include "custom_types/generated/core/test_struct_helper.h"
#include "extern_types/generated/core/test_struct_helper.h"

#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::Counter;

TEST_CASE("Nats  counter Counter tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implCounter = std::make_shared<Test::Counter::Counter>();
    auto serviceCounter = Nats::CounterService::create(implCounter, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceCounter]() {return  serviceCounter->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientCounter = Nats::CounterClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientCounter]() {return clientCounter->_is_ready(); }));
    lock.unlock();
    client->flush();
    SECTION("Test setting vector")
    {
        std::atomic<bool> isvectorChanged = false;
        clientCounter->_getPublisher().subscribeToVectorChanged(
        [&isvectorChanged, &m_wait ](auto value){
            isvectorChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Test::CustomTypes::Vector3D();
        CustomTypes::fillTestVector3D(test_value);
        clientCounter->setVector(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isvectorChanged]() {return isvectorChanged  == true; }));
        lock.unlock();
        REQUIRE(implCounter->getVector() == test_value);
        REQUIRE(clientCounter->getVector() == test_value);
    }
    SECTION("Test method increment")
    {
        [[maybe_unused]] auto result = clientCounter->increment(Eigen::Vector3f(0,0,0));
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method increment async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientCounter->incrementAsync(Eigen::Vector3f(0,0,0));
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        //REQUIRE(return_value == Eigen::Vector3f(0,0,0)); // Make sure the comparison is valid for extern type. 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method increment async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientCounter->incrementAsync(Eigen::Vector3f(0,0,0),
            [&finished, &m_wait](Eigen::Vector3f value)
            { (void) value;// Make sure the comparison is valid for extern type.
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    SECTION("Test method decrement")
    {
        [[maybe_unused]] auto result = clientCounter->decrement(Test::CustomTypes::Vector3D());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method decrement async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientCounter->decrementAsync(Test::CustomTypes::Vector3D());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Test::CustomTypes::Vector3D()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method decrement async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientCounter->decrementAsync(Test::CustomTypes::Vector3D(),
            [&finished, &m_wait](Test::CustomTypes::Vector3D value)
            {
                REQUIRE(value == Test::CustomTypes::Vector3D());
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }

    serviceCounter.reset();
    clientCounter.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
