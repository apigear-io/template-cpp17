#include "tb_same1/generated/mqtt/sameenum1interfaceservice.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include <iostream>

using namespace Test::TbSame1;
using namespace Test::TbSame1::MQTT;

SameEnum1InterfaceService::SameEnum1InterfaceService(std::shared_ptr<ISameEnum1Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

SameEnum1InterfaceService::~SameEnum1InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> SameEnum1InterfaceService::createTopicMap()
{
    return {
        {std::string("tb.same1/SameEnum1Interface/set/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp1(args); } },
        {std::string("tb.same1/SameEnum1Interface/rpc/func1"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc1(args, responseTopic, correlationData); } },
    };
}

void SameEnum1InterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onProp1Changed(m_impl->getProp1());
}
void SameEnum1InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<Enum1Enum>();
    m_impl->setProp1(prop1);
}
void SameEnum1InterfaceService::onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum1Enum& param1 = json_args.at(0).get<Enum1Enum>();
    auto result = m_impl->func1(param1);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void SameEnum1InterfaceService::onSig1(Enum1Enum param1)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1 };
        static const auto topic = std::string("tb.same1/SameEnum1Interface/sig/sig1");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void SameEnum1InterfaceService::onProp1Changed(Enum1Enum prop1)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.same1/SameEnum1Interface/prop/prop1");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop1).dump());
    }
}
