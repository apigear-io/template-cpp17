#include "testbed2/generated/mqtt/nestedstruct3interfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::MQTT;

NestedStruct3InterfaceService::NestedStruct3InterfaceService(std::shared_ptr<INestedStruct3Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

NestedStruct3InterfaceService::~NestedStruct3InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> NestedStruct3InterfaceService::createTopicMap()
{
    return {
        {std::string("testbed2/NestedStruct3Interface/set/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp1(args); } },
        {std::string("testbed2/NestedStruct3Interface/set/prop2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp2(args); } },
        {std::string("testbed2/NestedStruct3Interface/set/prop3"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp3(args); } },
        {std::string("testbed2/NestedStruct3Interface/rpc/func1"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc1(args, responseTopic, correlationData); } },
        {std::string("testbed2/NestedStruct3Interface/rpc/func2"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc2(args, responseTopic, correlationData); } },
        {std::string("testbed2/NestedStruct3Interface/rpc/func3"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc3(args, responseTopic, correlationData); } },
    };
}

void NestedStruct3InterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onProp1Changed(m_impl->getProp1());
    onProp2Changed(m_impl->getProp2());
    onProp3Changed(m_impl->getProp3());
}
void NestedStruct3InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<NestedStruct1>();
    m_impl->setProp1(prop1);
}
void NestedStruct3InterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<NestedStruct2>();
    m_impl->setProp2(prop2);
}
void NestedStruct3InterfaceService::onSetProp3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop3 = json_args.get<NestedStruct3>();
    m_impl->setProp3(prop3);
}
void NestedStruct3InterfaceService::onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    auto result = m_impl->func1(param1);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void NestedStruct3InterfaceService::onInvokeFunc2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    const NestedStruct2& param2 = json_args.at(1).get<NestedStruct2>();
    auto result = m_impl->func2(param1, param2);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void NestedStruct3InterfaceService::onInvokeFunc3(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    const NestedStruct2& param2 = json_args.at(1).get<NestedStruct2>();
    const NestedStruct3& param3 = json_args.at(2).get<NestedStruct3>();
    auto result = m_impl->func3(param1, param2, param3);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void NestedStruct3InterfaceService::onSig1(const NestedStruct1& param1)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1 };
        static const auto topic = std::string("testbed2/NestedStruct3Interface/sig/sig1");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void NestedStruct3InterfaceService::onSig2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1, param2 };
        static const auto topic = std::string("testbed2/NestedStruct3Interface/sig/sig2");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void NestedStruct3InterfaceService::onSig3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1, param2, param3 };
        static const auto topic = std::string("testbed2/NestedStruct3Interface/sig/sig3");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void NestedStruct3InterfaceService::onProp1Changed(const NestedStruct1& prop1)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/NestedStruct3Interface/prop/prop1");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop1).dump());
    }
}
void NestedStruct3InterfaceService::onProp2Changed(const NestedStruct2& prop2)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/NestedStruct3Interface/prop/prop2");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop2).dump());
    }
}
void NestedStruct3InterfaceService::onProp3Changed(const NestedStruct3& prop3)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/NestedStruct3Interface/prop/prop3");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop3).dump());
    }
}
