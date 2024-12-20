#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/emptyinterface.h"
#include "tb_simple/generated/nats/emptyinterfaceclient.h"
#include "tb_simple/generated/nats/emptyinterfaceservice.h"


#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace Test;
using namespace Test::TbSimple;

TEST_CASE("Nats  tb.simple EmptyInterface tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto implEmptyInterface = std::make_shared<Test::TbSimple::EmptyInterface>();
    auto serviceEmptyInterface = Nats::EmptyInterfaceService::create(implEmptyInterface, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [serviceEmptyInterface]() {return  serviceEmptyInterface->_is_ready();}));
    lock.unlock();
    service->flush();

    auto clientEmptyInterface = Nats::EmptyInterfaceClient::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [clientEmptyInterface]() {return clientEmptyInterface->_is_ready(); }));
    lock.unlock();
    client->flush();

    serviceEmptyInterface.reset();
    clientEmptyInterface.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
