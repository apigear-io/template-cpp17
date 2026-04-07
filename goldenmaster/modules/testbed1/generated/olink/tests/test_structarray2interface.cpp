#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "testbed1/generated/core/test_struct_helper.h"
#include "testbed1/implementation/structarray2interface.h"
#include "testbed1/generated/olink/structarray2interfaceclient.h"
#include "testbed1/generated/olink/structarray2interfaceservice.h"


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
using namespace Test::Testbed1;

TEST_CASE("olink  testbed1 StructArray2Interface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientStructArray2Interface = std::make_shared<Test::Testbed1::olink::StructArray2InterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implStructArray2Interface = std::make_shared<Test::Testbed1::StructArray2Interface>();
    auto serviceStructArray2Interface = std::make_shared<Test::Testbed1::olink::StructArray2InterfaceService>(implStructArray2Interface, remote_registry);
    remote_registry.addSource(serviceStructArray2Interface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientStructArray2Interface);
    clientNode->linkRemote(clientStructArray2Interface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    SECTION("Test setting propBool")
    {
        std::atomic<bool> ispropBoolChanged = false;
        clientStructArray2Interface->_getPublisher().subscribeToPropBoolChanged(
        [&ispropBoolChanged, &m_wait ](auto value){
            ispropBoolChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructBoolWithArray();
        Testbed1::fillTestStructBoolWithArray(test_value);
        clientStructArray2Interface->setPropBool(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropBoolChanged]() {return ispropBoolChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArray2Interface->getPropBool() == test_value);
        REQUIRE(clientStructArray2Interface->getPropBool() == test_value);
    }
    SECTION("Test setting propInt")
    {
        std::atomic<bool> ispropIntChanged = false;
        clientStructArray2Interface->_getPublisher().subscribeToPropIntChanged(
        [&ispropIntChanged, &m_wait ](auto value){
            ispropIntChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructIntWithArray();
        Testbed1::fillTestStructIntWithArray(test_value);
        clientStructArray2Interface->setPropInt(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropIntChanged]() {return ispropIntChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArray2Interface->getPropInt() == test_value);
        REQUIRE(clientStructArray2Interface->getPropInt() == test_value);
    }
    SECTION("Test setting propFloat")
    {
        std::atomic<bool> ispropFloatChanged = false;
        clientStructArray2Interface->_getPublisher().subscribeToPropFloatChanged(
        [&ispropFloatChanged, &m_wait ](auto value){
            ispropFloatChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructFloatWithArray();
        Testbed1::fillTestStructFloatWithArray(test_value);
        clientStructArray2Interface->setPropFloat(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropFloatChanged]() {return ispropFloatChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArray2Interface->getPropFloat() == test_value);
        REQUIRE(clientStructArray2Interface->getPropFloat() == test_value);
    }
    SECTION("Test setting propString")
    {
        std::atomic<bool> ispropStringChanged = false;
        clientStructArray2Interface->_getPublisher().subscribeToPropStringChanged(
        [&ispropStringChanged, &m_wait ](auto value){
            ispropStringChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructStringWithArray();
        Testbed1::fillTestStructStringWithArray(test_value);
        clientStructArray2Interface->setPropString(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropStringChanged]() {return ispropStringChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArray2Interface->getPropString() == test_value);
        REQUIRE(clientStructArray2Interface->getPropString() == test_value);
    }
    SECTION("Test setting propEnum")
    {
        std::atomic<bool> ispropEnumChanged = false;
        clientStructArray2Interface->_getPublisher().subscribeToPropEnumChanged(
        [&ispropEnumChanged, &m_wait ](auto value){
            ispropEnumChanged  = true;
            m_wait.notify_all();
        });
        auto test_value = Testbed1::StructEnumWithArray();
        Testbed1::fillTestStructEnumWithArray(test_value);
        clientStructArray2Interface->setPropEnum(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&ispropEnumChanged]() {return ispropEnumChanged  == true; }));
        lock.unlock();
        REQUIRE(implStructArray2Interface->getPropEnum() == test_value);
        REQUIRE(clientStructArray2Interface->getPropEnum() == test_value);
    }
    SECTION("Test emit sigBool")
    {
        std::atomic<bool> issigBoolEmitted = false;
        auto local_param_bool_struct = Testbed1::StructBoolWithArray();
        Testbed1::fillTestStructBoolWithArray(local_param_bool_struct);

        clientStructArray2Interface->_getPublisher().subscribeToSigBool(
        [&m_wait, &issigBoolEmitted, &local_param_bool_struct](const Testbed1::StructBoolWithArray& paramBool)
        {
            REQUIRE(paramBool ==local_param_bool_struct);
            issigBoolEmitted  = true;
            m_wait.notify_all();
        });

         implStructArray2Interface->_getPublisher().publishSigBool(local_param_bool_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigBoolEmitted ]() {return issigBoolEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigInt")
    {
        std::atomic<bool> issigIntEmitted = false;
        auto local_param_int_struct = Testbed1::StructIntWithArray();
        Testbed1::fillTestStructIntWithArray(local_param_int_struct);

        clientStructArray2Interface->_getPublisher().subscribeToSigInt(
        [&m_wait, &issigIntEmitted, &local_param_int_struct](const Testbed1::StructIntWithArray& paramInt)
        {
            REQUIRE(paramInt ==local_param_int_struct);
            issigIntEmitted  = true;
            m_wait.notify_all();
        });

         implStructArray2Interface->_getPublisher().publishSigInt(local_param_int_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigIntEmitted ]() {return issigIntEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigFloat")
    {
        std::atomic<bool> issigFloatEmitted = false;
        auto local_param_float_struct = Testbed1::StructFloatWithArray();
        Testbed1::fillTestStructFloatWithArray(local_param_float_struct);

        clientStructArray2Interface->_getPublisher().subscribeToSigFloat(
        [&m_wait, &issigFloatEmitted, &local_param_float_struct](const Testbed1::StructFloatWithArray& paramFloat)
        {
            REQUIRE(paramFloat ==local_param_float_struct);
            issigFloatEmitted  = true;
            m_wait.notify_all();
        });

         implStructArray2Interface->_getPublisher().publishSigFloat(local_param_float_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigFloatEmitted ]() {return issigFloatEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sigString")
    {
        std::atomic<bool> issigStringEmitted = false;
        auto local_param_string_struct = Testbed1::StructStringWithArray();
        Testbed1::fillTestStructStringWithArray(local_param_string_struct);

        clientStructArray2Interface->_getPublisher().subscribeToSigString(
        [&m_wait, &issigStringEmitted, &local_param_string_struct](const Testbed1::StructStringWithArray& paramString)
        {
            REQUIRE(paramString ==local_param_string_struct);
            issigStringEmitted  = true;
            m_wait.notify_all();
        });

         implStructArray2Interface->_getPublisher().publishSigString(local_param_string_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issigStringEmitted ]() {return issigStringEmitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method funcBool")
    {
        [[maybe_unused]] auto result = clientStructArray2Interface->funcBool(Testbed1::StructBoolWithArray());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcBool async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcBoolAsync(Testbed1::StructBoolWithArray());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructBool>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcBool async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcBoolAsync(Testbed1::StructBoolWithArray(),[&finished, &m_wait](std::list<StructBool> value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructBool>()); 
        
    }
    SECTION("Test method funcInt")
    {
        [[maybe_unused]] auto result = clientStructArray2Interface->funcInt(Testbed1::StructIntWithArray());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcInt async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcIntAsync(Testbed1::StructIntWithArray());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructInt>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcInt async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcIntAsync(Testbed1::StructIntWithArray(),[&finished, &m_wait](std::list<StructInt> value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructInt>()); 
        
    }
    SECTION("Test method funcFloat")
    {
        [[maybe_unused]] auto result = clientStructArray2Interface->funcFloat(Testbed1::StructFloatWithArray());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcFloat async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcFloatAsync(Testbed1::StructFloatWithArray());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructFloat>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcFloat async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcFloatAsync(Testbed1::StructFloatWithArray(),[&finished, &m_wait](std::list<StructFloat> value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructFloat>()); 
        
    }
    SECTION("Test method funcString")
    {
        [[maybe_unused]] auto result = clientStructArray2Interface->funcString(Testbed1::StructStringWithArray());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcString async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcStringAsync(Testbed1::StructStringWithArray());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructString>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcString async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcStringAsync(Testbed1::StructStringWithArray(),[&finished, &m_wait](std::list<StructString> value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::StructString>()); 
        
    }
    SECTION("Test method funcEnum")
    {
        [[maybe_unused]] auto result = clientStructArray2Interface->funcEnum(Testbed1::StructEnumWithArray());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method funcEnum async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcEnumAsync(Testbed1::StructEnumWithArray());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::Enum0Enum>()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method funcEnum async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientStructArray2Interface->funcEnumAsync(Testbed1::StructEnumWithArray(),[&finished, &m_wait](std::list<Enum0Enum> value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == std::list<Testbed1::Enum0Enum>()); 
        
    }
    clientNode->unlinkRemote(clientStructArray2Interface->olinkObjectName());
    remote_registry.removeSource(serviceStructArray2Interface->olinkObjectName());
    client_registry.removeSink(clientStructArray2Interface->olinkObjectName());
    serviceStructArray2Interface.reset();
    clientStructArray2Interface.reset();
}
