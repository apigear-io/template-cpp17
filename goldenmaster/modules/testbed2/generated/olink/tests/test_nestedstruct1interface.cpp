#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed2/generated/core/test_struct_helper.h"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "testbed2/generated/olink/nestedstruct1interfaceclient.h"
#include "testbed2/generated/olink/nestedstruct1interfaceservice.h"


THIRD_PARTY_INCLUDES_START
#include "olink/clientregistry.h"
#include "olink/clientnode.h"
#include "olink/remotenode.h"
#include "olink/remoteregistry.h"
THIRD_PARTY_INCLUDES_END

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
using namespace Test::Testbed2;

TEST_CASE("olink  testbed2 NestedStruct1Interface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientNestedStruct1Interface = std::make_shared<Test::Testbed2::olink::NestedStruct1InterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implNestedStruct1Interface = std::make_shared<Test::Testbed2::NestedStruct1Interface>();
    auto serviceNestedStruct1Interface = std::make_shared<Test::Testbed2::olink::NestedStruct1InterfaceService>(implNestedStruct1Interface, remote_registry);
    remote_registry.addSource(serviceNestedStruct1Interface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientNestedStruct1Interface);
    clientNode->linkRemote(clientNestedStruct1Interface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientNestedStruct1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(test_value);
        clientNestedStruct1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implNestedStruct1Interface->getProp1() == test_value);
        REQUIRE(clientNestedStruct1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = Testbed2::NestedStruct1();
        Testbed2::fillTestNestedStruct1(local_param1_struct);

        clientNestedStruct1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const Testbed2::NestedStruct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implNestedStruct1Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcNoReturnValue")
    {
        clientNestedStruct1Interface->funcNoReturnValue(Testbed2::NestedStruct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcNoReturnValue async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct1Interface->funcNoReturnValueAsync(Testbed2::NestedStruct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        resultFuture.wait();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcNoReturnValue async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct1Interface->funcNoReturnValueAsync(Testbed2::NestedStruct1(),[&finished, &m_wait](){finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        resultFuture.wait();
        
    }
    SECTION("Test method funcNoParams")
    {
        [[maybe_unused]] auto result = clientNestedStruct1Interface->funcNoParams();
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcNoParams async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct1Interface->funcNoParamsAsync();
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcNoParams async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct1Interface->funcNoParamsAsync([&finished, &m_wait](NestedStruct1 value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientNestedStruct1Interface->func1(Testbed2::NestedStruct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientNestedStruct1Interface->func1Async(Testbed2::NestedStruct1());
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
        auto resultFuture = clientNestedStruct1Interface->func1Async(Testbed2::NestedStruct1(),[&finished, &m_wait](NestedStruct1 value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == Testbed2::NestedStruct1()); 
        
    }
    clientNode->unlinkRemote(clientNestedStruct1Interface->olinkObjectName());
    remote_registry.removeSource(serviceNestedStruct1Interface->olinkObjectName());
    client_registry.removeSink(clientNestedStruct1Interface->olinkObjectName());
    serviceNestedStruct1Interface.reset();
    clientNestedStruct1Interface.reset();
}
