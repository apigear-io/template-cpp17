

#include "tb_names/generated/olink/namesclient.h"
#include "tb_names/generated/core/names.publisher.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbNames;
using namespace Test::TbNames::olink;

namespace 
{
const std::string interfaceId = "tb.names.Nam_Es";
}

Nam_EsClient::Nam_EsClient()
    : m_publisher(std::make_unique<NamEsPublisher>())
{}

void Nam_EsClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("Switch")) {
        setSwitchLocal(fields["Switch"].get<bool>());
    }
    if(fields.contains("SOME_PROPERTY")) {
        setSomePropertyLocal(fields["SOME_PROPERTY"].get<int>());
    }
    if(fields.contains("Some_Poperty2")) {
        setSomePoperty2Local(fields["Some_Poperty2"].get<int>());
    }
}

void Nam_EsClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "Switch") {
        setSwitchLocal(value.get<bool>());
    }
    else if ( propertyName == "SOME_PROPERTY") {
        setSomePropertyLocal(value.get<int>());
    }
    else if ( propertyName == "Some_Poperty2") {
        setSomePoperty2Local(value.get<int>());
    }
}

void Nam_EsClient::setSwitch(bool Switch)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "Switch");
    m_node->setRemoteProperty(propertyId, Switch);
}

void Nam_EsClient::setSwitchLocal(bool Switch)
{
    if (m_data.m_Switch != Switch) {
        m_data.m_Switch = Switch;
        m_publisher->publishSwitchChanged(Switch);
    }
}

bool Nam_EsClient::getSwitch() const
{
    return m_data.m_Switch;
}

void Nam_EsClient::setSomeProperty(int SOME_PROPERTY)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "SOME_PROPERTY");
    m_node->setRemoteProperty(propertyId, SOME_PROPERTY);
}

void Nam_EsClient::setSomePropertyLocal(int SOME_PROPERTY)
{
    if (m_data.m_SOME_PROPERTY != SOME_PROPERTY) {
        m_data.m_SOME_PROPERTY = SOME_PROPERTY;
        m_publisher->publishSomePropertyChanged(SOME_PROPERTY);
    }
}

int Nam_EsClient::getSomeProperty() const
{
    return m_data.m_SOME_PROPERTY;
}

void Nam_EsClient::setSomePoperty2(int Some_Poperty2)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "Some_Poperty2");
    m_node->setRemoteProperty(propertyId, Some_Poperty2);
}

void Nam_EsClient::setSomePoperty2Local(int Some_Poperty2)
{
    if (m_data.m_Some_Poperty2 != Some_Poperty2) {
        m_data.m_Some_Poperty2 = Some_Poperty2;
        m_publisher->publishSomePoperty2Changed(Some_Poperty2);
    }
}

int Nam_EsClient::getSomePoperty2() const
{
    return m_data.m_Some_Poperty2;
}

void Nam_EsClient::sOME_FUNCTION(bool SOME_PARAM)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    ApiGear::ObjectLink::InvokeReplyFunc func = [this](ApiGear::ObjectLink::InvokeReplyArg arg)
        {
            (void) this;
            (void) arg;
        };
    const nlohmann::json &args = nlohmann::json::array({ SOME_PARAM });
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "SOME_FUNCTION");
    m_node->invokeRemote(operationId, args, func);
}

std::future<void> Nam_EsClient::sOME_FUNCTIONAsync(bool SOME_PARAM)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<void>{};
    }
    std::shared_ptr<std::promise<void>> resultPromise = std::make_shared<std::promise<void>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "SOME_FUNCTION");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({SOME_PARAM}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            (void) arg;
            resultPromise->set_value();
        });
    return resultPromise->get_future();
}

void Nam_EsClient::some_Function2(bool Some_Param)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    ApiGear::ObjectLink::InvokeReplyFunc func = [this](ApiGear::ObjectLink::InvokeReplyArg arg)
        {
            (void) this;
            (void) arg;
        };
    const nlohmann::json &args = nlohmann::json::array({ Some_Param });
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "Some_Function2");
    m_node->invokeRemote(operationId, args, func);
}

std::future<void> Nam_EsClient::some_Function2Async(bool Some_Param)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<void>{};
    }
    std::shared_ptr<std::promise<void>> resultPromise = std::make_shared<std::promise<void>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "Some_Function2");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({Some_Param}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            (void) arg;
            resultPromise->set_value();
        });
    return resultPromise->get_future();
}

std::string Nam_EsClient::olinkObjectName()
{
    return interfaceId;
}

void Nam_EsClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "SOME_SIGNAL") {
        m_publisher->publishSomeSignal(args[0].get<bool>());   
        return;
    }
    if(signalName == "Some_Signal2") {
        m_publisher->publishSomeSignal2(args[0].get<bool>());   
        return;
    }
}

void Nam_EsClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void Nam_EsClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void Nam_EsClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool Nam_EsClient::isReady() const
{
    return m_node != nullptr;
}

INamEsPublisher& Nam_EsClient::_getPublisher() const
{
    return *m_publisher;
}
