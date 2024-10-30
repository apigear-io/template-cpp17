#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/nopropertiesinterface.data.h"
#include "apigear/nats/natsclient.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT NoPropertiesInterfaceClient : public INoPropertiesInterface
{
public:
    explicit NoPropertiesInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~NoPropertiesInterfaceClient() override;
    void funcVoid() override;
    std::future<void> funcVoidAsync() override;
    bool funcBool(bool paramBool) override;
    std::future<bool> funcBoolAsync(bool paramBool) override;
    INoPropertiesInterfacePublisher& _getPublisher() const override;
private:
    /// @brief publishes the value for the signal SigVoid coming from the service
    /// @param args contains the param(s) of the type(s) 
    void onSigVoid(const std::string& args) const;
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) bool paramBool
    void onSigBool(const std::string& args) const;
    std::shared_ptr<ApiGear::Nats::Client> m_client;

    /** The publisher for NoPropertiesInterface */
    std::unique_ptr<INoPropertiesInterfacePublisher> m_publisher;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
