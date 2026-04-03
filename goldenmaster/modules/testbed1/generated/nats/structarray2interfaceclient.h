#pragma once

#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structarray2interface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <atomic>
#include <future>
#include <unordered_map>

namespace Test {
namespace Testbed1 {
namespace Nats {
/**
 * @brief NATS adapter for StructArray2Interface.
 *
 * @note Threading: property-change and signal callbacks arrive on the NATS transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 * Property storage is not guarded by a mutex; wrap with StructArray2InterfaceThreadSafeDecorator
 * for concurrent access from multiple threads.
 */
class TEST_TESTBED1_EXPORT StructArray2InterfaceClient : public IStructArray2Interface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<StructArray2InterfaceClient>
{
protected:
    explicit StructArray2InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<StructArray2InterfaceClient> create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~StructArray2InterfaceClient() override;
    void init();
    const StructBoolWithArray& getPropBool() const override;
    void setPropBool(const StructBoolWithArray& propBool) override;
    const StructIntWithArray& getPropInt() const override;
    void setPropInt(const StructIntWithArray& propInt) override;
    const StructFloatWithArray& getPropFloat() const override;
    void setPropFloat(const StructFloatWithArray& propFloat) override;
    const StructStringWithArray& getPropString() const override;
    void setPropString(const StructStringWithArray& propString) override;
    const StructEnumWithArray& getPropEnum() const override;
    void setPropEnum(const StructEnumWithArray& propEnum) override;
    std::list<StructBool> funcBool(const StructBoolWithArray& paramBool) override;
    std::future<std::list<StructBool>> funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;
    std::list<StructInt> funcInt(const StructIntWithArray& paramInt) override;
    std::future<std::list<StructInt>> funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;
    std::list<StructFloat> funcFloat(const StructFloatWithArray& paramFloat) override;
    std::future<std::list<StructFloat>> funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;
    std::list<StructString> funcString(const StructStringWithArray& paramString) override;
    std::future<std::list<StructString>> funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;
    std::list<Enum0Enum> funcEnum(const StructEnumWithArray& paramEnum) override;
    std::future<std::list<Enum0Enum>> funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback = nullptr) override;
    IStructArray2InterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructBoolWithArray
    StructBoolWithArray _to_PropBool(const std::string& args);
    /// @brief sets the value for the property PropBool coming from the service
    void setPropBoolLocal(const StructBoolWithArray& propBool);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructIntWithArray
    StructIntWithArray _to_PropInt(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    void setPropIntLocal(const StructIntWithArray& propInt);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructFloatWithArray
    StructFloatWithArray _to_PropFloat(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    void setPropFloatLocal(const StructFloatWithArray& propFloat);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructStringWithArray
    StructStringWithArray _to_PropString(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    void setPropStringLocal(const StructStringWithArray& propString);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructEnumWithArray
    StructEnumWithArray _to_PropEnum(const std::string& args);
    /// @brief sets the value for the property PropEnum coming from the service
    void setPropEnumLocal(const StructEnumWithArray& propEnum);
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) const StructBoolWithArray& paramBool
    void onSigBool(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt coming from the service
    /// @param args contains the param(s) of the type(s) const StructIntWithArray& paramInt
    void onSigInt(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat coming from the service
    /// @param args contains the param(s) of the type(s) const StructFloatWithArray& paramFloat
    void onSigFloat(const std::string& args) const;
    /// @brief publishes the value for the signal SigString coming from the service
    /// @param args contains the param(s) of the type(s) const StructStringWithArray& paramString
    void onSigString(const std::string& args) const;
    /** Local storage for properties values. */
    StructArray2InterfaceData m_data;
    uint64_t m_requestInitCallId = 0;
    std::atomic<bool> m_initialized{false};
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for StructArray2Interface */
    std::unique_ptr<IStructArray2InterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace Testbed1
} // namespace Test
