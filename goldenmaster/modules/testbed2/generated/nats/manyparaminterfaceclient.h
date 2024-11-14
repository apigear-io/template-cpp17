#pragma once

#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/manyparaminterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace Testbed2 {
namespace Nats {
class TEST_TESTBED2_EXPORT ManyParamInterfaceClient : public IManyParamInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<ManyParamInterfaceClient>
{
protected:
    explicit ManyParamInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<ManyParamInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~ManyParamInterfaceClient() override;
    void init();
    int getProp1() const override;
    void setProp1(int prop1) override;
    int getProp2() const override;
    void setProp2(int prop2) override;
    int getProp3() const override;
    void setProp3(int prop3) override;
    int getProp4() const override;
    void setProp4(int prop4) override;
    int func1(int param1) override;
    std::future<int> func1Async(int param1) override;
    int func2(int param1, int param2) override;
    std::future<int> func2Async(int param1, int param2) override;
    int func3(int param1, int param2, int param3) override;
    std::future<int> func3Async(int param1, int param2, int param3) override;
    int func4(int param1, int param2, int param3, int param4) override;
    std::future<int> func4Async(int param1, int param2, int param3, int param4) override;
    IManyParamInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type int
    void setProp1Local(const std::string& args);
    /// @brief sets the value for the property Prop2 coming from the service
    /// @param args contains the param of the type int
    void setProp2Local(const std::string& args);
    /// @brief sets the value for the property Prop3 coming from the service
    /// @param args contains the param of the type int
    void setProp3Local(const std::string& args);
    /// @brief sets the value for the property Prop4 coming from the service
    /// @param args contains the param of the type int
    void setProp4Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) int param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) int param1, int param2
    void onSig2(const std::string& args) const;
    /// @brief publishes the value for the signal Sig3 coming from the service
    /// @param args contains the param(s) of the type(s) int param1, int param2, int param3
    void onSig3(const std::string& args) const;
    /// @brief publishes the value for the signal Sig4 coming from the service
    /// @param args contains the param(s) of the type(s) int param1, int param2, int param3, int param4
    void onSig4(const std::string& args) const;
    /** Local storage for properties values. */
    ManyParamInterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for ManyParamInterface */
    std::unique_ptr<IManyParamInterfacePublisher> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace Testbed2
} // namespace Test
