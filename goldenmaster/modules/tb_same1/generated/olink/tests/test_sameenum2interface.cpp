#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same1/generated/core/test_struct_helper.h"
#include "tb_same1/implementation/sameenum2interface.h"
#include "tb_same1/generated/olink/sameenum2interfaceclient.h"
#include "tb_same1/generated/olink/sameenum2interfaceservice.h"


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
using namespace Test::TbSame1;

TEST_CASE("olink  tb.same1 SameEnum2Interface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientSameEnum2Interface = std::make_shared<Test::TbSame1::olink::SameEnum2InterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implSameEnum2Interface = std::make_shared<Test::TbSame1::SameEnum2Interface>();
    auto serviceSameEnum2Interface = std::make_shared<Test::TbSame1::olink::SameEnum2InterfaceService>(implSameEnum2Interface, remote_registry);
    remote_registry.addSource(serviceSameEnum2Interface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientSameEnum2Interface);
    clientNode->linkRemote(clientSameEnum2Interface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientSameEnum2Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame1::Enum1Enum::value2;
        clientSameEnum2Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameEnum2Interface->getProp1() == test_value);
        REQUIRE(clientSameEnum2Interface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientSameEnum2Interface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame1::Enum2Enum::value2;
        clientSameEnum2Interface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameEnum2Interface->getProp2() == test_value);
        REQUIRE(clientSameEnum2Interface->getProp2() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;

        clientSameEnum2Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](TbSame1::Enum1Enum param1)
        {
            REQUIRE(param1 == TbSame1::Enum1Enum::value2);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameEnum2Interface->_getPublisher().publishSig1(TbSame1::Enum1Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;

        clientSameEnum2Interface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted](TbSame1::Enum1Enum param1, TbSame1::Enum2Enum param2)
        {
            REQUIRE(param1 == TbSame1::Enum1Enum::value2);
            REQUIRE(param2 == TbSame1::Enum2Enum::value2);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implSameEnum2Interface->_getPublisher().publishSig2(TbSame1::Enum1Enum::value2, TbSame1::Enum2Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientSameEnum2Interface->func1(TbSame1::Enum1Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum2Interface->func1Async(TbSame1::Enum1Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func1 async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum2Interface->func1Async(TbSame1::Enum1Enum::value1,[&finished, &m_wait](Enum1Enum value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Enum1Enum::value1); 
        
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result = clientSameEnum2Interface->func2(TbSame1::Enum1Enum::value1, TbSame1::Enum2Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum2Interface->func2Async(TbSame1::Enum1Enum::value1, TbSame1::Enum2Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    SECTION("Test method func2 async with a callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum2Interface->func2Async(TbSame1::Enum1Enum::value1, TbSame1::Enum2Enum::value1,[&finished, &m_wait](Enum1Enum value){ (void) value;finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });
         
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame1::Enum1Enum::value1); 
        
    }
    clientNode->unlinkRemote(clientSameEnum2Interface->olinkObjectName());
    remote_registry.removeSource(serviceSameEnum2Interface->olinkObjectName());
    client_registry.removeSink(clientSameEnum2Interface->olinkObjectName());
    serviceSameEnum2Interface.reset();
    clientSameEnum2Interface.reset();
}
