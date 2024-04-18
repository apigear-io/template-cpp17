

#include "tb_same1/generated/olink/sameenum2interfaceclient.h"
#include "tb_same1/generated/core/sameenum2interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSame1;
using namespace Test::TbSame1::olink;

namespace 
{
const std::string interfaceId = "tb.same1.SameEnum2Interface";
}

SameEnum2InterfaceClient::SameEnum2InterfaceClient()
    : m_publisher(std::make_unique<SameEnum2InterfacePublisher>())
{}

void SameEnum2InterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<Enum1Enum>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<Enum2Enum>());
    }
}

void SameEnum2InterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "prop1") {
        setProp1Local(value.get<Enum1Enum>());
    }
    else if ( propertyName == "prop2") {
        setProp2Local(value.get<Enum2Enum>());
    }
}

void SameEnum2InterfaceClient::setProp1(Enum1Enum prop1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    m_node->setRemoteProperty(propertyId, prop1);
}

void SameEnum2InterfaceClient::setProp1Local(Enum1Enum prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum SameEnum2InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void SameEnum2InterfaceClient::setProp2(Enum2Enum prop2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop2");
    m_node->setRemoteProperty(propertyId, prop2);
}

void SameEnum2InterfaceClient::setProp2Local(Enum2Enum prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

Enum2Enum SameEnum2InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

Enum1Enum SameEnum2InterfaceClient::func1(Enum1Enum param1)
{
    return func1Async(param1).get();
}

std::future<Enum1Enum> SameEnum2InterfaceClient::func1Async(Enum1Enum param1)
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

Enum1Enum SameEnum2InterfaceClient::func2(Enum1Enum param1, Enum2Enum param2)
{
    return func2Async(param1, param2).get();
}

std::future<Enum1Enum> SameEnum2InterfaceClient::func2Async(Enum1Enum param1, Enum2Enum param2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<Enum1Enum>{};
    }
    std::shared_ptr<std::promise<Enum1Enum>> resultPromise = std::make_shared<std::promise<Enum1Enum>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func2");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1, param2}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const Enum1Enum& value = arg.value.get<Enum1Enum>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string SameEnum2InterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void SameEnum2InterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sig1") {
        m_publisher->publishSig1(args[0].get<Enum1Enum>());   
        return;
    }
    if(signalName == "sig2") {
        m_publisher->publishSig2(args[0].get<Enum1Enum>(),args[1].get<Enum2Enum>());   
        return;
    }
}

void SameEnum2InterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void SameEnum2InterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void SameEnum2InterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool SameEnum2InterfaceClient::isReady() const
{
    return m_node != nullptr;
}

ISameEnum2InterfacePublisher& SameEnum2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
