

#include "tb_same1/generated/olink/samestruct2interfaceclient.h"
#include "tb_same1/generated/core/samestruct2interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSame1;
using namespace Test::TbSame1::olink;

namespace 
{
const std::string interfaceId = "tb.same1.SameStruct2Interface";
}

SameStruct2InterfaceClient::SameStruct2InterfaceClient()
    : m_publisher(std::make_unique<SameStruct2InterfacePublisher>())
{}

void SameStruct2InterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<Struct2>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<Struct2>());
    }
}

void SameStruct2InterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "prop1") {
        setProp1Local(value.get<Struct2>());
    }
    else if ( propertyName == "prop2") {
        setProp2Local(value.get<Struct2>());
    }
}

void SameStruct2InterfaceClient::setProp1(const Struct2& prop1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    m_node->setRemoteProperty(propertyId, prop1);
}

void SameStruct2InterfaceClient::setProp1Local(const Struct2& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Struct2& SameStruct2InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void SameStruct2InterfaceClient::setProp2(const Struct2& prop2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop2");
    m_node->setRemoteProperty(propertyId, prop2);
}

void SameStruct2InterfaceClient::setProp2Local(const Struct2& prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const Struct2& SameStruct2InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

Struct1 SameStruct2InterfaceClient::func1(const Struct1& param1)
{
    return func1Async(param1).get();
}

std::future<Struct1> SameStruct2InterfaceClient::func1Async(const Struct1& param1)
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

Struct1 SameStruct2InterfaceClient::func2(const Struct1& param1, const Struct2& param2)
{
    return func2Async(param1, param2).get();
}

std::future<Struct1> SameStruct2InterfaceClient::func2Async(const Struct1& param1, const Struct2& param2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<Struct1>{};
    }
    std::shared_ptr<std::promise<Struct1>> resultPromise = std::make_shared<std::promise<Struct1>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func2");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1, param2}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const Struct1& value = arg.value.get<Struct1>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string SameStruct2InterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void SameStruct2InterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sig1") {
        m_publisher->publishSig1(args[0].get<Struct1>());   
        return;
    }
    if(signalName == "sig2") {
        m_publisher->publishSig2(args[0].get<Struct1>(),args[1].get<Struct2>());   
        return;
    }
}

void SameStruct2InterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void SameStruct2InterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void SameStruct2InterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool SameStruct2InterfaceClient::isReady() const
{
    return m_node != nullptr;
}

ISameStruct2InterfacePublisher& SameStruct2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
