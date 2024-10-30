#include "tb_simple/generated/nats/emptyinterfaceclient.h"
#include "tb_simple/generated/core/emptyinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;


EmptyInterfaceClient::EmptyInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<EmptyInterfacePublisher>())
{
}

EmptyInterfaceClient::~EmptyInterfaceClient()
{
}


IEmptyInterfacePublisher& EmptyInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
