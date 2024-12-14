#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/voidinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT VoidInterfaceClient : public IVoidInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<VoidInterfaceClient>
{
protected:
    explicit VoidInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<VoidInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~VoidInterfaceClient() override;
    void init();
    void funcVoid() override;
    std::future<void> funcVoidAsync() override;
    IVoidInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    /// @brief publishes the value for the signal SigVoid coming from the service
    /// @param args contains the param(s) of the type(s) 
    void onSigVoid(const std::string& args) const;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for VoidInterface */
    std::unique_ptr<IVoidInterfacePublisher> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
