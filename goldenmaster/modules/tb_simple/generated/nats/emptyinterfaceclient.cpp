#include "tb_simple/generated/nats/emptyinterfaceclient.h"
#include "tb_simple/generated/core/emptyinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 0;
const uint32_t  expectedPropertiesSubscriptions = 0;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<EmptyInterfaceClient> EmptyInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<EmptyInterfaceClient> obj(new EmptyInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> EmptyInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

EmptyInterfaceClient::EmptyInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<EmptyInterfacePublisher>())
{}

void EmptyInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

EmptyInterfaceClient::~EmptyInterfaceClient() = default;

void EmptyInterfaceClient::onConnected()
{
}


IEmptyInterfacePublisher& EmptyInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
