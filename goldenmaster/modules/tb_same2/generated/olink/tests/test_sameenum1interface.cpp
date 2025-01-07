#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_same2/generated/core/test_struct_helper.h"
#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/olink/sameenum1interfaceclient.h"
#include "tb_same2/generated/olink/sameenum1interfaceservice.h"


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

TEST_CASE("olink  tb.same2 SameEnum1Interface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientSameEnum1Interface = std::make_shared<Test::TbSame2::olink::SameEnum1InterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implSameEnum1Interface = std::make_shared<Test::TbSame2::SameEnum1Interface>();
    auto serviceSameEnum1Interface = std::make_shared<Test::TbSame2::olink::SameEnum1InterfaceService>(implSameEnum1Interface, remote_registry);
    remote_registry.addSource(serviceSameEnum1Interface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientSameEnum1Interface);
    clientNode->linkRemote(clientSameEnum1Interface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientSameEnum1Interface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbSame2::Enum1Enum::value2;
        clientSameEnum1Interface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implSameEnum1Interface->getProp1() == test_value);
        REQUIRE(clientSameEnum1Interface->getProp1() == test_value);
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;

        clientSameEnum1Interface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](TbSame2::Enum1Enum param1)
        {
            REQUIRE(param1 == TbSame2::Enum1Enum::value2);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implSameEnum1Interface->_getPublisher().publishSig1(TbSame2::Enum1Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientSameEnum1Interface->func1(TbSame2::Enum1Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientSameEnum1Interface->func1Async(TbSame2::Enum1Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbSame2::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    clientNode->unlinkRemote(clientSameEnum1Interface->olinkObjectName());
    remote_registry.removeSource(serviceSameEnum1Interface->olinkObjectName());
    client_registry.removeSink(clientSameEnum1Interface->olinkObjectName());
    serviceSameEnum1Interface.reset();
    clientSameEnum1Interface.reset();
}
