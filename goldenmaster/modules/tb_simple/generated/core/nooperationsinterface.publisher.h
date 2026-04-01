#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/nooperationsinterface.api.h"
#include "tb_simple/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbSimple {

/**
 * The implementation of a NoOperationsInterfacePublisher.
 * Use this class to store clients of the NoOperationsInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 * @warning Subscribers are stored by reference. The caller MUST ensure that
 *          subscriber objects outlive their subscription. Destroying a subscriber
 *          without calling unsubscribeFromAllChanges() first causes undefined behavior.
 * @warning Subscriber callbacks are invoked outside any lock. Subscriber
 *          implementations must be thread-safe.
 */
class TEST_TB_SIMPLE_EXPORT NoOperationsInterfacePublisher : public INoOperationsInterfacePublisher
{
public:
    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(INoOperationsInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(INoOperationsInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToPropBoolChanged
    */
    uint64_t subscribeToPropBoolChanged(NoOperationsInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(uint64_t handleId) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToPropIntChanged
    */
    uint64_t subscribeToPropIntChanged(NoOperationsInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(uint64_t handleId) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToSigVoid
    */
    uint64_t subscribeToSigVoid(NoOperationsInterfaceSigVoidSignalCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::unsubscribeFromSigVoid
    */
    void unsubscribeFromSigVoid(uint64_t handleId) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToSigBool
    */
    uint64_t subscribeToSigBool(NoOperationsInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(uint64_t handleId) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(bool propBool) const override;
    /**
    * Implementation of INoOperationsInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
    /**
    * Implementation of INoOperationsInterfacePublisher::publishSigVoid
    */
    void publishSigVoid() const override;
    /**
    * Implementation of INoOperationsInterfacePublisher::publishSigBool
    */
    void publishSigBool(bool paramBool) const override;
private:
    // Subscribers informed about any property change or signal emitted in NoOperationsInterface
    std::vector<std::reference_wrapper<INoOperationsInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<bool> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<int> PropIntPublisher;
    ApiGear::Utilities::SinglePub<> SigVoidPublisher;
    ApiGear::Utilities::SinglePub<bool> SigBoolPublisher;
};

} // namespace TbSimple
} // namespace Test
