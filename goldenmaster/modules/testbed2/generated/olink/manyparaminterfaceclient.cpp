

#include "testbed2/generated/olink/manyparaminterfaceclient.h"
#include "testbed2/generated/core/manyparaminterface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::olink;

namespace 
{
const std::string interfaceId = "testbed2.ManyParamInterface";
}

ManyParamInterfaceClient::ManyParamInterfaceClient()
    : m_publisher(std::make_unique<ManyParamInterfacePublisher>())
{}

void ManyParamInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<int>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<int>());
    }
    if(fields.contains("prop3")) {
        setProp3Local(fields["prop3"].get<int>());
    }
    if(fields.contains("prop4")) {
        setProp4Local(fields["prop4"].get<int>());
    }
}

void ManyParamInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "prop1") {
        setProp1Local(value.get<int>());
    }
    else if ( propertyName == "prop2") {
        setProp2Local(value.get<int>());
    }
    else if ( propertyName == "prop3") {
        setProp3Local(value.get<int>());
    }
    else if ( propertyName == "prop4") {
        setProp4Local(value.get<int>());
    }
}

void ManyParamInterfaceClient::setProp1(int prop1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    m_node->setRemoteProperty(propertyId, prop1);
}

void ManyParamInterfaceClient::setProp1Local(int prop1)
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

int ManyParamInterfaceClient::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_data.m_prop1;
}

void ManyParamInterfaceClient::setProp2(int prop2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop2");
    m_node->setRemoteProperty(propertyId, prop2);
}

void ManyParamInterfaceClient::setProp2Local(int prop2)
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

int ManyParamInterfaceClient::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_data.m_prop2;
}

void ManyParamInterfaceClient::setProp3(int prop3)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop3");
    m_node->setRemoteProperty(propertyId, prop3);
}

void ManyParamInterfaceClient::setProp3Local(int prop3)
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

int ManyParamInterfaceClient::getProp3() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    return m_data.m_prop3;
}

void ManyParamInterfaceClient::setProp4(int prop4)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop4");
    m_node->setRemoteProperty(propertyId, prop4);
}

void ManyParamInterfaceClient::setProp4Local(int prop4)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_prop4Mutex);
        if (m_data.m_prop4 == prop4) {
            return;
        }
        m_data.m_prop4 = prop4;
    }

    m_publisher->publishProp4Changed(prop4);
}

int ManyParamInterfaceClient::getProp4() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop4Mutex);
    return m_data.m_prop4;
}

int ManyParamInterfaceClient::func1(int param1)
{
    return func1Async(param1).get();
}

std::future<int> ManyParamInterfaceClient::func1Async(int param1)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int>{};
    }
    std::shared_ptr<std::promise<int>> resultPromise = std::make_shared<std::promise<int>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func1");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const int& value = arg.value.get<int>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

int ManyParamInterfaceClient::func2(int param1, int param2)
{
    return func2Async(param1, param2).get();
}

std::future<int> ManyParamInterfaceClient::func2Async(int param1, int param2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int>{};
    }
    std::shared_ptr<std::promise<int>> resultPromise = std::make_shared<std::promise<int>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func2");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1, param2}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const int& value = arg.value.get<int>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

int ManyParamInterfaceClient::func3(int param1, int param2, int param3)
{
    return func3Async(param1, param2, param3).get();
}

std::future<int> ManyParamInterfaceClient::func3Async(int param1, int param2, int param3)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int>{};
    }
    std::shared_ptr<std::promise<int>> resultPromise = std::make_shared<std::promise<int>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func3");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1, param2, param3}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const int& value = arg.value.get<int>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

int ManyParamInterfaceClient::func4(int param1, int param2, int param3, int param4)
{
    return func4Async(param1, param2, param3, param4).get();
}

std::future<int> ManyParamInterfaceClient::func4Async(int param1, int param2, int param3, int param4)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int>{};
    }
    std::shared_ptr<std::promise<int>> resultPromise = std::make_shared<std::promise<int>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "func4");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({param1, param2, param3, param4}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const int& value = arg.value.get<int>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string ManyParamInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void ManyParamInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sig1") {
        m_publisher->publishSig1(args[0].get<int>());   
        return;
    }
    if(signalName == "sig2") {
        m_publisher->publishSig2(args[0].get<int>(),args[1].get<int>());   
        return;
    }
    if(signalName == "sig3") {
        m_publisher->publishSig3(args[0].get<int>(),args[1].get<int>(),args[2].get<int>());   
        return;
    }
    if(signalName == "sig4") {
        m_publisher->publishSig4(args[0].get<int>(),args[1].get<int>(),args[2].get<int>(),args[3].get<int>());   
        return;
    }
}

void ManyParamInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void ManyParamInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void ManyParamInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool ManyParamInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

IManyParamInterfacePublisher& ManyParamInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
