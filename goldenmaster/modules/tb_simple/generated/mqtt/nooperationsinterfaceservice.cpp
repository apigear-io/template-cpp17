#include "tb_simple/generated/mqtt/nooperationsinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::MQTT;

NoOperationsInterfaceService::NoOperationsInterfaceService(std::shared_ptr<INoOperationsInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

NoOperationsInterfaceService::~NoOperationsInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> NoOperationsInterfaceService::createTopicMap()
{
    return {
        {std::string("tb.simple/NoOperationsInterface/set/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropBool(args); } },
        {std::string("tb.simple/NoOperationsInterface/set/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropInt(args); } },
    };
}

void NoOperationsInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onPropBoolChanged(m_impl->getPropBool());
    onPropIntChanged(m_impl->getPropInt());
}
void NoOperationsInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<bool>();
    m_impl->setPropBool(propBool);
}
void NoOperationsInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<int>();
    m_impl->setPropInt(propInt);
}
void NoOperationsInterfaceService::onSigVoid()
{
    if(m_service != nullptr) {
        const nlohmann::json& args = {  };
        static const auto topic = std::string("tb.simple/NoOperationsInterface/sig/sigVoid");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void NoOperationsInterfaceService::onSigBool(bool paramBool)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramBool };
        static const auto topic = std::string("tb.simple/NoOperationsInterface/sig/sigBool");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void NoOperationsInterfaceService::onPropBoolChanged(bool propBool)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.simple/NoOperationsInterface/prop/propBool");
        m_service->notifyPropertyChange(topic, nlohmann::json(propBool).dump());
    }
}
void NoOperationsInterfaceService::onPropIntChanged(int propInt)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.simple/NoOperationsInterface/prop/propInt");
        m_service->notifyPropertyChange(topic, nlohmann::json(propInt).dump());
    }
}
