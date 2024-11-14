#pragma once

#include "tb_same2/generated/api/common.h"
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/core/samestruct1interface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSame2 {
namespace Nats {
class TEST_TB_SAME2_EXPORT SameStruct1InterfaceClient : public ISameStruct1Interface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameStruct1InterfaceClient>
{
protected:
    explicit SameStruct1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<SameStruct1InterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~SameStruct1InterfaceClient() override;
    void init();
    const Struct1& getProp1() const override;
    void setProp1(const Struct1& prop1) override;
    Struct1 func1(const Struct1& param1) override;
    std::future<Struct1> func1Async(const Struct1& param1) override;
    ISameStruct1InterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type Struct1
    void setProp1Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) const Struct1& param1
    void onSig1(const std::string& args) const;
    /** Local storage for properties values. */
    SameStruct1InterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for SameStruct1Interface */
    std::unique_ptr<ISameStruct1InterfacePublisher> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace TbSame2
} // namespace Test
