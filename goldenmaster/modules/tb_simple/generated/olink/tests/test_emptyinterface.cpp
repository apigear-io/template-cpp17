#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "tb_simple/generated/core/test_struct_helper.h"
#include "tb_simple/implementation/emptyinterface.h"
#include "tb_simple/generated/olink/emptyinterfaceclient.h"
#include "tb_simple/generated/olink/emptyinterfaceservice.h"


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
using namespace Test::TbSimple;

TEST_CASE("olink  tb.simple EmptyInterface tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto clientEmptyInterface = std::make_shared<Test::TbSimple::olink::EmptyInterfaceClient>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto implEmptyInterface = std::make_shared<Test::TbSimple::EmptyInterface>();
    auto serviceEmptyInterface = std::make_shared<Test::TbSimple::olink::EmptyInterfaceService>(implEmptyInterface, remote_registry);
    remote_registry.addSource(serviceEmptyInterface);

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(clientEmptyInterface);
    clientNode->linkRemote(clientEmptyInterface->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);
    clientNode->unlinkRemote(clientEmptyInterface->olinkObjectName());
    remote_registry.removeSource(serviceEmptyInterface->olinkObjectName());
    client_registry.removeSink(clientEmptyInterface->olinkObjectName());
    serviceEmptyInterface.reset();
    clientEmptyInterface.reset();
}
