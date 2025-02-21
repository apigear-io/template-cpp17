#include "testbed1/generated/mqtt/structarrayinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::MQTT;

StructArrayInterfaceService::StructArrayInterfaceService(std::shared_ptr<IStructArrayInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

StructArrayInterfaceService::~StructArrayInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> StructArrayInterfaceService::createTopicMap()
{
    return {
        {std::string("testbed1/StructArrayInterface/set/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropBool(args); } },
        {std::string("testbed1/StructArrayInterface/set/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropInt(args); } },
        {std::string("testbed1/StructArrayInterface/set/propFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropFloat(args); } },
        {std::string("testbed1/StructArrayInterface/set/propString"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropString(args); } },
        {std::string("testbed1/StructArrayInterface/rpc/funcBool"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncBool(args, responseTopic, correlationData); } },
        {std::string("testbed1/StructArrayInterface/rpc/funcInt"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncInt(args, responseTopic, correlationData); } },
        {std::string("testbed1/StructArrayInterface/rpc/funcFloat"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncFloat(args, responseTopic, correlationData); } },
        {std::string("testbed1/StructArrayInterface/rpc/funcString"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncString(args, responseTopic, correlationData); } },
    };
}

void StructArrayInterfaceService::onConnectionStatusChanged(bool connectionStatus)
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
}
void StructArrayInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<std::list<StructBool>>();
    m_impl->setPropBool(propBool);
}
void StructArrayInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<std::list<StructInt>>();
    m_impl->setPropInt(propInt);
}
void StructArrayInterfaceService::onSetPropFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat = json_args.get<std::list<StructFloat>>();
    m_impl->setPropFloat(propFloat);
}
void StructArrayInterfaceService::onSetPropString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propString = json_args.get<std::list<StructString>>();
    m_impl->setPropString(propString);
}
void StructArrayInterfaceService::onInvokeFuncBool(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructBool>& paramBool = json_args.at(0).get<std::list<StructBool>>();
    auto result = m_impl->funcBool(paramBool);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArrayInterfaceService::onInvokeFuncInt(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructInt>& paramInt = json_args.at(0).get<std::list<StructInt>>();
    auto result = m_impl->funcInt(paramInt);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArrayInterfaceService::onInvokeFuncFloat(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructFloat>& paramFloat = json_args.at(0).get<std::list<StructFloat>>();
    auto result = m_impl->funcFloat(paramFloat);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArrayInterfaceService::onInvokeFuncString(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructString>& paramString = json_args.at(0).get<std::list<StructString>>();
    auto result = m_impl->funcString(paramString);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArrayInterfaceService::onSigBool(const std::list<StructBool>& paramBool)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramBool };
        static const auto topic = std::string("testbed1/StructArrayInterface/sig/sigBool");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArrayInterfaceService::onSigInt(const std::list<StructInt>& paramInt)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramInt };
        static const auto topic = std::string("testbed1/StructArrayInterface/sig/sigInt");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArrayInterfaceService::onSigFloat(const std::list<StructFloat>& paramFloat)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramFloat };
        static const auto topic = std::string("testbed1/StructArrayInterface/sig/sigFloat");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArrayInterfaceService::onSigString(const std::list<StructString>& paramString)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramString };
        static const auto topic = std::string("testbed1/StructArrayInterface/sig/sigString");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArrayInterfaceService::onPropBoolChanged(const std::list<StructBool>& propBool)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArrayInterface/prop/propBool");
        m_service->notifyPropertyChange(topic, nlohmann::json(propBool).dump());
    }
}
void StructArrayInterfaceService::onPropIntChanged(const std::list<StructInt>& propInt)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArrayInterface/prop/propInt");
        m_service->notifyPropertyChange(topic, nlohmann::json(propInt).dump());
    }
}
void StructArrayInterfaceService::onPropFloatChanged(const std::list<StructFloat>& propFloat)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArrayInterface/prop/propFloat");
        m_service->notifyPropertyChange(topic, nlohmann::json(propFloat).dump());
    }
}
void StructArrayInterfaceService::onPropStringChanged(const std::list<StructString>& propString)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructArrayInterface/prop/propString");
        m_service->notifyPropertyChange(topic, nlohmann::json(propString).dump());
    }
}
