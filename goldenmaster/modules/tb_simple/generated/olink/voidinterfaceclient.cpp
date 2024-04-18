

#include "tb_simple/generated/olink/voidinterfaceclient.h"
#include "tb_simple/generated/core/voidinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.VoidInterface";
}

VoidInterfaceClient::VoidInterfaceClient()
    : m_publisher(std::make_unique<VoidInterfacePublisher>())
{}

void VoidInterfaceClient::applyState(const nlohmann::json& fields) 
{
    // no properties to apply state
    (void) fields;
}

void VoidInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{// no properties to apply state
    (void) propertyName;
    (void) value;
}

void VoidInterfaceClient::funcVoid()
{
    ApiGear::ObjectLink::InvokeReplyFunc func = [this](ApiGear::ObjectLink::InvokeReplyArg arg)
        {
            (void) this;
            (void) arg;
        };
    const nlohmann::json &args = nlohmann::json::array({  });
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcVoid");
    m_node->invokeRemote(operationId, args, func);
}

std::future<void> VoidInterfaceClient::funcVoidAsync()
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

std::string VoidInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void VoidInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    (void) args;
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigVoid") {
        m_publisher->publishSigVoid();   
        return;
    }
}

void VoidInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void VoidInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void VoidInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool VoidInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

IVoidInterfacePublisher& VoidInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
