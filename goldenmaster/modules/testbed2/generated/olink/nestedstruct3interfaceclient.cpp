

#include "testbed2/generated/olink/nestedstruct3interfaceclient.h"
#include "testbed2/generated/core/nestedstruct3interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::olink;

namespace 
{
const std::string interfaceId = "testbed2.NestedStruct3Interface";
}

NestedStruct3InterfaceClient::NestedStruct3InterfaceClient()
    : m_publisher(std::make_unique<NestedStruct3InterfacePublisher>())
{}

void NestedStruct3InterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<NestedStruct1>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<NestedStruct2>());
    }
    if(fields.contains("prop3")) {
        setProp3Local(fields["prop3"].get<NestedStruct3>());
    }
}

void NestedStruct3InterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "prop1") {
        setProp1Local(value.get<NestedStruct1>());
    }
    else if ( propertyName == "prop2") {
        setProp2Local(value.get<NestedStruct2>());
    }
    else if ( propertyName == "prop3") {
        setProp3Local(value.get<NestedStruct3>());
    }
}

void NestedStruct3InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    m_node->setRemoteProperty(propertyId, prop1);
}

void NestedStruct3InterfaceClient::setProp1Local(const NestedStruct1& prop1)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
        if (m_data.m_prop1 == prop1) {
            return;
        }
        m_data.m_prop1 = prop1;
    }

    m_publisher->publishProp1Changed(prop1);
}

const NestedStruct1& NestedStruct3InterfaceClient::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_data.m_prop1;
}

void NestedStruct3InterfaceClient::setProp2(const NestedStruct2& prop2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop2");
    m_node->setRemoteProperty(propertyId, prop2);
}

void NestedStruct3InterfaceClient::setProp2Local(const NestedStruct2& prop2)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
        if (m_data.m_prop2 == prop2) {
            return;
        }
        m_data.m_prop2 = prop2;
    }

    m_publisher->publishProp2Changed(prop2);
}

const NestedStruct2& NestedStruct3InterfaceClient::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_data.m_prop2;
}

void NestedStruct3InterfaceClient::setProp3(const NestedStruct3& prop3)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop3");
    m_node->setRemoteProperty(propertyId, prop3);
}

void NestedStruct3InterfaceClient::setProp3Local(const NestedStruct3& prop3)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
        if (m_data.m_prop3 == prop3) {
            return;
        }
        m_data.m_prop3 = prop3;
    }

    m_publisher->publishProp3Changed(prop3);
}

const NestedStruct3& NestedStruct3InterfaceClient::getProp3() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    return m_data.m_prop3;
}

NestedStruct1 NestedStruct3InterfaceClient::func1(const NestedStruct1& param1)
{
    return func1Async(param1).get();
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func1Async(const NestedStruct1& param1)
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

NestedStruct1 NestedStruct3InterfaceClient::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    return func2Async(param1, param2).get();
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func2Async(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<NestedStruct1>{};
    }
    std::shared_ptr<std::promise<NestedStruct1>> resultPromise = std::make_shared<std::promise<NestedStruct1>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func2");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1, param2}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const NestedStruct1& value = arg.value.get<NestedStruct1>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

NestedStruct1 NestedStruct3InterfaceClient::func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    return func3Async(param1, param2, param3).get();
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<NestedStruct1>{};
    }
    std::shared_ptr<std::promise<NestedStruct1>> resultPromise = std::make_shared<std::promise<NestedStruct1>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func3");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1, param2, param3}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const NestedStruct1& value = arg.value.get<NestedStruct1>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string NestedStruct3InterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void NestedStruct3InterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sig1") {
        m_publisher->publishSig1(args[0].get<NestedStruct1>());   
        return;
    }
    if(signalName == "sig2") {
        m_publisher->publishSig2(args[0].get<NestedStruct1>(),args[1].get<NestedStruct2>());   
        return;
    }
    if(signalName == "sig3") {
        m_publisher->publishSig3(args[0].get<NestedStruct1>(),args[1].get<NestedStruct2>(),args[2].get<NestedStruct3>());   
        return;
    }
}

void NestedStruct3InterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void NestedStruct3InterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void NestedStruct3InterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool NestedStruct3InterfaceClient::isReady() const
{
    return m_node != nullptr;
}

INestedStruct3InterfacePublisher& NestedStruct3InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
