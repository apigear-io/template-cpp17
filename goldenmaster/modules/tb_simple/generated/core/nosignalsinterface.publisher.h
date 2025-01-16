#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/nosignalsinterface.api.h"
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
 * The implementation of a NoSignalsInterfacePublisher.
 * Use this class to store clients of the NoSignalsInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TB_SIMPLE_EXPORT NoSignalsInterfacePublisher : public INoSignalsInterfacePublisher
{
public:
    /**
    * Implementation of INoSignalsInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(INoSignalsInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of INoSignalsInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(INoSignalsInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of INoSignalsInterfacePublisher::subscribeToPropBoolChanged
    */
    long subscribeToPropBoolChanged(NoSignalsInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of INoSignalsInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(long handleId) override;

    /**
    * Implementation of INoSignalsInterfacePublisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(NoSignalsInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of INoSignalsInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of INoSignalsInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(bool propBool) const override;
    /**
    * Implementation of INoSignalsInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
private:
    // Subscribers informed about any property change or signal emitted in NoSignalsInterface
    std::vector<std::reference_wrapper<INoSignalsInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<bool> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<int> PropIntPublisher;
};

} // namespace TbSimple
} // namespace Test
