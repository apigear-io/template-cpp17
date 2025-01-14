#include "testbed2/generated/mqtt/manyparaminterfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::MQTT;

ManyParamInterfaceService::ManyParamInterfaceService(std::shared_ptr<IManyParamInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

ManyParamInterfaceService::~ManyParamInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> ManyParamInterfaceService::createTopicMap()
{
    return {
        {std::string("testbed2/ManyParamInterface/set/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp1(args); } },
        {std::string("testbed2/ManyParamInterface/set/prop2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp2(args); } },
        {std::string("testbed2/ManyParamInterface/set/prop3"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp3(args); } },
        {std::string("testbed2/ManyParamInterface/set/prop4"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetProp4(args); } },
        {std::string("testbed2/ManyParamInterface/rpc/func1"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc1(args, responseTopic, correlationData); } },
        {std::string("testbed2/ManyParamInterface/rpc/func2"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc2(args, responseTopic, correlationData); } },
        {std::string("testbed2/ManyParamInterface/rpc/func3"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc3(args, responseTopic, correlationData); } },
        {std::string("testbed2/ManyParamInterface/rpc/func4"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFunc4(args, responseTopic, correlationData); } },
    };
}

void ManyParamInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onProp1Changed(m_impl->getProp1());
    onProp2Changed(m_impl->getProp2());
    onProp3Changed(m_impl->getProp3());
    onProp4Changed(m_impl->getProp4());
}
void ManyParamInterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<int>();
    m_impl->setProp1(prop1);
}
void ManyParamInterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<int>();
    m_impl->setProp2(prop2);
}
void ManyParamInterfaceService::onSetProp3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop3 = json_args.get<int>();
    m_impl->setProp3(prop3);
}
void ManyParamInterfaceService::onSetProp4(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop4 = json_args.get<int>();
    m_impl->setProp4(prop4);
}
void ManyParamInterfaceService::onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    auto result = m_impl->func1(param1);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void ManyParamInterfaceService::onInvokeFunc2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    const int& param2 = json_args.at(1).get<int>();
    auto result = m_impl->func2(param1, param2);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void ManyParamInterfaceService::onInvokeFunc3(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    const int& param2 = json_args.at(1).get<int>();
    const int& param3 = json_args.at(2).get<int>();
    auto result = m_impl->func3(param1, param2, param3);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void ManyParamInterfaceService::onInvokeFunc4(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    const int& param2 = json_args.at(1).get<int>();
    const int& param3 = json_args.at(2).get<int>();
    const int& param4 = json_args.at(3).get<int>();
    auto result = m_impl->func4(param1, param2, param3, param4);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void ManyParamInterfaceService::onSig1(int param1)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1 };
        static const auto topic = std::string("testbed2/ManyParamInterface/sig/sig1");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void ManyParamInterfaceService::onSig2(int param1, int param2)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1, param2 };
        static const auto topic = std::string("testbed2/ManyParamInterface/sig/sig2");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void ManyParamInterfaceService::onSig3(int param1, int param2, int param3)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1, param2, param3 };
        static const auto topic = std::string("testbed2/ManyParamInterface/sig/sig3");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void ManyParamInterfaceService::onSig4(int param1, int param2, int param3, int param4)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { param1, param2, param3, param4 };
        static const auto topic = std::string("testbed2/ManyParamInterface/sig/sig4");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void ManyParamInterfaceService::onProp1Changed(int prop1)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/ManyParamInterface/prop/prop1");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop1).dump());
    }
}
void ManyParamInterfaceService::onProp2Changed(int prop2)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/ManyParamInterface/prop/prop2");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop2).dump());
    }
}
void ManyParamInterfaceService::onProp3Changed(int prop3)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/ManyParamInterface/prop/prop3");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop3).dump());
    }
}
void ManyParamInterfaceService::onProp4Changed(int prop4)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed2/ManyParamInterface/prop/prop4");
        m_service->notifyPropertyChange(topic, nlohmann::json(prop4).dump());
    }
}
