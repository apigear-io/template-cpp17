#pragma once

#include "counter/generated/api/counter.h"
#include "counter/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace Counter {
namespace Nats {
class TEST_COUNTER_EXPORT CounterService : public ICounterSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<CounterService>
{
protected:
    explicit CounterService(std::shared_ptr<ICounter> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<CounterService>create(std::shared_ptr<ICounter> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~CounterService() override;
    void init();

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    void onVectorChanged(const Test::CustomTypes::Vector3D& vector) override;
    /// @brief requests to set the value for the property Vector coming from the client
    /// @param fields contains the param of the type Test::CustomTypes::Vector3D
    void onSetVector(const std::string& args) const;
    void onExternVectorChanged(const Eigen::Vector3f& extern_vector) override;
    /// @brief requests to set the value for the property ExternVector coming from the client
    /// @param fields contains the param of the type Eigen::Vector3f
    void onSetExternVector(const std::string& args) const;
    std::string onInvokeIncrement(const std::string& args) const;
    std::string onInvokeDecrement(const std::string& args) const;

    std::shared_ptr<ICounter> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace Counter
} // namespace Test
