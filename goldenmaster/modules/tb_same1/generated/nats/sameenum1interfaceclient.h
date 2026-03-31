#pragma once

#include "tb_same1/generated/api/common.h"
#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/core/sameenum1interface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <atomic>
#include <future>
#include <unordered_map>

namespace Test {
namespace TbSame1 {
namespace Nats {
/**
 * @brief NATS adapter for SameEnum1Interface.
 *
 * @note Threading: property-change and signal callbacks arrive on the NATS transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 */
class TEST_TB_SAME1_EXPORT SameEnum1InterfaceClient : public ISameEnum1Interface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameEnum1InterfaceClient>
{
protected:
    explicit SameEnum1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<SameEnum1InterfaceClient> create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~SameEnum1InterfaceClient() override;
    void init();
    Enum1Enum getProp1() const override;
    void setProp1(Enum1Enum prop1) override;
    Enum1Enum func1(Enum1Enum param1) override;
    std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) override;
    ISameEnum1InterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type Enum1Enum
    Enum1Enum _to_Prop1(const std::string& args);
    /// @brief sets the value for the property Prop1 coming from the service
    void setProp1Local(Enum1Enum prop1);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1
    void onSig1(const std::string& args) const;
    /** Local storage for properties values. */
    SameEnum1InterfaceData m_data;
    uint64_t m_requestInitCallId = 0;
    std::atomic<bool> m_initialized{false};
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for SameEnum1Interface */
    std::unique_ptr<ISameEnum1InterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbSame1
} // namespace Test
