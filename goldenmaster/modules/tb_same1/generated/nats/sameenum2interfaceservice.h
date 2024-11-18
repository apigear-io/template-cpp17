#pragma once

#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSame1 {
namespace Nats {
class TEST_TB_SAME1_EXPORT SameEnum2InterfaceService : public ISameEnum2InterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameEnum2InterfaceService>
{
protected:
    explicit SameEnum2InterfaceService(std::shared_ptr<ISameEnum2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<SameEnum2InterfaceService>create(std::shared_ptr<ISameEnum2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~SameEnum2InterfaceService() override;
    void init();

    // ISameEnum2InterfaceSubscriber interface
    void onSig1(Enum1Enum param1) override;
    void onSig2(Enum1Enum param1, Enum2Enum param2) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    void onProp1Changed(Enum1Enum prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Enum1Enum
    void onSetProp1(const std::string& args) const;
    void onProp2Changed(Enum2Enum prop2) override;
    /// @brief requests to set the value for the property Prop2 coming from the client
    /// @param fields contains the param of the type Enum2Enum
    void onSetProp2(const std::string& args) const;
    std::string onInvokeFunc1(const std::string& args) const;
    std::string onInvokeFunc2(const std::string& args) const;

    std::shared_ptr<ISameEnum2Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSame1
} // namespace Test
