#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/simpleinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT SimpleInterfaceClient : public ISimpleInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SimpleInterfaceClient>
{
protected:
    explicit SimpleInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<SimpleInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~SimpleInterfaceClient() override;
    void init();
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
    std::future<void> funcNoReturnValueAsync(bool paramBool, std::function<void(void)> callback = nullptr) override;
    bool funcBool(bool paramBool) override;
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;
    int funcInt(int paramInt) override;
    std::future<int> funcIntAsync(int paramInt, std::function<void(int)> callback = nullptr) override;
    int32_t funcInt32(int32_t paramInt32) override;
    std::future<int32_t> funcInt32Async(int32_t paramInt32, std::function<void(int32_t)> callback = nullptr) override;
    int64_t funcInt64(int64_t paramInt64) override;
    std::future<int64_t> funcInt64Async(int64_t paramInt64, std::function<void(int64_t)> callback = nullptr) override;
    float funcFloat(float paramFloat) override;
    std::future<float> funcFloatAsync(float paramFloat, std::function<void(float)> callback = nullptr) override;
    float funcFloat32(float paramFloat32) override;
    std::future<float> funcFloat32Async(float paramFloat32, std::function<void(float)> callback = nullptr) override;
    double funcFloat64(double paramFloat) override;
    std::future<double> funcFloat64Async(double paramFloat, std::function<void(double)> callback = nullptr) override;
    std::string funcString(const std::string& paramString) override;
    std::future<std::string> funcStringAsync(const std::string& paramString, std::function<void(std::string)> callback = nullptr) override;
    ISimpleInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type bool
    bool _to_PropBool(const std::string& args);
    /// @brief sets the value for the property PropBool coming from the service
    void setPropBoolLocal(bool propBool);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type int
    int _to_PropInt(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    void setPropIntLocal(int propInt);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type int32_t
    int32_t _to_PropInt32(const std::string& args);
    /// @brief sets the value for the property PropInt32 coming from the service
    void setPropInt32Local(int32_t propInt32);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type int64_t
    int64_t _to_PropInt64(const std::string& args);
    /// @brief sets the value for the property PropInt64 coming from the service
    void setPropInt64Local(int64_t propInt64);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type float
    float _to_PropFloat(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    void setPropFloatLocal(float propFloat);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type float
    float _to_PropFloat32(const std::string& args);
    /// @brief sets the value for the property PropFloat32 coming from the service
    void setPropFloat32Local(float propFloat32);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type double
    double _to_PropFloat64(const std::string& args);
    /// @brief sets the value for the property PropFloat64 coming from the service
    void setPropFloat64Local(double propFloat64);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::string
    std::string _to_PropString(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    void setPropStringLocal(const std::string& propString);
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
    /** Local storage for properties values. */
    SimpleInterfaceData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for SimpleInterface */
    std::unique_ptr<ISimpleInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
