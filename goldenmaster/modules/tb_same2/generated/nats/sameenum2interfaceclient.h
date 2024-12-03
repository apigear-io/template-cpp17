#pragma once

#include "tb_same2/generated/api/common.h"
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/core/sameenum2interface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSame2 {
namespace Nats {
class TEST_TB_SAME2_EXPORT SameEnum2InterfaceClient : public ISameEnum2Interface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameEnum2InterfaceClient>
{
protected:
    explicit SameEnum2InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<SameEnum2InterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~SameEnum2InterfaceClient() override;
    void init();
    Enum1Enum getProp1() const override;
    void setProp1(Enum1Enum prop1) override;
    Enum2Enum getProp2() const override;
    void setProp2(Enum2Enum prop2) override;
    Enum1Enum func1(Enum1Enum param1) override;
    std::future<Enum1Enum> func1Async(Enum1Enum param1) override;
    Enum1Enum func2(Enum1Enum param1, Enum2Enum param2) override;
    std::future<Enum1Enum> func2Async(Enum1Enum param1, Enum2Enum param2) override;
    ISameEnum2InterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type Enum1Enum
    Enum1Enum _to_Prop1(const std::string& args);
    /// @brief sets the value for the property Prop1 coming from the service
    void setProp1Local(Enum1Enum prop1);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type Enum2Enum
    Enum2Enum _to_Prop2(const std::string& args);
    /// @brief sets the value for the property Prop2 coming from the service
    void setProp2Local(Enum2Enum prop2);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1, Enum2Enum param2
    void onSig2(const std::string& args) const;
    /** Local storage for properties values. */
    SameEnum2InterfaceData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for SameEnum2Interface */
    std::unique_ptr<ISameEnum2InterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbSame2
} // namespace Test
