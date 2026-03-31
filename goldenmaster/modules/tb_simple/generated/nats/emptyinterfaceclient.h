#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/emptyinterface.data.h"
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
 * @brief NATS adapter for EmptyInterface.
 *
 * @note Threading: property-change and signal callbacks arrive on the NATS transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 */
class TEST_TB_SIMPLE_EXPORT EmptyInterfaceClient : public IEmptyInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<EmptyInterfaceClient>
{
protected:
    explicit EmptyInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<EmptyInterfaceClient> create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~EmptyInterfaceClient() override;
    void init();
    IEmptyInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    uint64_t m_requestInitCallId = 0;
    std::atomic<bool> m_initialized{false};
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for EmptyInterface */
    std::unique_ptr<IEmptyInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
