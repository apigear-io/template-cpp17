#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed2/generated/core/test_struct_helper.h"
#include "testbed2/implementation/nestedstruct2interface.h"
#include "testbed2/generated/olink/nestedstruct2interfaceclient.h"
#include "testbed2/generated/olink/nestedstruct2interfaceservice.h"


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
using namespace Test::Testbed2;

TEST_CASE("olink  testbed2 NestedStruct2Interface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientNestedStruct2Interface = std::make_shared<Test::Testbed2::olink::NestedStruct2InterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implNestedStruct2Interface = std::make_shared<Test::Testbed2::NestedStruct2Interface>();
    auto serviceNestedStruct2Interface = std::make_shared<Test::Testbed2::olink::NestedStruct2InterfaceService>(implNestedStruct2Interface, remote_registry);
    remote_registry.addSource(serviceNestedStruct2Interface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientNestedStruct2Interface);
    clientNode->linkRemote(clientNestedStruct2Interface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientNestedStruct2Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(test_value);
        clientNestedStruct2Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct2Interface->getProp1() == test_value);
        REQUIRE(clientNestedStruct2Interface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientNestedStruct2Interface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(test_value);
        clientNestedStruct2Interface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct2Interface->getProp2() == test_value);
        REQUIRE(clientNestedStruct2Interface->getProp2() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);

        clientNestedStruct2Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const Testbed2::NestedStruct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct2Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);
        auto local_param2_struct = Testbed2::NestedStruct2();
        Testbed2::fillTestNestedStruct2(local_param2_struct);

        clientNestedStruct2Interface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted, &local_param1_struct, &local_param2_struct](const Testbed2::NestedStruct1& param1, const Testbed2::NestedStruct2& param2)
        {
            REQUIRE(param1 ==local_param1_struct);
            REQUIRE(param2 ==local_param2_struct);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct2Interface->_getPublisher().publishSig2(local_param1_struct, local_param2_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientNestedStruct2Interface->func1(Testbed2::NestedStruct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct2Interface->func1Async(Testbed2::NestedStruct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func1 async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct2Interface->func1Async(Testbed2::NestedStruct1(),[&finished, &m_wait](NestedStruct1 value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result = clientNestedStruct2Interface->func2(Testbed2::NestedStruct1(), Testbed2::NestedStruct2());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct2Interface->func2Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func2 async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct2Interface->func2Async(Testbed2::NestedStruct1(), Testbed2::NestedStruct2(),[&finished, &m_wait](NestedStruct1 value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        
    }
    clientNode->unlinkRemote(clientNestedStruct2Interface->olinkObjectName());
    remote_registry.removeSource(serviceNestedStruct2Interface->olinkObjectName());
    client_registry.removeSink(clientNestedStruct2Interface->olinkObjectName());
    serviceNestedStruct2Interface.reset();
    clientNestedStruct2Interface.reset();
}
