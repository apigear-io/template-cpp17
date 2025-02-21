#include "tb_same2/generated/mqtt/samestruct2interfaceservice.h"
#include "tb_same2/generated/core/tb_same2.json.adapter.h"
#include <iostream>

using namespace Test::TbSame2;
using namespace Test::TbSame2::MQTT;

SameStruct2InterfaceService::SameStruct2InterfaceService(std::shared_ptr<ISameStruct2Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

SameStruct2InterfaceService::~SameStruct2InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> SameStruct2InterfaceService::createTopicMap()
{
    return {
        {std::string("tb.same2/SameStruct2Interface/set/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp1(args); } },
        {std::string("tb.same2/SameStruct2Interface/set/prop2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp2(args); } },
        {std::string("tb.same2/SameStruct2Interface/rpc/func1"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc1(args, responseTopic, correlationData); } },
        {std::string("tb.same2/SameStruct2Interface/rpc/func2"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc2(args, responseTopic, correlationData); } },
    };
}

void SameStruct2InterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onProp1Changed(m_impl->getProp1());
    onProp2Changed(m_impl->getProp2());
}
void SameStruct2InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<Struct2>();
    m_impl->setProp1(prop1);
}
void SameStruct2InterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<Struct2>();
    m_impl->setProp2(prop2);
}
void SameStruct2InterfaceService::onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Struct1& param1 = json_args.at(0).get<Struct1>();
    auto result = m_impl->func1(param1);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void SameStruct2InterfaceService::onInvokeFunc2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Struct1& param1 = json_args.at(0).get<Struct1>();
    const Struct2& param2 = json_args.at(1).get<Struct2>();
    auto result = m_impl->func2(param1, param2);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void SameStruct2InterfaceService::onSig1(const Struct1& param1)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1 };
        static const auto topic = std::string("tb.same2/SameStruct2Interface/sig/sig1");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void SameStruct2InterfaceService::onSig2(const Struct1& param1, const Struct2& param2)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1, param2 };
        static const auto topic = std::string("tb.same2/SameStruct2Interface/sig/sig2");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void SameStruct2InterfaceService::onProp1Changed(const Struct2& prop1)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.same2/SameStruct2Interface/prop/prop1");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop1).dump());
    }
}
void SameStruct2InterfaceService::onProp2Changed(const Struct2& prop2)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.same2/SameStruct2Interface/prop/prop2");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop2).dump());
    }
}
