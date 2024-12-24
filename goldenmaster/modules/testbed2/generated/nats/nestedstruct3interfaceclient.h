#pragma once

#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/nestedstruct3interface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace Testbed2 {
namespace Nats {
class TEST_TESTBED2_EXPORT NestedStruct3InterfaceClient : public INestedStruct3Interface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NestedStruct3InterfaceClient>
{
protected:
    explicit NestedStruct3InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<NestedStruct3InterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~NestedStruct3InterfaceClient() override;
    void init();
    const NestedStruct1& getProp1() const override;
    void setProp1(const NestedStruct1& prop1) override;
    const NestedStruct2& getProp2() const override;
    void setProp2(const NestedStruct2& prop2) override;
    const NestedStruct3& getProp3() const override;
    void setProp3(const NestedStruct3& prop3) override;
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1) override;
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2) override;
    NestedStruct1 func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    std::future<NestedStruct1> func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    INestedStruct3InterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type NestedStruct1
    NestedStruct1 _to_Prop1(const std::string& args);
    /// @brief sets the value for the property Prop1 coming from the service
    void setProp1Local(const NestedStruct1& prop1);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type NestedStruct2
    NestedStruct2 _to_Prop2(const std::string& args);
    /// @brief sets the value for the property Prop2 coming from the service
    void setProp2Local(const NestedStruct2& prop2);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type NestedStruct3
    NestedStruct3 _to_Prop3(const std::string& args);
    /// @brief sets the value for the property Prop3 coming from the service
    void setProp3Local(const NestedStruct3& prop3);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1, const NestedStruct2& param2
    void onSig2(const std::string& args) const;
    /// @brief publishes the value for the signal Sig3 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3
    void onSig3(const std::string& args) const;
    /** Local storage for properties values. */
    NestedStruct3InterfaceData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for NestedStruct3Interface */
    std::unique_ptr<INestedStruct3InterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace Testbed2
} // namespace Test
