#include "tb_names/generated/mqtt/namesservice.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"
#include <iostream>

using namespace Test::TbNames;
using namespace Test::TbNames::MQTT;

Nam_EsService::Nam_EsService(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : m_impl(impl)
    , m_service(service)
    , m_topics(createTopicMap())
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusRegistrationID = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

Nam_EsService::~Nam_EsService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);

    for (const auto& topic: m_topics)
    {
        m_service->unsubscribeTopic(topic. first);
    }
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> Nam_EsService::createTopicMap()
{
    return {
        {std::string("tb.names/Nam_Es/set/Switch"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetSwitch(args); } },
        {std::string("tb.names/Nam_Es/set/SOME_PROPERTY"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetSomeProperty(args); } },
        {std::string("tb.names/Nam_Es/set/Some_Poperty2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetSomePoperty2(args); } },
        {std::string("tb.names/Nam_Es/set/enum_property"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetEnumProperty(args); } },
        {std::string("tb.names/Nam_Es/rpc/SOME_FUNCTION"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeSomeFunction(args, responseTopic, correlationData); } },
        {std::string("tb.names/Nam_Es/rpc/Some_Function2"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeSomeFunction2(args, responseTopic, correlationData); } },
    };
}

void Nam_EsService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }

    for (const auto& topic: m_topics)
    {
        m_service->subscribeTopic(topic. first, topic.second);
    }

    // send current values
    onSwitchChanged(m_impl->getSwitch());
    onSomePropertyChanged(m_impl->getSomeProperty());
    onSomePoperty2Changed(m_impl->getSomePoperty2());
    onEnumPropertyChanged(m_impl->getEnumProperty());
}
void Nam_EsService::onSetSwitch(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto Switch = json_args.get<bool>();
    m_impl->setSwitch(Switch);
}
void Nam_EsService::onSetSomeProperty(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto SOME_PROPERTY = json_args.get<int>();
    m_impl->setSomeProperty(SOME_PROPERTY);
}
void Nam_EsService::onSetSomePoperty2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto Some_Poperty2 = json_args.get<int>();
    m_impl->setSomePoperty2(Some_Poperty2);
}
void Nam_EsService::onSetEnumProperty(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto enum_property = json_args.get<Enum_With_Under_scoresEnum>();
    m_impl->setEnumProperty(enum_property);
}
void Nam_EsService::onInvokeSomeFunction(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    (void) responseTopic;
    (void) correlationData;
    const bool& SOME_PARAM = json_args.at(0).get<bool>();
    m_impl->sOME_FUNCTION(SOME_PARAM);
}
void Nam_EsService::onInvokeSomeFunction2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    (void) responseTopic;
    (void) correlationData;
    const bool& Some_Param = json_args.at(0).get<bool>();
    m_impl->some_Function2(Some_Param);
}
void Nam_EsService::onSomeSignal(bool SOME_PARAM)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { SOME_PARAM };
        static const auto topic = std::string("tb.names/Nam_Es/sig/SOME_SIGNAL");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void Nam_EsService::onSomeSignal2(bool Some_Param)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { Some_Param };
        static const auto topic = std::string("tb.names/Nam_Es/sig/Some_Signal2");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void Nam_EsService::onSwitchChanged(bool Switch)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.names/Nam_Es/prop/Switch");
        m_service->notifyPropertyChange(topic, nlohmann::json(Switch).dump());
    }
}
void Nam_EsService::onSomePropertyChanged(int SOME_PROPERTY)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.names/Nam_Es/prop/SOME_PROPERTY");
        m_service->notifyPropertyChange(topic, nlohmann::json(SOME_PROPERTY).dump());
    }
}
void Nam_EsService::onSomePoperty2Changed(int Some_Poperty2)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.names/Nam_Es/prop/Some_Poperty2");
        m_service->notifyPropertyChange(topic, nlohmann::json(Some_Poperty2).dump());
    }
}
void Nam_EsService::onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.names/Nam_Es/prop/enum_property");
        m_service->notifyPropertyChange(topic, nlohmann::json(enum_property).dump());
    }
}
