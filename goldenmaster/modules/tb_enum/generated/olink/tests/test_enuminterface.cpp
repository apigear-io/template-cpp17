#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_enum/generated/core/test_struct_helper.h"
#include "tb_enum/implementation/enuminterface.h"
#include "tb_enum/generated/olink/enuminterfaceclient.h"
#include "tb_enum/generated/olink/enuminterfaceservice.h"


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
using namespace Test::TbEnum;

TEST_CASE("olink  tb.enum EnumInterface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientEnumInterface = std::make_shared<Test::TbEnum::olink::EnumInterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implEnumInterface = std::make_shared<Test::TbEnum::EnumInterface>();
    auto serviceEnumInterface = std::make_shared<Test::TbEnum::olink::EnumInterfaceService>(implEnumInterface, remote_registry);
    remote_registry.addSource(serviceEnumInterface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientEnumInterface);
    clientNode->linkRemote(clientEnumInterface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    SECTION("Test setting prop0")
    {
        std::atomic<bool> isprop0Changed = false;
        clientEnumInterface->_getPublisher().subscribeToProp0Changed(
        [&isprop0Changed, &m_wait ](auto value){
            isprop0Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbEnum::Enum0Enum::value1;
        clientEnumInterface->setProp0(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop0Changed]() {return isprop0Changed  == true; }));
        lock.unlock();
        REQUIRE(implEnumInterface->getProp0() == test_value);
        REQUIRE(clientEnumInterface->getProp0() == test_value);
    }
    SECTION("Test setting prop1")
    {
        std::atomic<bool> isprop1Changed = false;
        clientEnumInterface->_getPublisher().subscribeToProp1Changed(
        [&isprop1Changed, &m_wait ](auto value){
            isprop1Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbEnum::Enum1Enum::value2;
        clientEnumInterface->setProp1(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop1Changed]() {return isprop1Changed  == true; }));
        lock.unlock();
        REQUIRE(implEnumInterface->getProp1() == test_value);
        REQUIRE(clientEnumInterface->getProp1() == test_value);
    }
    SECTION("Test setting prop2")
    {
        std::atomic<bool> isprop2Changed = false;
        clientEnumInterface->_getPublisher().subscribeToProp2Changed(
        [&isprop2Changed, &m_wait ](auto value){
            isprop2Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbEnum::Enum2Enum::value1;
        clientEnumInterface->setProp2(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop2Changed]() {return isprop2Changed  == true; }));
        lock.unlock();
        REQUIRE(implEnumInterface->getProp2() == test_value);
        REQUIRE(clientEnumInterface->getProp2() == test_value);
    }
    SECTION("Test setting prop3")
    {
        std::atomic<bool> isprop3Changed = false;
        clientEnumInterface->_getPublisher().subscribeToProp3Changed(
        [&isprop3Changed, &m_wait ](auto value){
            isprop3Changed  = true;
            m_wait.notify_all();
        });
        auto test_value = TbEnum::Enum3Enum::value2;
        clientEnumInterface->setProp3(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&isprop3Changed]() {return isprop3Changed  == true; }));
        lock.unlock();
        REQUIRE(implEnumInterface->getProp3() == test_value);
        REQUIRE(clientEnumInterface->getProp3() == test_value);
    }
    SECTION("Test emit sig0")
    {
        std::atomic<bool> issig0Emitted = false;

        clientEnumInterface->_getPublisher().subscribeToSig0(
        [&m_wait, &issig0Emitted](TbEnum::Enum0Enum param0)
        {
            REQUIRE(param0 == TbEnum::Enum0Enum::value1);
            issig0Emitted  = true;
            m_wait.notify_all();
        });

         implEnumInterface->_getPublisher().publishSig0(TbEnum::Enum0Enum::value1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig0Emitted ]() {return issig0Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig1")
    {
        std::atomic<bool> issig1Emitted = false;

        clientEnumInterface->_getPublisher().subscribeToSig1(
        [&m_wait, &issig1Emitted](TbEnum::Enum1Enum param1)
        {
            REQUIRE(param1 == TbEnum::Enum1Enum::value2);
            issig1Emitted  = true;
            m_wait.notify_all();
        });

         implEnumInterface->_getPublisher().publishSig1(TbEnum::Enum1Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig1Emitted ]() {return issig1Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig2")
    {
        std::atomic<bool> issig2Emitted = false;

        clientEnumInterface->_getPublisher().subscribeToSig2(
        [&m_wait, &issig2Emitted](TbEnum::Enum2Enum param2)
        {
            REQUIRE(param2 == TbEnum::Enum2Enum::value1);
            issig2Emitted  = true;
            m_wait.notify_all();
        });

         implEnumInterface->_getPublisher().publishSig2(TbEnum::Enum2Enum::value1);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig2Emitted ]() {return issig2Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test emit sig3")
    {
        std::atomic<bool> issig3Emitted = false;

        clientEnumInterface->_getPublisher().subscribeToSig3(
        [&m_wait, &issig3Emitted](TbEnum::Enum3Enum param3)
        {
            REQUIRE(param3 == TbEnum::Enum3Enum::value2);
            issig3Emitted  = true;
            m_wait.notify_all();
        });

         implEnumInterface->_getPublisher().publishSig3(TbEnum::Enum3Enum::value2);
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&issig3Emitted ]() {return issig3Emitted   == true; }));
        lock.unlock();
    }
    SECTION("Test method func0")
    {
        [[maybe_unused]] auto result = clientEnumInterface->func0(TbEnum::Enum0Enum::value0);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func0 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientEnumInterface->func0Async(TbEnum::Enum0Enum::value0);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbEnum::Enum0Enum::value0); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1")
    {
        [[maybe_unused]] auto result = clientEnumInterface->func1(TbEnum::Enum1Enum::value1);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func1 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientEnumInterface->func1Async(TbEnum::Enum1Enum::value1);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbEnum::Enum1Enum::value1); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2")
    {
        [[maybe_unused]] auto result = clientEnumInterface->func2(TbEnum::Enum2Enum::value2);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func2 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientEnumInterface->func2Async(TbEnum::Enum2Enum::value2);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbEnum::Enum2Enum::value2); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func3")
    {
        [[maybe_unused]] auto result = clientEnumInterface->func3(TbEnum::Enum3Enum::value3);
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method func3 async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = clientEnumInterface->func3Async(TbEnum::Enum3Enum::value3);
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        REQUIRE(return_value == TbEnum::Enum3Enum::value3); 
        // CHECK EFFECTS OF YOUR METHOD HERE
    }

    clientNode->unlinkRemote(clientEnumInterface->olinkObjectName());
    remote_registry.removeSource(serviceEnumInterface->olinkObjectName());
    client_registry.removeSink(clientEnumInterface->olinkObjectName());
    serviceEnumInterface.reset();
    clientEnumInterface.reset();
}
