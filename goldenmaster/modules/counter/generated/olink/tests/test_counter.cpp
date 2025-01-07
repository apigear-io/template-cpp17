#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "counter/generated/core/test_struct_helper.h"
#include "counter/implementation/counter.h"
#include "counter/generated/olink/counterclient.h"
#include "counter/generated/olink/counterservice.h"

#include "custom_types/generated/core/test_struct_helper.h"
#include "extern_types/generated/core/test_struct_helper.h"

#include "olink/clientregistry.h"
#include "olink/clientnode.h"
#include "olink/remotenode.h"
#include "olink/remoteregistry.h"

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 1000;//in ms
}

using namespace Test;
using namespace Test::Counter;

TEST_CASE("olink  counter Counter tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientCounter = std::make_shared<Test::Counter::olink::CounterClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implCounter = std::make_shared<Test::Counter::Counter>();
    auto serviceCounter = std::make_shared<Test::Counter::olink::CounterService>(implCounter, remote_registry);
    remote_registry.addSource(serviceCounter);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientCounter);
    clientNode->linkRemote(clientCounter->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
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
    SECTION("Test setting vectorArray")
    {
        std::atomic<bool> isvectorArrayChanged = false;
        clientCounter->_getPublisher().subscribeToVectorArrayChanged(
        [&isvectorArrayChanged, &m_wait ](auto value){
            isvectorArrayChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = std::list<Test::CustomTypes::Vector3D>();
        auto element = CustomTypes::Vector3D();
        CustomTypes::fillTestVector3D(element);
        test_value.push_back(element);
        clientCounter->setVectorArray(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isvectorArrayChanged]() {return isvectorArrayChanged  == true; }));
        lock.unlock();
        REQUIRE(implCounter->getVectorArray() == test_value);
        REQUIRE(clientCounter->getVectorArray() == test_value);
    }
    SECTION("Test emit valueChanged")
    {
        std::atomic<bool> isvalueChangedEmitted = false;
        auto local_vector_struct = Test::CustomTypes::Vector3D();
        CustomTypes::fillTestVector3D(local_vector_struct);
        auto local_vector_array_array = std::list<Test::CustomTypes::Vector3D>();
        auto element_vectorArray = CustomTypes::Vector3D();
        CustomTypes::fillTestVector3D(element_vectorArray);
        local_vector_array_array.push_back(element_vectorArray);
        auto local_extern_vector_array_array = std::list<Eigen::Vector3f>();
        local_extern_vector_array_array.push_back(Eigen::Vector3f(0,0,0));

        clientCounter->_getPublisher().subscribeToValueChanged(
        [&m_wait, &isvalueChangedEmitted, &local_vector_struct, &local_vector_array_array, &local_extern_vector_array_array](const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray)
        {
            REQUIRE(vector ==local_vector_struct);
           // Make sure the comparison is valid for extern type.
           // REQUIRE(extern_vector ==  Eigen::Vector3f(0,0,0));
            REQUIRE(vectorArray == local_vector_array_array);
           // Make sure the comparison is valid for extern type.
           // REQUIRE(extern_vectorArray ==  std::list<Eigen::Vector3f>());
            isvalueChangedEmitted  = true;
            m_wait.notify_all();
        });

         implCounter->_getPublisher().publishValueChanged(local_vector_struct, Eigen::Vector3f(0,0,0), local_vector_array_array, local_extern_vector_array_array);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isvalueChangedEmitted ]() {return isvalueChangedEmitted   == true; }));
        lock.unlock();
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
    SECTION("Test method incrementArray")
    {
        [[maybe_unused]] auto result = clientCounter->incrementArray(std::list<Eigen::Vector3f>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method incrementArray async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientCounter->incrementArrayAsync(std::list<Eigen::Vector3f>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        //REQUIRE(return_value == std::list<Eigen::Vector3f>()); // Make sure the comparison is valid for extern type. 
        // CHECK EFFECTS OF YOUR METHOD HERE
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
    SECTION("Test method decrementArray")
    {
        [[maybe_unused]] auto result = clientCounter->decrementArray(std::list<Test::CustomTypes::Vector3D>());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method decrementArray async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientCounter->decrementArrayAsync(std::list<Test::CustomTypes::Vector3D>());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Test::CustomTypes::Vector3D>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    clientNode->unlinkRemote(clientCounter->olinkObjectName());
    remote_registry.removeSource(serviceCounter->olinkObjectName());
    client_registry.removeSink(clientCounter->olinkObjectName());
    serviceCounter.reset();
    clientCounter.reset();
}
