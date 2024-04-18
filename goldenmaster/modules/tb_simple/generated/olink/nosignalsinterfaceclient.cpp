

#include "tb_simple/generated/olink/nosignalsinterfaceclient.h"
#include "tb_simple/generated/core/nosignalsinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.NoSignalsInterface";
}

NoSignalsInterfaceClient::NoSignalsInterfaceClient()
    : m_publisher(std::make_unique<NoSignalsInterfacePublisher>())
{}

void NoSignalsInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<bool>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<int>());
    }
}

void NoSignalsInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propBool") {
        setPropBoolLocal(value.get<bool>());
    }
    else if ( propertyName == "propInt") {
        setPropIntLocal(value.get<int>());
    }
}

void NoSignalsInterfaceClient::setPropBool(bool propBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    m_node->setRemoteProperty(propertyId, propBool);
}

void NoSignalsInterfaceClient::setPropBoolLocal(bool propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

bool NoSignalsInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void NoSignalsInterfaceClient::setPropInt(int propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void NoSignalsInterfaceClient::setPropIntLocal(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int NoSignalsInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void NoSignalsInterfaceClient::funcVoid()
{
    return funcVoidAsync().get();
}

std::future<void> NoSignalsInterfaceClient::funcVoidAsync()
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<void>{};
    }
    std::shared_ptr<std::promise<void>> resultPromise = std::make_shared<std::promise<void>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcVoid");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            (void) arg;
            resultPromise->set_value();
        });
    return resultPromise->get_future();
}

bool NoSignalsInterfaceClient::funcBool(bool paramBool)
{
    return funcBoolAsync(paramBool).get();
}

std::future<bool> NoSignalsInterfaceClient::funcBoolAsync(bool paramBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<bool>{};
    }
    std::shared_ptr<std::promise<bool>> resultPromise = std::make_shared<std::promise<bool>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcBool");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramBool}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const bool& value = arg.value.get<bool>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string NoSignalsInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void NoSignalsInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    (void) args;
    (void) signalName;
}

void NoSignalsInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void NoSignalsInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void NoSignalsInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool NoSignalsInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

INoSignalsInterfacePublisher& NoSignalsInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
