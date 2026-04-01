#include "testbed2/generated/mqtt/nestedstruct1interfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include "apigear/utilities/logger.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::MQTT;

NestedStruct1InterfaceService::NestedStruct1InterfaceService(std::shared_ptr<INestedStruct1Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

NestedStruct1InterfaceService::~NestedStruct1InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> NestedStruct1InterfaceService::createTopicMap()
{
    return {
        {std::string("testbed2/NestedStruct1Interface/set/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp1(args); } },
        {std::string("testbed2/NestedStruct1Interface/rpc/funcNoReturnValue"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncNoReturnValue(args, responseTopic, correlationData); } },
        {std::string("testbed2/NestedStruct1Interface/rpc/funcNoParams"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncNoParams(args, responseTopic, correlationData); } },
        {std::string("testbed2/NestedStruct1Interface/rpc/func1"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc1(args, responseTopic, correlationData); } },
    };
}

void NestedStruct1InterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onProp1Changed(m_impl->getProp1());
}
void NestedStruct1InterfaceService::onSetProp1(const std::string& args) const
{
    try {
        nlohmann::json json_args = nlohmann::json::parse(args);
        if (json_args.empty())
        {
            return;
        }

        auto prop1 = json_args.get<NestedStruct1>();
        m_impl->setProp1(prop1);
    } catch (const std::exception& e) {
        AG_LOG_ERROR("NestedStruct1InterfaceService JSON error: " + std::string(e.what()));
    }
}
void NestedStruct1InterfaceService::onInvokeFuncNoReturnValue(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    (void) responseTopic;
    (void) correlationData;
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    m_impl->funcNoReturnValue(param1);
}
void NestedStruct1InterfaceService::onInvokeFuncNoParams(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    auto result = m_impl->funcNoParams();
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void NestedStruct1InterfaceService::onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    try {
        nlohmann::json json_args = nlohmann::json::parse(args);
        const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
        auto result = m_impl->func1(param1);
        m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
    } catch (const std::exception& e) {
        AG_LOG_ERROR("NestedStruct1InterfaceService JSON error: " + std::string(e.what()));
    }
}
void NestedStruct1InterfaceService::onSig1(const NestedStruct1& param1)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1 };
        static const auto topic = std::string("testbed2/NestedStruct1Interface/sig/sig1");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void NestedStruct1InterfaceService::onProp1Changed(const NestedStruct1& prop1)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/NestedStruct1Interface/prop/prop1");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop1).dump());
    }
}
