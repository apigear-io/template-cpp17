#include "tb_enum/generated/mqtt/enuminterfaceservice.h"
#include "tb_enum/generated/core/tb_enum.json.adapter.h"
#include <iostream>

using namespace Test::TbEnum;
using namespace Test::TbEnum::MQTT;

EnumInterfaceService::EnumInterfaceService(std::shared_ptr<IEnumInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

EnumInterfaceService::~EnumInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> EnumInterfaceService::createTopicMap()
{
    return {
        {std::string("tb.enum/EnumInterface/set/prop0"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp0(args); } },
        {std::string("tb.enum/EnumInterface/set/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp1(args); } },
        {std::string("tb.enum/EnumInterface/set/prop2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp2(args); } },
        {std::string("tb.enum/EnumInterface/set/prop3"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp3(args); } },
        {std::string("tb.enum/EnumInterface/rpc/func0"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc0(args, responseTopic, correlationData); } },
        {std::string("tb.enum/EnumInterface/rpc/func1"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc1(args, responseTopic, correlationData); } },
        {std::string("tb.enum/EnumInterface/rpc/func2"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc2(args, responseTopic, correlationData); } },
        {std::string("tb.enum/EnumInterface/rpc/func3"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc3(args, responseTopic, correlationData); } },
    };
}

void EnumInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onProp0Changed(m_impl->getProp0());
    onProp1Changed(m_impl->getProp1());
    onProp2Changed(m_impl->getProp2());
    onProp3Changed(m_impl->getProp3());
}
void EnumInterfaceService::onSetProp0(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop0 = json_args.get<Enum0Enum>();
    m_impl->setProp0(prop0);
}
void EnumInterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<Enum1Enum>();
    m_impl->setProp1(prop1);
}
void EnumInterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<Enum2Enum>();
    m_impl->setProp2(prop2);
}
void EnumInterfaceService::onSetProp3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop3 = json_args.get<Enum3Enum>();
    m_impl->setProp3(prop3);
}
void EnumInterfaceService::onInvokeFunc0(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum0Enum& param0 = json_args.at(0).get<Enum0Enum>();
    auto result = m_impl->func0(param0);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void EnumInterfaceService::onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum1Enum& param1 = json_args.at(0).get<Enum1Enum>();
    auto result = m_impl->func1(param1);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void EnumInterfaceService::onInvokeFunc2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum2Enum& param2 = json_args.at(0).get<Enum2Enum>();
    auto result = m_impl->func2(param2);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void EnumInterfaceService::onInvokeFunc3(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum3Enum& param3 = json_args.at(0).get<Enum3Enum>();
    auto result = m_impl->func3(param3);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void EnumInterfaceService::onSig0(Enum0Enum param0)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param0 };
        static const auto topic = std::string("tb.enum/EnumInterface/sig/sig0");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void EnumInterfaceService::onSig1(Enum1Enum param1)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1 };
        static const auto topic = std::string("tb.enum/EnumInterface/sig/sig1");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void EnumInterfaceService::onSig2(Enum2Enum param2)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param2 };
        static const auto topic = std::string("tb.enum/EnumInterface/sig/sig2");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void EnumInterfaceService::onSig3(Enum3Enum param3)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param3 };
        static const auto topic = std::string("tb.enum/EnumInterface/sig/sig3");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void EnumInterfaceService::onProp0Changed(Enum0Enum prop0)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.enum/EnumInterface/prop/prop0");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop0).dump());
    }
}
void EnumInterfaceService::onProp1Changed(Enum1Enum prop1)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.enum/EnumInterface/prop/prop1");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop1).dump());
    }
}
void EnumInterfaceService::onProp2Changed(Enum2Enum prop2)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.enum/EnumInterface/prop/prop2");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop2).dump());
    }
}
void EnumInterfaceService::onProp3Changed(Enum3Enum prop3)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.enum/EnumInterface/prop/prop3");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop3).dump());
    }
}
