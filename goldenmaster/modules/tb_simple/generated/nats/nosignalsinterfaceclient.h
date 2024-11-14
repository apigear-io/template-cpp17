#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/nosignalsinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT NoSignalsInterfaceClient : public INoSignalsInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NoSignalsInterfaceClient>
{
protected:
    explicit NoSignalsInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<NoSignalsInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~NoSignalsInterfaceClient() override;
    void init();
    bool getPropBool() const override;
    void setPropBool(bool propBool) override;
    int getPropInt() const override;
    void setPropInt(int propInt) override;
    void funcVoid() override;
    std::future<void> funcVoidAsync() override;
    bool funcBool(bool paramBool) override;
    std::future<bool> funcBoolAsync(bool paramBool) override;
    INoSignalsInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    /// @brief sets the value for the property PropBool coming from the service
    /// @param args contains the param of the type bool
    void setPropBoolLocal(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    /// @param args contains the param of the type int
    void setPropIntLocal(const std::string& args);
    /** Local storage for properties values. */
    NoSignalsInterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for NoSignalsInterface */
    std::unique_ptr<INoSignalsInterfacePublisher> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
