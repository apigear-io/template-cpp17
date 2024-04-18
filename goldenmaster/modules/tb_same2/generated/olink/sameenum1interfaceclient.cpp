

#include "tb_same2/generated/olink/sameenum1interfaceclient.h"
#include "tb_same2/generated/core/sameenum1interface.publisher.h"
#include "tb_same2/generated/core/tb_same2.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSame2;
using namespace Test::TbSame2::olink;

namespace 
{
const std::string interfaceId = "tb.same2.SameEnum1Interface";
}

SameEnum1InterfaceClient::SameEnum1InterfaceClient()
    : m_publisher(std::make_unique<SameEnum1InterfacePublisher>())
{}

void SameEnum1InterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<Enum1Enum>());
    }
}

void SameEnum1InterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "prop1") {
        setProp1Local(value.get<Enum1Enum>());
    }
}

void SameEnum1InterfaceClient::setProp1(Enum1Enum prop1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    m_node->setRemoteProperty(propertyId, prop1);
}

void SameEnum1InterfaceClient::setProp1Local(Enum1Enum prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum SameEnum1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

Enum1Enum SameEnum1InterfaceClient::func1(Enum1Enum param1)
{
    Enum1Enum value(func1Async(param1).get());
    return value;
}

std::future<Enum1Enum> SameEnum1InterfaceClient::func1Async(Enum1Enum param1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<Enum1Enum>{};
    }
    std::shared_ptr<std::promise<Enum1Enum>> resultPromise = std::make_shared<std::promise<Enum1Enum>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func1");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const Enum1Enum& value = arg.value.get<Enum1Enum>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string SameEnum1InterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void SameEnum1InterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sig1") {
        m_publisher->publishSig1(args[0].get<Enum1Enum>());   
        return;
    }
}

void SameEnum1InterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void SameEnum1InterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void SameEnum1InterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool SameEnum1InterfaceClient::isReady() const
{
    return m_node != nullptr;
}

ISameEnum1InterfacePublisher& SameEnum1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
