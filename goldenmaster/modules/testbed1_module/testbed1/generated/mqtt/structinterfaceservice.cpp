#include "testbed1/generated/mqtt/structinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include "apigear/mqtt/mqtttopic.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::MQTT;

StructInterfaceService::StructInterfaceService(std::shared_ptr<IStructInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusRegistrationID = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
    // subscribe to all property change request methods
    m_service->subscribeTopic(std::string("testbed1/StructInterface/set/propBool"), [this](const std::string& topic, const std::string& args, const std::string&, const std::string&){ onSetProperty(topic, args); });
    m_service->subscribeTopic(std::string("testbed1/StructInterface/set/propInt"), [this](const std::string& topic, const std::string& args, const std::string&, const std::string&){ onSetProperty(topic, args); });
    m_service->subscribeTopic(std::string("testbed1/StructInterface/set/propFloat"), [this](const std::string& topic, const std::string& args, const std::string&, const std::string&){ onSetProperty(topic, args); });
    m_service->subscribeTopic(std::string("testbed1/StructInterface/set/propString"), [this](const std::string& topic, const std::string& args, const std::string&, const std::string&){ onSetProperty(topic, args); });
    m_service->subscribeTopic(std::string("testbed1/StructInterface/rpc/funcBool"), [this](const std::string& topic, const std::string& args, const std::string& responseTopic, const std::string& correlationData) { onInvoke(topic, args, responseTopic, correlationData); });
    m_service->subscribeTopic(std::string("testbed1/StructInterface/rpc/funcInt"), [this](const std::string& topic, const std::string& args, const std::string& responseTopic, const std::string& correlationData) { onInvoke(topic, args, responseTopic, correlationData); });
    m_service->subscribeTopic(std::string("testbed1/StructInterface/rpc/funcFloat"), [this](const std::string& topic, const std::string& args, const std::string& responseTopic, const std::string& correlationData) { onInvoke(topic, args, responseTopic, correlationData); });
    m_service->subscribeTopic(std::string("testbed1/StructInterface/rpc/funcString"), [this](const std::string& topic, const std::string& args, const std::string& responseTopic, const std::string& correlationData) { onInvoke(topic, args, responseTopic, correlationData); });

}

StructInterfaceService::~StructInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/set/propBool"));
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/set/propInt"));
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/set/propFloat"));
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/set/propString"));
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/rpc/funcBool"));
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/rpc/funcInt"));
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/rpc/funcFloat"));
    m_service->unsubscribeTopic(std::string("testbed1/StructInterface/rpc/funcString"));
}

void StructInterfaceService::onConnectionStatusChanged(bool connectionStatus)
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

void StructInterfaceService::onSetProperty(const std::string& topic, const std::string& args)
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::string& name = ApiGear::MQTT::Topic(topic).getEntityName();
    if(name == "propBool") {
        auto propBool = json_args.get<StructBool>();
        m_impl->setPropBool(propBool);
        return;
    }
    if(name == "propInt") {
        auto propInt = json_args.get<StructInt>();
        m_impl->setPropInt(propInt);
        return;
    }
    if(name == "propFloat") {
        auto propFloat = json_args.get<StructFloat>();
        m_impl->setPropFloat(propFloat);
        return;
    }
    if(name == "propString") {
        auto propString = json_args.get<StructString>();
        m_impl->setPropString(propString);
        return;
    }
}

void StructInterfaceService::onInvoke(const std::string& topic, const std::string& args, const std::string& responseTopic, const std::string& correlationData)
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::string& name = ApiGear::MQTT::Topic(topic).getEntityName();


    if(name == "funcBool") {
        const StructBool& paramBool = json_args.at(0).get<StructBool>();
        auto result = m_impl->funcBool(paramBool);
        m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
        return;
    }
    if(name == "funcInt") {
        const StructInt& paramInt = json_args.at(0).get<StructInt>();
        auto result = m_impl->funcInt(paramInt);
        m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
        return;
    }
    if(name == "funcFloat") {
        const StructFloat& paramFloat = json_args.at(0).get<StructFloat>();
        auto result = m_impl->funcFloat(paramFloat);
        m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
        return;
    }
    if(name == "funcString") {
        const StructString& paramString = json_args.at(0).get<StructString>();
        auto result = m_impl->funcString(paramString);
        m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
        return;
    }
}
void StructInterfaceService::onSigBool(const StructBool& paramBool)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramBool };
        static const auto topic = std::string("testbed1/StructInterface/sig/sigBool");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructInterfaceService::onSigInt(const StructInt& paramInt)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramInt };
        static const auto topic = std::string("testbed1/StructInterface/sig/sigInt");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructInterfaceService::onSigFloat(const StructFloat& paramFloat)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramFloat };
        static const auto topic = std::string("testbed1/StructInterface/sig/sigFloat");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructInterfaceService::onSigString(const StructString& paramString)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramString };
        static const auto topic = std::string("testbed1/StructInterface/sig/sigString");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructInterfaceService::onPropBoolChanged(const StructBool& propBool)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructInterface/prop/propBool");
        m_service->notifyPropertyChange(topic, nlohmann::json(propBool).dump());
    }
}
void StructInterfaceService::onPropIntChanged(const StructInt& propInt)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructInterface/prop/propInt");
        m_service->notifyPropertyChange(topic, nlohmann::json(propInt).dump());
    }
}
void StructInterfaceService::onPropFloatChanged(const StructFloat& propFloat)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructInterface/prop/propFloat");
        m_service->notifyPropertyChange(topic, nlohmann::json(propFloat).dump());
    }
}
void StructInterfaceService::onPropStringChanged(const StructString& propString)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("testbed1/StructInterface/prop/propString");
        m_service->notifyPropertyChange(topic, nlohmann::json(propString).dump());
    }
}
