

#include "tb_same2/generated/olink/samestruct1interfaceclient.h"
#include "tb_same2/generated/core/samestruct1interface.publisher.h"
#include "tb_same2/generated/core/tb_same2.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSame2;
using namespace Test::TbSame2::olink;

namespace 
{
const std::string interfaceId = "tb.same2.SameStruct1Interface";
}

SameStruct1InterfaceClient::SameStruct1InterfaceClient()
    : m_publisher(std::make_unique<SameStruct1InterfacePublisher>())
{}

void SameStruct1InterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<Struct1>());
    }
}

void SameStruct1InterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "prop1") {
        setProp1Local(value.get<Struct1>());
    }
}

void SameStruct1InterfaceClient::setProp1(const Struct1& prop1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    m_node->setRemoteProperty(propertyId, prop1);
}

void SameStruct1InterfaceClient::setProp1Local(const Struct1& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Struct1& SameStruct1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

Struct1 SameStruct1InterfaceClient::func1(const Struct1& param1)
{
    return func1Async(param1).get();
}

std::future<Struct1> SameStruct1InterfaceClient::func1Async(const Struct1& param1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<Struct1>{};
    }
    std::shared_ptr<std::promise<Struct1>> resultPromise = std::make_shared<std::promise<Struct1>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func1");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const Struct1& value = arg.value.get<Struct1>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string SameStruct1InterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void SameStruct1InterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sig1") {
        m_publisher->publishSig1(args[0].get<Struct1>());   
        return;
    }
}

void SameStruct1InterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void SameStruct1InterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void SameStruct1InterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool SameStruct1InterfaceClient::isReady() const
{
    return m_node != nullptr;
}

ISameStruct1InterfacePublisher& SameStruct1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
