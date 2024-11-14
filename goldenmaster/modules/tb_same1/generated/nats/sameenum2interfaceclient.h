#pragma once

#include "tb_same1/generated/api/common.h"
#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/core/sameenum2interface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSame1 {
namespace Nats {
class TEST_TB_SAME1_EXPORT SameEnum2InterfaceClient : public ISameEnum2Interface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameEnum2InterfaceClient>
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
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type Enum1Enum
    void setProp1Local(const std::string& args);
    /// @brief sets the value for the property Prop2 coming from the service
    /// @param args contains the param of the type Enum2Enum
    void setProp2Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1, Enum2Enum param2
    void onSig2(const std::string& args) const;
    /** Local storage for properties values. */
    SameEnum2InterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for SameEnum2Interface */
    std::unique_ptr<ISameEnum2InterfacePublisher> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace TbSame1
} // namespace Test
