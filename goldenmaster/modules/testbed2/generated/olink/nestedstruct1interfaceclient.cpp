

#include "testbed2/generated/olink/nestedstruct1interfaceclient.h"
#include "testbed2/generated/core/nestedstruct1interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::olink;

namespace 
{
const std::string interfaceId = "testbed2.NestedStruct1Interface";
}

NestedStruct1InterfaceClient::NestedStruct1InterfaceClient()
    : m_publisher(std::make_unique<NestedStruct1InterfacePublisher>())
{}

void NestedStruct1InterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<NestedStruct1>());
    }
}

void NestedStruct1InterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "prop1") {
        setProp1Local(value.get<NestedStruct1>());
    }
}

void NestedStruct1InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    m_node->setRemoteProperty(propertyId, prop1);
}

void NestedStruct1InterfaceClient::setProp1Local(const NestedStruct1& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const NestedStruct1& NestedStruct1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

NestedStruct1 NestedStruct1InterfaceClient::func1(const NestedStruct1& param1)
{
    return func1Async(param1).get();
}

std::future<NestedStruct1> NestedStruct1InterfaceClient::func1Async(const NestedStruct1& param1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<NestedStruct1>{};
    }
    std::shared_ptr<std::promise<NestedStruct1>> resultPromise = std::make_shared<std::promise<NestedStruct1>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func1");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const NestedStruct1& value = arg.value.get<NestedStruct1>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string NestedStruct1InterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void NestedStruct1InterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sig1") {
        m_publisher->publishSig1(args[0].get<NestedStruct1>());   
        return;
    }
}

void NestedStruct1InterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void NestedStruct1InterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void NestedStruct1InterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool NestedStruct1InterfaceClient::isReady() const
{
    return m_node != nullptr;
}

INestedStruct1InterfacePublisher& NestedStruct1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
