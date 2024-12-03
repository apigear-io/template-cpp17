#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/simplearrayinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT SimpleArrayInterfaceClient : public ISimpleArrayInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SimpleArrayInterfaceClient>
{
protected:
    explicit SimpleArrayInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<SimpleArrayInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~SimpleArrayInterfaceClient() override;
    void init();
    const std::list<bool>& getPropBool() const override;
    void setPropBool(const std::list<bool>& propBool) override;
    const std::list<int>& getPropInt() const override;
    void setPropInt(const std::list<int>& propInt) override;
    const std::list<int32_t>& getPropInt32() const override;
    void setPropInt32(const std::list<int32_t>& propInt32) override;
    const std::list<int64_t>& getPropInt64() const override;
    void setPropInt64(const std::list<int64_t>& propInt64) override;
    const std::list<float>& getPropFloat() const override;
    void setPropFloat(const std::list<float>& propFloat) override;
    const std::list<float>& getPropFloat32() const override;
    void setPropFloat32(const std::list<float>& propFloat32) override;
    const std::list<double>& getPropFloat64() const override;
    void setPropFloat64(const std::list<double>& propFloat64) override;
    const std::list<std::string>& getPropString() const override;
    void setPropString(const std::list<std::string>& propString) override;
    const std::string& getPropReadOnlyString() const override;
    std::list<bool> funcBool(const std::list<bool>& paramBool) override;
    std::future<std::list<bool>> funcBoolAsync(const std::list<bool>& paramBool) override;
    std::list<int> funcInt(const std::list<int>& paramInt) override;
    std::future<std::list<int>> funcIntAsync(const std::list<int>& paramInt) override;
    std::list<int32_t> funcInt32(const std::list<int32_t>& paramInt32) override;
    std::future<std::list<int32_t>> funcInt32Async(const std::list<int32_t>& paramInt32) override;
    std::list<int64_t> funcInt64(const std::list<int64_t>& paramInt64) override;
    std::future<std::list<int64_t>> funcInt64Async(const std::list<int64_t>& paramInt64) override;
    std::list<float> funcFloat(const std::list<float>& paramFloat) override;
    std::future<std::list<float>> funcFloatAsync(const std::list<float>& paramFloat) override;
    std::list<float> funcFloat32(const std::list<float>& paramFloat32) override;
    std::future<std::list<float>> funcFloat32Async(const std::list<float>& paramFloat32) override;
    std::list<double> funcFloat64(const std::list<double>& paramFloat) override;
    std::future<std::list<double>> funcFloat64Async(const std::list<double>& paramFloat) override;
    std::list<std::string> funcString(const std::list<std::string>& paramString) override;
    std::future<std::list<std::string>> funcStringAsync(const std::list<std::string>& paramString) override;
    ISimpleArrayInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<bool>
    std::list<bool> _to_PropBool(const std::string& args);
    /// @brief sets the value for the property PropBool coming from the service
    void setPropBoolLocal(const std::list<bool>& propBool);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<int>
    std::list<int> _to_PropInt(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    void setPropIntLocal(const std::list<int>& propInt);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<int32_t>
    std::list<int32_t> _to_PropInt32(const std::string& args);
    /// @brief sets the value for the property PropInt32 coming from the service
    void setPropInt32Local(const std::list<int32_t>& propInt32);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<int64_t>
    std::list<int64_t> _to_PropInt64(const std::string& args);
    /// @brief sets the value for the property PropInt64 coming from the service
    void setPropInt64Local(const std::list<int64_t>& propInt64);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<float>
    std::list<float> _to_PropFloat(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    void setPropFloatLocal(const std::list<float>& propFloat);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<float>
    std::list<float> _to_PropFloat32(const std::string& args);
    /// @brief sets the value for the property PropFloat32 coming from the service
    void setPropFloat32Local(const std::list<float>& propFloat32);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<double>
    std::list<double> _to_PropFloat64(const std::string& args);
    /// @brief sets the value for the property PropFloat64 coming from the service
    void setPropFloat64Local(const std::list<double>& propFloat64);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<std::string>
    std::list<std::string> _to_PropString(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    void setPropStringLocal(const std::list<std::string>& propString);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::string
    std::string _to_PropReadOnlyString(const std::string& args);
    /// @brief sets the value for the property PropReadOnlyString coming from the service
    void setPropReadOnlyStringLocal(const std::string& propReadOnlyString);
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<bool>& paramBool
    void onSigBool(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<int>& paramInt
    void onSigInt(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt32 coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<int32_t>& paramInt32
    void onSigInt32(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt64 coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<int64_t>& paramInt64
    void onSigInt64(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<float>& paramFloat
    void onSigFloat(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat32 coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<float>& paramFloa32
    void onSigFloat32(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat64 coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<double>& paramFloat64
    void onSigFloat64(const std::string& args) const;
    /// @brief publishes the value for the signal SigString coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<std::string>& paramString
    void onSigString(const std::string& args) const;
    /** Local storage for properties values. */
    SimpleArrayInterfaceData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for SimpleArrayInterface */
    std::unique_ptr<ISimpleArrayInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
