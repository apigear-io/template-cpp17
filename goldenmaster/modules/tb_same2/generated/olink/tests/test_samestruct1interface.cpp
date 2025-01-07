#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same2/generated/core/test_struct_helper.h"
#include "tb_same2/implementation/samestruct1interface.h"
#include "tb_same2/generated/olink/samestruct1interfaceclient.h"
#include "tb_same2/generated/olink/samestruct1interfaceservice.h"


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
using namespace Test::TbSame2;

TEST_CASE("olink  tb.same2 SameStruct1Interface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientSameStruct1Interface = std::make_shared<Test::TbSame2::olink::SameStruct1InterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implSameStruct1Interface = std::make_shared<Test::TbSame2::SameStruct1Interface>();
    auto serviceSameStruct1Interface = std::make_shared<Test::TbSame2::olink::SameStruct1InterfaceService>(implSameStruct1Interface, remote_registry);
    remote_registry.addSource(serviceSameStruct1Interface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientSameStruct1Interface);
    clientNode->linkRemote(clientSameStruct1Interface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientSameStruct1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame2::Struct1();
        TbSame2::fillTestStruct1(test_value);
        clientSameStruct1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameStruct1Interface->getProp1() == test_value);
        REQUIRE(clientSameStruct1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;
        auto local_param1_struct = TbSame2::Struct1();
        TbSame2::fillTestStruct1(local_param1_struct);

        clientSameStruct1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted, &local_param1_struct](const TbSame2::Struct1& param1)
        {
            REQUIRE(param1 ==local_param1_struct);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameStruct1Interface->_getPublisher().publishSig1(local_param1_struct);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientSameStruct1Interface->func1(TbSame2::Struct1());
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameStruct1Interface->func1Async(TbSame2::Struct1());
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Struct1()); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    clientNode->unlinkRemote(clientSameStruct1Interface->olinkObjectName());
    remote_registry.removeSource(serviceSameStruct1Interface->olinkObjectName());
    client_registry.removeSink(clientSameStruct1Interface->olinkObjectName());
    serviceSameStruct1Interface.reset();
    clientSameStruct1Interface.reset();
}
