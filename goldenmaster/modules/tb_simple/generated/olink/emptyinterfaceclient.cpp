

#include "tb_simple/generated/olink/emptyinterfaceclient.h"
#include "tb_simple/generated/core/emptyinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.EmptyInterface";
}

EmptyInterfaceClient::EmptyInterfaceClient()
    : m_publisher(std::make_unique<EmptyInterfacePublisher>())
{}

void EmptyInterfaceClient::applyState(const nlohmann::json& fields) 
{
    // no properties to apply state
    (void) fields;
}

void EmptyInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{// no properties to apply state
    (void) propertyName;
    (void) value;
}

std::string EmptyInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void EmptyInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    (void) args;
    (void) signalName;
}

void EmptyInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void EmptyInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void EmptyInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool EmptyInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

IEmptyInterfacePublisher& EmptyInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
