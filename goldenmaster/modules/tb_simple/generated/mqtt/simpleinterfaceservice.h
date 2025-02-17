#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"

namespace Test {
namespace TbSimple {
namespace MQTT {
class TEST_TB_SIMPLE_EXPORT SimpleInterfaceService : public ISimpleInterfaceSubscriber
{
public:
    explicit SimpleInterfaceService(std::shared_ptr<ISimpleInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~SimpleInterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // ISimpleInterfaceSubscriber interface
    void onSigBool(bool paramBool) override;
    void onSigInt(int paramInt) override;
    void onSigInt32(int32_t paramInt32) override;
    void onSigInt64(int64_t paramInt64) override;
    void onSigFloat(float paramFloat) override;
    void onSigFloat32(float paramFloat32) override;
    void onSigFloat64(double paramFloat64) override;
    void onSigString(const std::string& paramString) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();
    void onInvokeFuncNoReturnValue(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncBool(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt32(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt64(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat32(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat64(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncString(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onPropBoolChanged(bool propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type bool
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(int propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type int
    void onSetPropInt(const std::string& args) const;
    void onPropInt32Changed(int32_t propInt32) override;
    /// @brief requests to set the value for the property PropInt32 coming from the client
    /// @param fields contains the param of the type int32_t
    void onSetPropInt32(const std::string& args) const;
    void onPropInt64Changed(int64_t propInt64) override;
    /// @brief requests to set the value for the property PropInt64 coming from the client
    /// @param fields contains the param of the type int64_t
    void onSetPropInt64(const std::string& args) const;
    void onPropFloatChanged(float propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type float
    void onSetPropFloat(const std::string& args) const;
    void onPropFloat32Changed(float propFloat32) override;
    /// @brief requests to set the value for the property PropFloat32 coming from the client
    /// @param fields contains the param of the type float
    void onSetPropFloat32(const std::string& args) const;
    void onPropFloat64Changed(double propFloat64) override;
    /// @brief requests to set the value for the property PropFloat64 coming from the client
    /// @param fields contains the param of the type double
    void onSetPropFloat64(const std::string& args) const;
    void onPropStringChanged(const std::string& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type std::string
    void onSetPropString(const std::string& args) const;

    std::shared_ptr<ISimpleInterface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusRegistrationID;

    /// @brief has all the topics of this service and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
};
} // namespace MQTT
} // namespace TbSimple
} // namespace Test
