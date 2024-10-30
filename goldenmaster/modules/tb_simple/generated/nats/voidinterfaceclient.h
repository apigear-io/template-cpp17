#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/voidinterface.data.h"
#include "apigear/nats/natsclient.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT VoidInterfaceClient : public IVoidInterface
{
public:
    explicit VoidInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~VoidInterfaceClient() override;
    void funcVoid() override;
    std::future<void> funcVoidAsync() override;
    IVoidInterfacePublisher& _getPublisher() const override;
private:
    /// @brief publishes the value for the signal SigVoid coming from the service
    /// @param args contains the param(s) of the type(s) 
    void onSigVoid(const std::string& args) const;
    std::shared_ptr<ApiGear::Nats::Client> m_client;

    /** The publisher for VoidInterface */
    std::unique_ptr<IVoidInterfacePublisher> m_publisher;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
