#pragma once

#include <future>
#include "tb_same1/generated/api/common.h"
#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/core/sameenum1interface.data.h"
#include "apigear/nats/natsclient.h"

namespace Test {
namespace TbSame1 {
namespace Nats {
class TEST_TB_SAME1_EXPORT SameEnum1InterfaceClient : public ISameEnum1Interface
{
public:
    explicit SameEnum1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~SameEnum1InterfaceClient() override;
    Enum1Enum getProp1() const override;
    void setProp1(Enum1Enum prop1) override;
    Enum1Enum func1(Enum1Enum param1) override;
    std::future<Enum1Enum> func1Async(Enum1Enum param1) override;
    ISameEnum1InterfacePublisher& _getPublisher() const override;
private:
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type Enum1Enum
    void setProp1Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1
    void onSig1(const std::string& args) const;
    /** Local storage for properties values. */
    SameEnum1InterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;

    /** The publisher for SameEnum1Interface */
    std::unique_ptr<ISameEnum1InterfacePublisher> m_publisher;

};
} // namespace Nats
} // namespace TbSame1
} // namespace Test
