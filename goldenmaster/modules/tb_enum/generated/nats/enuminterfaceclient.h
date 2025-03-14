#pragma once

#include "tb_enum/generated/api/common.h"
#include "tb_enum/generated/api/tb_enum.h"
#include "tb_enum/generated/core/enuminterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbEnum {
namespace Nats {
class TEST_TB_ENUM_EXPORT EnumInterfaceClient : public IEnumInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<EnumInterfaceClient>
{
protected:
    explicit EnumInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<EnumInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~EnumInterfaceClient() override;
    void init();
    Enum0Enum getProp0() const override;
    void setProp0(Enum0Enum prop0) override;
    Enum1Enum getProp1() const override;
    void setProp1(Enum1Enum prop1) override;
    Enum2Enum getProp2() const override;
    void setProp2(Enum2Enum prop2) override;
    Enum3Enum getProp3() const override;
    void setProp3(Enum3Enum prop3) override;
    Enum0Enum func0(Enum0Enum param0) override;
    std::future<Enum0Enum> func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback = nullptr) override;
    Enum1Enum func1(Enum1Enum param1) override;
    std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) override;
    Enum2Enum func2(Enum2Enum param2) override;
    std::future<Enum2Enum> func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback = nullptr) override;
    Enum3Enum func3(Enum3Enum param3) override;
    std::future<Enum3Enum> func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback = nullptr) override;
    IEnumInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type Enum0Enum
    Enum0Enum _to_Prop0(const std::string& args);
    /// @brief sets the value for the property Prop0 coming from the service
    void setProp0Local(Enum0Enum prop0);
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
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type Enum3Enum
    Enum3Enum _to_Prop3(const std::string& args);
    /// @brief sets the value for the property Prop3 coming from the service
    void setProp3Local(Enum3Enum prop3);
    /// @brief publishes the value for the signal Sig0 coming from the service
    /// @param args contains the param(s) of the type(s) Enum0Enum param0
    void onSig0(const std::string& args) const;
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) Enum2Enum param2
    void onSig2(const std::string& args) const;
    /// @brief publishes the value for the signal Sig3 coming from the service
    /// @param args contains the param(s) of the type(s) Enum3Enum param3
    void onSig3(const std::string& args) const;
    /** Local storage for properties values. */
    EnumInterfaceData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for EnumInterface */
    std::unique_ptr<IEnumInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbEnum
} // namespace Test
