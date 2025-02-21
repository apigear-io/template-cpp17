#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/emptyinterface.data.h"
#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace TbSimple {
namespace MQTT {
class TEST_TB_SIMPLE_EXPORT EmptyInterfaceClient : public IEmptyInterface, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit EmptyInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~EmptyInterfaceClient() override;
    IEmptyInterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&);

    bool m_isReady;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for EmptyInterface */
    std::unique_ptr<IEmptyInterfacePublisher> m_publisher;

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
} // namespace TbSimple
} // namespace Test
