#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"

namespace Test {
namespace TbSimple {
namespace MQTT {
class TEST_TB_SIMPLE_EXPORT SimpleArrayInterfaceService : public ISimpleArrayInterfaceSubscriber
{
public:
    explicit SimpleArrayInterfaceService(std::shared_ptr<ISimpleArrayInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~SimpleArrayInterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // ISimpleArrayInterfaceSubscriber interface
    void onSigBool(const std::list<bool>& paramBool) override;
    void onSigInt(const std::list<int>& paramInt) override;
    void onSigInt32(const std::list<int32_t>& paramInt32) override;
    void onSigInt64(const std::list<int64_t>& paramInt64) override;
    void onSigFloat(const std::list<float>& paramFloat) override;
    void onSigFloat32(const std::list<float>& paramFloa32) override;
    void onSigFloat64(const std::list<double>& paramFloat64) override;
    void onSigString(const std::list<std::string>& paramString) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();
    void onInvokeFuncBool(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt32(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt64(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat32(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat64(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncString(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onPropBoolChanged(const std::list<bool>& propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type std::list<bool>
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(const std::list<int>& propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type std::list<int>
    void onSetPropInt(const std::string& args) const;
    void onPropInt32Changed(const std::list<int32_t>& propInt32) override;
    /// @brief requests to set the value for the property PropInt32 coming from the client
    /// @param fields contains the param of the type std::list<int32_t>
    void onSetPropInt32(const std::string& args) const;
    void onPropInt64Changed(const std::list<int64_t>& propInt64) override;
    /// @brief requests to set the value for the property PropInt64 coming from the client
    /// @param fields contains the param of the type std::list<int64_t>
    void onSetPropInt64(const std::string& args) const;
    void onPropFloatChanged(const std::list<float>& propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type std::list<float>
    void onSetPropFloat(const std::string& args) const;
    void onPropFloat32Changed(const std::list<float>& propFloat32) override;
    /// @brief requests to set the value for the property PropFloat32 coming from the client
    /// @param fields contains the param of the type std::list<float>
    void onSetPropFloat32(const std::string& args) const;
    void onPropFloat64Changed(const std::list<double>& propFloat64) override;
    /// @brief requests to set the value for the property PropFloat64 coming from the client
    /// @param fields contains the param of the type std::list<double>
    void onSetPropFloat64(const std::string& args) const;
    void onPropStringChanged(const std::list<std::string>& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type std::list<std::string>
    void onSetPropString(const std::string& args) const;
    void onPropReadOnlyStringChanged(const std::string& propReadOnlyString) override;

    std::shared_ptr<ISimpleArrayInterface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusRegistrationID;

    /// @brief has all the topics of this service and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
};
} // namespace MQTT
} // namespace TbSimple
} // namespace Test
