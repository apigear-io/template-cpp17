#pragma once

#include <future>
#include "tb_names/generated/api/common.h"
#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/core/names.data.h"
#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace TbNames {
namespace MQTT {
class TEST_TB_NAMES_EXPORT Nam_EsClient : public INamEs, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit Nam_EsClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~Nam_EsClient() override;
    bool getSwitch() const override;
    void setSwitch(bool Switch) override;
    int getSomeProperty() const override;
    void setSomeProperty(int SOME_PROPERTY) override;
    int getSomePoperty2() const override;
    void setSomePoperty2(int Some_Poperty2) override;
    void sOME_FUNCTION(bool SOME_PARAM) override;
    std::future<void> sOME_FUNCTIONAsync(bool SOME_PARAM) override;
    void some_Function2(bool Some_Param) override;
    std::future<void> some_Function2Async(bool Some_Param) override;
    INamEsPublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property Switch coming from the service
    /// @param args contains the param of the type bool
    void setSwitchLocal(const std::string& args);
    /// @brief sets the value for the property SomeProperty coming from the service
    /// @param args contains the param of the type int
    void setSomePropertyLocal(const std::string& args);
    /// @brief sets the value for the property SomePoperty2 coming from the service
    /// @param args contains the param of the type int
    void setSomePoperty2Local(const std::string& args);
    /// @brief publishes the value for the signal SomeSignal coming from the service
    /// @param args contains the param(s) of the type(s) bool SOME_PARAM
    void onSomeSignal(const std::string& args) const;
    /// @brief publishes the value for the signal SomeSignal2 coming from the service
    /// @param args contains the param(s) of the type(s) bool Some_Param
    void onSomeSignal2(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    NamEsData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for NamEs */
    std::unique_ptr<INamEsPublisher> m_publisher;

    /**
     * @brief register a response handler for an operation invocation
     * 
     * @param handler function to be called on return
     * @return int unique id of the call
     */
    int registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler);
    std::mutex m_responseHandlerMutex;
    std::map<int, ApiGear::MQTT::InvokeReplyFunc> m_responseHandlerMap;
};
} // namespace MQTT
} // namespace TbNames
} // namespace Test
