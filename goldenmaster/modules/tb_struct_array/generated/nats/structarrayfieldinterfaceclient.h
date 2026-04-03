#pragma once

#include "tb_struct_array/generated/api/common.h"
#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <atomic>
#include <future>
#include <unordered_map>

namespace Test {
namespace TbStructArray {
namespace Nats {
/**
 * @brief NATS adapter for StructArrayFieldInterface.
 *
 * @note Threading: property-change and signal callbacks arrive on the NATS transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 * Property storage is not guarded by a mutex; wrap with StructArrayFieldInterfaceThreadSafeDecorator
 * for concurrent access from multiple threads.
 */
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfaceClient : public IStructArrayFieldInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<StructArrayFieldInterfaceClient>
{
protected:
    explicit StructArrayFieldInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<StructArrayFieldInterfaceClient> create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~StructArrayFieldInterfaceClient() override;
    void init();
    const StructWithArrayOfStructs& getPropStructArray() const override;
    void setPropStructArray(const StructWithArrayOfStructs& propStructArray) override;
    const StructWithArrayOfEnums& getPropEnumArray() const override;
    void setPropEnumArray(const StructWithArrayOfEnums& propEnumArray) override;
    const StructWithArrayOfInts& getPropIntArray() const override;
    void setPropIntArray(const StructWithArrayOfInts& propIntArray) override;
    const MixedStruct& getPropMixed() const override;
    void setPropMixed(const MixedStruct& propMixed) override;
    MixedStruct funcMixed(const MixedStruct& paramMixed) override;
    std::future<MixedStruct> funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback = nullptr) override;
    StructWithArrayOfStructs funcStructArray(const StructWithArrayOfStructs& paramPoints) override;
    std::future<StructWithArrayOfStructs> funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback = nullptr) override;
    IStructArrayFieldInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructWithArrayOfStructs
    StructWithArrayOfStructs _to_PropStructArray(const std::string& args);
    /// @brief sets the value for the property PropStructArray coming from the service
    void setPropStructArrayLocal(const StructWithArrayOfStructs& propStructArray);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructWithArrayOfEnums
    StructWithArrayOfEnums _to_PropEnumArray(const std::string& args);
    /// @brief sets the value for the property PropEnumArray coming from the service
    void setPropEnumArrayLocal(const StructWithArrayOfEnums& propEnumArray);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructWithArrayOfInts
    StructWithArrayOfInts _to_PropIntArray(const std::string& args);
    /// @brief sets the value for the property PropIntArray coming from the service
    void setPropIntArrayLocal(const StructWithArrayOfInts& propIntArray);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type MixedStruct
    MixedStruct _to_PropMixed(const std::string& args);
    /// @brief sets the value for the property PropMixed coming from the service
    void setPropMixedLocal(const MixedStruct& propMixed);
    /// @brief publishes the value for the signal SigMixed coming from the service
    /// @param args contains the param(s) of the type(s) const MixedStruct& paramMixed
    void onSigMixed(const std::string& args) const;
    /// @brief publishes the value for the signal SigStructArray coming from the service
    /// @param args contains the param(s) of the type(s) const StructWithArrayOfStructs& paramPoints
    void onSigStructArray(const std::string& args) const;
    /** Local storage for properties values. */
    StructArrayFieldInterfaceData m_data;
    uint64_t m_requestInitCallId = 0;
    std::atomic<bool> m_initialized{false};
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for StructArrayFieldInterface */
    std::unique_ptr<IStructArrayFieldInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbStructArray
} // namespace Test
