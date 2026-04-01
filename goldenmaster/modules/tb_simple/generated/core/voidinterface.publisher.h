#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/voidinterface.api.h"
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
 * The implementation of a VoidInterfacePublisher.
 * Use this class to store clients of the VoidInterface and inform them about the change
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
class TEST_TB_SIMPLE_EXPORT VoidInterfacePublisher : public IVoidInterfacePublisher
{
public:
    /**
    * Implementation of IVoidInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IVoidInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IVoidInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IVoidInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of IVoidInterfacePublisher::subscribeToSigVoid
    */
    uint64_t subscribeToSigVoid(VoidInterfaceSigVoidSignalCb callback) override;
    /**
    * Implementation of IVoidInterfacePublisher::unsubscribeFromSigVoid
    */
    void unsubscribeFromSigVoid(uint64_t handleId) override;

    /**
    * Implementation of IVoidInterfacePublisher::publishSigVoid
    */
    void publishSigVoid() const override;
private:
    // Subscribers informed about any property change or signal emitted in VoidInterface
    std::vector<std::reference_wrapper<IVoidInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<> SigVoidPublisher;
};

} // namespace TbSimple
} // namespace Test
