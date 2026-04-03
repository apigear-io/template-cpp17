

#include "tb_struct_array/generated/olink/structarrayfieldinterfaceclient.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.publisher.h"
#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iclientnode.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

using namespace Test::TbStructArray;
using namespace Test::TbStructArray::olink;

namespace 
{
const std::string interfaceId = "tb.struct.array.StructArrayFieldInterface";
}

StructArrayFieldInterfaceClient::StructArrayFieldInterfaceClient()
    : m_publisher(std::make_unique<StructArrayFieldInterfacePublisher>())
{}

void StructArrayFieldInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propStructArray")) {
        setPropStructArrayLocal(fields["propStructArray"].get<StructWithArrayOfStructs>());
    }
    if(fields.contains("propEnumArray")) {
        setPropEnumArrayLocal(fields["propEnumArray"].get<StructWithArrayOfEnums>());
    }
    if(fields.contains("propIntArray")) {
        setPropIntArrayLocal(fields["propIntArray"].get<StructWithArrayOfInts>());
    }
    if(fields.contains("propMixed")) {
        setPropMixedLocal(fields["propMixed"].get<MixedStruct>());
    }
}

void StructArrayFieldInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propStructArray") {
        setPropStructArrayLocal(value.get<StructWithArrayOfStructs>());
    }
    else if ( propertyName == "propEnumArray") {
        setPropEnumArrayLocal(value.get<StructWithArrayOfEnums>());
    }
    else if ( propertyName == "propIntArray") {
        setPropIntArrayLocal(value.get<StructWithArrayOfInts>());
    }
    else if ( propertyName == "propMixed") {
        setPropMixedLocal(value.get<MixedStruct>());
    }
}

void StructArrayFieldInterfaceClient::setPropStructArray(const StructWithArrayOfStructs& propStructArray)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propStructArray");
    m_node->setRemoteProperty(propertyId, propStructArray);
}

void StructArrayFieldInterfaceClient::setPropStructArrayLocal(const StructWithArrayOfStructs& propStructArray)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propStructArrayMutex);
        if (m_data.m_propStructArray == propStructArray) {
            return;
        }
        m_data.m_propStructArray = propStructArray;
    }

    m_publisher->publishPropStructArrayChanged(propStructArray);
}

const StructWithArrayOfStructs& StructArrayFieldInterfaceClient::getPropStructArray() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStructArrayMutex);
    return m_data.m_propStructArray;
}

void StructArrayFieldInterfaceClient::setPropEnumArray(const StructWithArrayOfEnums& propEnumArray)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propEnumArray");
    m_node->setRemoteProperty(propertyId, propEnumArray);
}

void StructArrayFieldInterfaceClient::setPropEnumArrayLocal(const StructWithArrayOfEnums& propEnumArray)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propEnumArrayMutex);
        if (m_data.m_propEnumArray == propEnumArray) {
            return;
        }
        m_data.m_propEnumArray = propEnumArray;
    }

    m_publisher->publishPropEnumArrayChanged(propEnumArray);
}

const StructWithArrayOfEnums& StructArrayFieldInterfaceClient::getPropEnumArray() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propEnumArrayMutex);
    return m_data.m_propEnumArray;
}

void StructArrayFieldInterfaceClient::setPropIntArray(const StructWithArrayOfInts& propIntArray)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propIntArray");
    m_node->setRemoteProperty(propertyId, propIntArray);
}

void StructArrayFieldInterfaceClient::setPropIntArrayLocal(const StructWithArrayOfInts& propIntArray)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propIntArrayMutex);
        if (m_data.m_propIntArray == propIntArray) {
            return;
        }
        m_data.m_propIntArray = propIntArray;
    }

    m_publisher->publishPropIntArrayChanged(propIntArray);
}

const StructWithArrayOfInts& StructArrayFieldInterfaceClient::getPropIntArray() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntArrayMutex);
    return m_data.m_propIntArray;
}

void StructArrayFieldInterfaceClient::setPropMixed(const MixedStruct& propMixed)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propMixed");
    m_node->setRemoteProperty(propertyId, propMixed);
}

void StructArrayFieldInterfaceClient::setPropMixedLocal(const MixedStruct& propMixed)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propMixedMutex);
        if (m_data.m_propMixed == propMixed) {
            return;
        }
        m_data.m_propMixed = propMixed;
    }

    m_publisher->publishPropMixedChanged(propMixed);
}

const MixedStruct& StructArrayFieldInterfaceClient::getPropMixed() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propMixedMutex);
    return m_data.m_propMixed;
}

MixedStruct StructArrayFieldInterfaceClient::funcMixed(const MixedStruct& paramMixed)
{
    return funcMixedAsync(paramMixed).get();
}

std::future<MixedStruct> StructArrayFieldInterfaceClient::funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<MixedStruct>{};
    }
    std::shared_ptr<std::promise<MixedStruct>> resultPromise = std::make_shared<std::promise<MixedStruct>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcMixed");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramMixed}), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const MixedStruct& value = arg.value.get<MixedStruct>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
        });
    return resultPromise->get_future();
}

StructWithArrayOfStructs StructArrayFieldInterfaceClient::funcStructArray(const StructWithArrayOfStructs& paramPoints)
{
    return funcStructArrayAsync(paramPoints).get();
}

std::future<StructWithArrayOfStructs> StructArrayFieldInterfaceClient::funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<StructWithArrayOfStructs>{};
    }
    std::shared_ptr<std::promise<StructWithArrayOfStructs>> resultPromise = std::make_shared<std::promise<StructWithArrayOfStructs>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcStructArray");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramPoints}), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const StructWithArrayOfStructs& value = arg.value.get<StructWithArrayOfStructs>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
        });
    return resultPromise->get_future();
}

std::string StructArrayFieldInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void StructArrayFieldInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigMixed") {
        m_publisher->publishSigMixed(args[0].get<MixedStruct>());   
        return;
    }
    if(signalName == "sigStructArray") {
        m_publisher->publishSigStructArray(args[0].get<StructWithArrayOfStructs>());   
        return;
    }
}

void StructArrayFieldInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void StructArrayFieldInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void StructArrayFieldInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool StructArrayFieldInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

IStructArrayFieldInterfacePublisher& StructArrayFieldInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
