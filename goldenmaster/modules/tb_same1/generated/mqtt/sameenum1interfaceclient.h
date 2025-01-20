#pragma once

#include <future>
#include "tb_same1/generated/api/common.h"
#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/core/sameenum1interface.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace Test {
namespace TbSame1 {
namespace MQTT {
class TEST_TB_SAME1_EXPORT SameEnum1InterfaceClient : public ISameEnum1Interface
{
public:
    explicit SameEnum1InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~SameEnum1InterfaceClient() override;
    Enum1Enum getProp1() const override;
    void setProp1(Enum1Enum prop1) override;
    Enum1Enum func1(Enum1Enum param1) override;
    std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) override;
    ISameEnum1InterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type Enum1Enum
    void setProp1Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) Enum1Enum param1
    void onSig1(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    SameEnum1InterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for SameEnum1Interface */
    std::unique_ptr<ISameEnum1InterfacePublisher> m_publisher;

    /**
     * @brief register a response handler for an operation invocation
     * 
     * @param handler function to be called on return
     * @return int unique id of the call
     */
    int registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler);
    std::mutex m_responseHandlerMutex;
    std::map<int, ApiGear::MQTT::InvokeReplyFunc> m_responseHandlerMap;

    /// @brief has all the topics of this client and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
    // id for connection status registration
    int m_connectionStatusRegistrationID;
};
} // namespace MQTT
} // namespace TbSame1
} // namespace Test
