#include "tb_simple/generated/mqtt/nosignalsinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::MQTT;

NoSignalsInterfaceService::NoSignalsInterfaceService(std::shared_ptr<INoSignalsInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

NoSignalsInterfaceService::~NoSignalsInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> NoSignalsInterfaceService::createTopicMap()
{
    return {
        {std::string("tb.simple/NoSignalsInterface/set/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropBool(args); } },
        {std::string("tb.simple/NoSignalsInterface/set/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropInt(args); } },
        {std::string("tb.simple/NoSignalsInterface/rpc/funcVoid"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncVoid(args, responseTopic, correlationData); } },
        {std::string("tb.simple/NoSignalsInterface/rpc/funcBool"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncBool(args, responseTopic, correlationData); } },
    };
}

void NoSignalsInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onPropBoolChanged(m_impl->getPropBool());
    onPropIntChanged(m_impl->getPropInt());
}
void NoSignalsInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<bool>();
    m_impl->setPropBool(propBool);
}
void NoSignalsInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<int>();
    m_impl->setPropInt(propInt);
}
void NoSignalsInterfaceService::onInvokeFuncVoid(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    (void) responseTopic;
    (void) correlationData;
    m_impl->funcVoid();
}
void NoSignalsInterfaceService::onInvokeFuncBool(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const bool& paramBool = json_args.at(0).get<bool>();
    auto result = m_impl->funcBool(paramBool);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void NoSignalsInterfaceService::onPropBoolChanged(bool propBool)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.simple/NoSignalsInterface/prop/propBool");
        m_service->notifyPropertyChange(topic, nlohmann::json(propBool).dump());
    }
}
void NoSignalsInterfaceService::onPropIntChanged(int propInt)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.simple/NoSignalsInterface/prop/propInt");
        m_service->notifyPropertyChange(topic, nlohmann::json(propInt).dump());
    }
}
