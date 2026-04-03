#include "testbed1/generated/mqtt/structarray2interfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::MQTT;

StructArray2InterfaceService::StructArray2InterfaceService(std::shared_ptr<IStructArray2Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

StructArray2InterfaceService::~StructArray2InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> StructArray2InterfaceService::createTopicMap()
{
    return {
        {std::string("testbed1/StructArray2Interface/set/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropBool(args); } },
        {std::string("testbed1/StructArray2Interface/set/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropInt(args); } },
        {std::string("testbed1/StructArray2Interface/set/propFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropFloat(args); } },
        {std::string("testbed1/StructArray2Interface/set/propString"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropString(args); } },
        {std::string("testbed1/StructArray2Interface/set/propEnum"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropEnum(args); } },
        {std::string("testbed1/StructArray2Interface/rpc/funcBool"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncBool(args, responseTopic, correlationData); } },
        {std::string("testbed1/StructArray2Interface/rpc/funcInt"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncInt(args, responseTopic, correlationData); } },
        {std::string("testbed1/StructArray2Interface/rpc/funcFloat"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncFloat(args, responseTopic, correlationData); } },
        {std::string("testbed1/StructArray2Interface/rpc/funcString"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncString(args, responseTopic, correlationData); } },
        {std::string("testbed1/StructArray2Interface/rpc/funcEnum"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncEnum(args, responseTopic, correlationData); } },
    };
}

void StructArray2InterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onPropBoolChanged(m_impl->getPropBool());
    onPropIntChanged(m_impl->getPropInt());
    onPropFloatChanged(m_impl->getPropFloat());
    onPropStringChanged(m_impl->getPropString());
    onPropEnumChanged(m_impl->getPropEnum());
}
void StructArray2InterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<StructBoolWithArray>();
    m_impl->setPropBool(propBool);
}
void StructArray2InterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<StructIntWithArray>();
    m_impl->setPropInt(propInt);
}
void StructArray2InterfaceService::onSetPropFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat = json_args.get<StructFloatWithArray>();
    m_impl->setPropFloat(propFloat);
}
void StructArray2InterfaceService::onSetPropString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propString = json_args.get<StructStringWithArray>();
    m_impl->setPropString(propString);
}
void StructArray2InterfaceService::onSetPropEnum(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propEnum = json_args.get<StructEnumWithArray>();
    m_impl->setPropEnum(propEnum);
}
void StructArray2InterfaceService::onInvokeFuncBool(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructBoolWithArray& paramBool = json_args.at(0).get<StructBoolWithArray>();
    auto result = m_impl->funcBool(paramBool);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArray2InterfaceService::onInvokeFuncInt(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructIntWithArray& paramInt = json_args.at(0).get<StructIntWithArray>();
    auto result = m_impl->funcInt(paramInt);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArray2InterfaceService::onInvokeFuncFloat(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructFloatWithArray& paramFloat = json_args.at(0).get<StructFloatWithArray>();
    auto result = m_impl->funcFloat(paramFloat);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArray2InterfaceService::onInvokeFuncString(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructStringWithArray& paramString = json_args.at(0).get<StructStringWithArray>();
    auto result = m_impl->funcString(paramString);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArray2InterfaceService::onInvokeFuncEnum(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructEnumWithArray& paramEnum = json_args.at(0).get<StructEnumWithArray>();
    auto result = m_impl->funcEnum(paramEnum);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArray2InterfaceService::onSigBool(const StructBoolWithArray& paramBool)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramBool };
        static const auto topic = std::string("testbed1/StructArray2Interface/sig/sigBool");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArray2InterfaceService::onSigInt(const StructIntWithArray& paramInt)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramInt };
        static const auto topic = std::string("testbed1/StructArray2Interface/sig/sigInt");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArray2InterfaceService::onSigFloat(const StructFloatWithArray& paramFloat)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramFloat };
        static const auto topic = std::string("testbed1/StructArray2Interface/sig/sigFloat");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArray2InterfaceService::onSigString(const StructStringWithArray& paramString)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramString };
        static const auto topic = std::string("testbed1/StructArray2Interface/sig/sigString");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArray2InterfaceService::onPropBoolChanged(const StructBoolWithArray& propBool)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArray2Interface/prop/propBool");
        m_service->notifyPropertyChange(topic, nlohmann::json(propBool).dump());
    }
}
void StructArray2InterfaceService::onPropIntChanged(const StructIntWithArray& propInt)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArray2Interface/prop/propInt");
        m_service->notifyPropertyChange(topic, nlohmann::json(propInt).dump());
    }
}
void StructArray2InterfaceService::onPropFloatChanged(const StructFloatWithArray& propFloat)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArray2Interface/prop/propFloat");
        m_service->notifyPropertyChange(topic, nlohmann::json(propFloat).dump());
    }
}
void StructArray2InterfaceService::onPropStringChanged(const StructStringWithArray& propString)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArray2Interface/prop/propString");
        m_service->notifyPropertyChange(topic, nlohmann::json(propString).dump());
    }
}
void StructArray2InterfaceService::onPropEnumChanged(const StructEnumWithArray& propEnum)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArray2Interface/prop/propEnum");
        m_service->notifyPropertyChange(topic, nlohmann::json(propEnum).dump());
    }
}
