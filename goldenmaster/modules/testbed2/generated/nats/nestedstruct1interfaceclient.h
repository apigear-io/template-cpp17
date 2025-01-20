#pragma once

#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/nestedstruct1interface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace Testbed2 {
namespace Nats {
class TEST_TESTBED2_EXPORT NestedStruct1InterfaceClient : public INestedStruct1Interface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NestedStruct1InterfaceClient>
{
protected:
    explicit NestedStruct1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<NestedStruct1InterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~NestedStruct1InterfaceClient() override;
    void init();
    const NestedStruct1& getProp1() const override;
    void setProp1(const NestedStruct1& prop1) override;
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
    INestedStruct1InterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type NestedStruct1
    NestedStruct1 _to_Prop1(const std::string& args);
    /// @brief sets the value for the property Prop1 coming from the service
    void setProp1Local(const NestedStruct1& prop1);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1
    void onSig1(const std::string& args) const;
    /** Local storage for properties values. */
    NestedStruct1InterfaceData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for NestedStruct1Interface */
    std::unique_ptr<INestedStruct1InterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace Testbed2
} // namespace Test
