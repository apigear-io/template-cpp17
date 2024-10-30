#pragma once

#include <future>
#include "tb_same2/generated/api/common.h"
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/core/samestruct2interface.data.h"
#include "apigear/nats/natsclient.h"

namespace Test {
namespace TbSame2 {
namespace Nats {
class TEST_TB_SAME2_EXPORT SameStruct2InterfaceClient : public ISameStruct2Interface
{
public:
    explicit SameStruct2InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~SameStruct2InterfaceClient() override;
    const Struct2& getProp1() const override;
    void setProp1(const Struct2& prop1) override;
    const Struct2& getProp2() const override;
    void setProp2(const Struct2& prop2) override;
    Struct1 func1(const Struct1& param1) override;
    std::future<Struct1> func1Async(const Struct1& param1) override;
    Struct1 func2(const Struct1& param1, const Struct2& param2) override;
    std::future<Struct1> func2Async(const Struct1& param1, const Struct2& param2) override;
    ISameStruct2InterfacePublisher& _getPublisher() const override;
private:
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type Struct2
    void setProp1Local(const std::string& args);
    /// @brief sets the value for the property Prop2 coming from the service
    /// @param args contains the param of the type Struct2
    void setProp2Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) const Struct1& param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) const Struct1& param1, const Struct2& param2
    void onSig2(const std::string& args) const;
    /** Local storage for properties values. */
    SameStruct2InterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;

    /** The publisher for SameStruct2Interface */
    std::unique_ptr<ISameStruct2InterfacePublisher> m_publisher;

};
} // namespace Nats
} // namespace TbSame2
} // namespace Test