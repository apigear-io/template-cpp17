#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/simpleinterface.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace Test {
namespace TbSimple {
namespace MQTT {
class TEST_TB_SIMPLE_EXPORT SimpleInterfaceClient : public ISimpleInterface
{
public:
    explicit SimpleInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~SimpleInterfaceClient() override;
    bool getPropBool() const override;
    void setPropBool(bool propBool) override;
    int getPropInt() const override;
    void setPropInt(int propInt) override;
    int32_t getPropInt32() const override;
    void setPropInt32(int32_t propInt32) override;
    int64_t getPropInt64() const override;
    void setPropInt64(int64_t propInt64) override;
    float getPropFloat() const override;
    void setPropFloat(float propFloat) override;
    float getPropFloat32() const override;
    void setPropFloat32(float propFloat32) override;
    double getPropFloat64() const override;
    void setPropFloat64(double propFloat64) override;
    const std::string& getPropString() const override;
    void setPropString(const std::string& propString) override;
    void funcNoReturnValue(bool paramBool) override;
    std::future<void> funcNoReturnValueAsync(bool paramBool) override;
    bool funcBool(bool paramBool) override;
    std::future<bool> funcBoolAsync(bool paramBool) override;
    int funcInt(int paramInt) override;
    std::future<int> funcIntAsync(int paramInt) override;
    int32_t funcInt32(int32_t paramInt32) override;
    std::future<int32_t> funcInt32Async(int32_t paramInt32) override;
    int64_t funcInt64(int64_t paramInt64) override;
    std::future<int64_t> funcInt64Async(int64_t paramInt64) override;
    float funcFloat(float paramFloat) override;
    std::future<float> funcFloatAsync(float paramFloat) override;
    float funcFloat32(float paramFloat32) override;
    std::future<float> funcFloat32Async(float paramFloat32) override;
    double funcFloat64(double paramFloat) override;
    std::future<double> funcFloat64Async(double paramFloat) override;
    std::string funcString(const std::string& paramString) override;
    std::future<std::string> funcStringAsync(const std::string& paramString) override;
    ISimpleInterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property PropBool coming from the service
    /// @param args contains the param of the type bool
    void setPropBoolLocal(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    /// @param args contains the param of the type int
    void setPropIntLocal(const std::string& args);
    /// @brief sets the value for the property PropInt32 coming from the service
    /// @param args contains the param of the type int32_t
    void setPropInt32Local(const std::string& args);
    /// @brief sets the value for the property PropInt64 coming from the service
    /// @param args contains the param of the type int64_t
    void setPropInt64Local(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    /// @param args contains the param of the type float
    void setPropFloatLocal(const std::string& args);
    /// @brief sets the value for the property PropFloat32 coming from the service
    /// @param args contains the param of the type float
    void setPropFloat32Local(const std::string& args);
    /// @brief sets the value for the property PropFloat64 coming from the service
    /// @param args contains the param of the type double
    void setPropFloat64Local(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    /// @param args contains the param of the type std::string
    void setPropStringLocal(const std::string& args);
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) bool paramBool
    void onSigBool(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt coming from the service
    /// @param args contains the param(s) of the type(s) int paramInt
    void onSigInt(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt32 coming from the service
    /// @param args contains the param(s) of the type(s) int32_t paramInt32
    void onSigInt32(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt64 coming from the service
    /// @param args contains the param(s) of the type(s) int64_t paramInt64
    void onSigInt64(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat coming from the service
    /// @param args contains the param(s) of the type(s) float paramFloat
    void onSigFloat(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat32 coming from the service
    /// @param args contains the param(s) of the type(s) float paramFloat32
    void onSigFloat32(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat64 coming from the service
    /// @param args contains the param(s) of the type(s) double paramFloat64
    void onSigFloat64(const std::string& args) const;
    /// @brief publishes the value for the signal SigString coming from the service
    /// @param args contains the param(s) of the type(s) const std::string& paramString
    void onSigString(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    SimpleInterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for SimpleInterface */
    std::unique_ptr<ISimpleInterfacePublisher> m_publisher;

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
} // namespace TbSimple
} // namespace Test
