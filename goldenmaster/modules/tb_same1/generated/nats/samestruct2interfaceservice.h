#pragma once

#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSame1 {
namespace Nats {
class TEST_TB_SAME1_EXPORT SameStruct2InterfaceService : public ISameStruct2InterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameStruct2InterfaceService>
{
protected:
    explicit SameStruct2InterfaceService(std::shared_ptr<ISameStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<SameStruct2InterfaceService>create(std::shared_ptr<ISameStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~SameStruct2InterfaceService() override;
    void init();

    // ISameStruct2InterfaceSubscriber interface
    void onSig1(const Struct1& param1) override;
    void onSig2(const Struct1& param1, const Struct2& param2) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onProp1Changed(const Struct2& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Struct2
    void onSetProp1(const std::string& args) const;
    void onProp2Changed(const Struct2& prop2) override;
    /// @brief requests to set the value for the property Prop2 coming from the client
    /// @param fields contains the param of the type Struct2
    void onSetProp2(const std::string& args) const;
    std::string onInvokeFunc1(const std::string& args) const;
    std::string onInvokeFunc2(const std::string& args) const;

    std::shared_ptr<ISameStruct2Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace TbSame1
} // namespace Test
