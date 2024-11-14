#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/nooperationsinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT NoOperationsInterfaceClient : public INoOperationsInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NoOperationsInterfaceClient>
{
protected:
    explicit NoOperationsInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<NoOperationsInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~NoOperationsInterfaceClient() override;
    void init();
    bool getPropBool() const override;
    void setPropBool(bool propBool) override;
    int getPropInt() const override;
    void setPropInt(int propInt) override;
    INoOperationsInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    /// @brief sets the value for the property PropBool coming from the service
    /// @param args contains the param of the type bool
    void setPropBoolLocal(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    /// @param args contains the param of the type int
    void setPropIntLocal(const std::string& args);
    /// @brief publishes the value for the signal SigVoid coming from the service
    /// @param args contains the param(s) of the type(s) 
    void onSigVoid(const std::string& args) const;
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) bool paramBool
    void onSigBool(const std::string& args) const;
    /** Local storage for properties values. */
    NoOperationsInterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for NoOperationsInterface */
    std::unique_ptr<INoOperationsInterfacePublisher> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
