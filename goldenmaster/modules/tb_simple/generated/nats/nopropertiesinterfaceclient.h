#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/nopropertiesinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <atomic>
#include <future>
#include <unordered_map>

namespace Test {
namespace TbSimple {
namespace Nats {
/**
 * @brief NATS adapter for NoPropertiesInterface.
 *
 * @note Threading: property-change and signal callbacks arrive on the NATS transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 * Property storage is not guarded by a mutex; wrap with NoPropertiesInterfaceThreadSafeDecorator
 * for concurrent access from multiple threads.
 */
class TEST_TB_SIMPLE_EXPORT NoPropertiesInterfaceClient : public INoPropertiesInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NoPropertiesInterfaceClient>
{
protected:
    explicit NoPropertiesInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<NoPropertiesInterfaceClient> create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~NoPropertiesInterfaceClient() override;
    void init();
    void funcVoid() override;
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;
    bool funcBool(bool paramBool) override;
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;
    INoPropertiesInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief publishes the value for the signal SigVoid coming from the service
    /// @param args contains the param(s) of the type(s) 
    void onSigVoid(const std::string& args) const;
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) bool paramBool
    void onSigBool(const std::string& args) const;
    uint64_t m_requestInitCallId = 0;
    std::atomic<bool> m_initialized{false};
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for NoPropertiesInterface */
    std::unique_ptr<INoPropertiesInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
