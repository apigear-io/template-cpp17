#include "tb_struct_array/generated/mqtt/structarrayfieldinterfaceservice.h"
#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"
#include <iostream>

using namespace Test::TbStructArray;
using namespace Test::TbStructArray::MQTT;

StructArrayFieldInterfaceService::StructArrayFieldInterfaceService(std::shared_ptr<IStructArrayFieldInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : MqttBaseAdapter(service, createTopicMap())
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusId = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

StructArrayFieldInterfaceService::~StructArrayFieldInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusId);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> StructArrayFieldInterfaceService::createTopicMap()
{
    return {
        {std::string("tb.struct.array/StructArrayFieldInterface/set/propStructArray"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropStructArray(args); } },
        {std::string("tb.struct.array/StructArrayFieldInterface/set/propEnumArray"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropEnumArray(args); } },
        {std::string("tb.struct.array/StructArrayFieldInterface/set/propIntArray"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropIntArray(args); } },
        {std::string("tb.struct.array/StructArrayFieldInterface/set/propMixed"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetPropMixed(args); } },
        {std::string("tb.struct.array/StructArrayFieldInterface/rpc/funcMixed"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncMixed(args, responseTopic, correlationData); } },
        {std::string("tb.struct.array/StructArrayFieldInterface/rpc/funcStructArray"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeFuncStructArray(args, responseTopic, correlationData); } },
    };
}

void StructArrayFieldInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // send current values
    onPropStructArrayChanged(m_impl->getPropStructArray());
    onPropEnumArrayChanged(m_impl->getPropEnumArray());
    onPropIntArrayChanged(m_impl->getPropIntArray());
    onPropMixedChanged(m_impl->getPropMixed());
}
void StructArrayFieldInterfaceService::onSetPropStructArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propStructArray = json_args.get<StructWithArrayOfStructs>();
    m_impl->setPropStructArray(propStructArray);
}
void StructArrayFieldInterfaceService::onSetPropEnumArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propEnumArray = json_args.get<StructWithArrayOfEnums>();
    m_impl->setPropEnumArray(propEnumArray);
}
void StructArrayFieldInterfaceService::onSetPropIntArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propIntArray = json_args.get<StructWithArrayOfInts>();
    m_impl->setPropIntArray(propIntArray);
}
void StructArrayFieldInterfaceService::onSetPropMixed(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propMixed = json_args.get<MixedStruct>();
    m_impl->setPropMixed(propMixed);
}
void StructArrayFieldInterfaceService::onInvokeFuncMixed(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const MixedStruct& paramMixed = json_args.at(0).get<MixedStruct>();
    auto result = m_impl->funcMixed(paramMixed);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArrayFieldInterfaceService::onInvokeFuncStructArray(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructWithArrayOfStructs& paramPoints = json_args.at(0).get<StructWithArrayOfStructs>();
    auto result = m_impl->funcStructArray(paramPoints);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void StructArrayFieldInterfaceService::onSigMixed(const MixedStruct& paramMixed)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramMixed };
        static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/sig/sigMixed");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArrayFieldInterfaceService::onSigStructArray(const StructWithArrayOfStructs& paramPoints)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { paramPoints };
        static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/sig/sigStructArray");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void StructArrayFieldInterfaceService::onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/prop/propStructArray");
        m_service->notifyPropertyChange(topic, nlohmann::json(propStructArray).dump());
    }
}
void StructArrayFieldInterfaceService::onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/prop/propEnumArray");
        m_service->notifyPropertyChange(topic, nlohmann::json(propEnumArray).dump());
    }
}
void StructArrayFieldInterfaceService::onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/prop/propIntArray");
        m_service->notifyPropertyChange(topic, nlohmann::json(propIntArray).dump());
    }
}
void StructArrayFieldInterfaceService::onPropMixedChanged(const MixedStruct& propMixed)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/prop/propMixed");
        m_service->notifyPropertyChange(topic, nlohmann::json(propMixed).dump());
    }
}
