#pragma once

#include "tb_names/generated/api/common.h"
#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/core/names.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbNames {
namespace Nats {
class TEST_TB_NAMES_EXPORT Nam_EsClient : public INamEs, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<Nam_EsClient>
{
protected:
    explicit Nam_EsClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<Nam_EsClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~Nam_EsClient() override;
    void init();
    bool getSwitch() const override;
    void setSwitch(bool Switch) override;
    int getSomeProperty() const override;
    void setSomeProperty(int SOME_PROPERTY) override;
    int getSomePoperty2() const override;
    void setSomePoperty2(int Some_Poperty2) override;
    Enum_With_Under_scoresEnum getEnumProperty() const override;
    void setEnumProperty(Enum_With_Under_scoresEnum enum_property) override;
    void sOME_FUNCTION(bool SOME_PARAM) override;
    std::future<void> sOME_FUNCTIONAsync(bool SOME_PARAM) override;
    void some_Function2(bool Some_Param) override;
    std::future<void> some_Function2Async(bool Some_Param) override;
    INamEsPublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    /// @brief sets the value for the property Switch coming from the service
    /// @param args contains the param of the type bool
    void setSwitchLocal(const std::string& args);
    /// @brief sets the value for the property SomeProperty coming from the service
    /// @param args contains the param of the type int
    void setSomePropertyLocal(const std::string& args);
    /// @brief sets the value for the property SomePoperty2 coming from the service
    /// @param args contains the param of the type int
    void setSomePoperty2Local(const std::string& args);
    /// @brief sets the value for the property EnumProperty coming from the service
    /// @param args contains the param of the type Enum_With_Under_scoresEnum
    void setEnumPropertyLocal(const std::string& args);
    /// @brief publishes the value for the signal SomeSignal coming from the service
    /// @param args contains the param(s) of the type(s) bool SOME_PARAM
    void onSomeSignal(const std::string& args) const;
    /// @brief publishes the value for the signal SomeSignal2 coming from the service
    /// @param args contains the param(s) of the type(s) bool Some_Param
    void onSomeSignal2(const std::string& args) const;
    /** Local storage for properties values. */
    NamEsData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for NamEs */
    std::unique_ptr<INamEsPublisher> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace TbNames
} // namespace Test
