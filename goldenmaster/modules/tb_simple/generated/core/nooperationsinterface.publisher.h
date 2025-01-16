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
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
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
    long subscribeToPropBoolChanged(NoOperationsInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(long handleId) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(NoOperationsInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToSigVoid
    */
    long subscribeToSigVoid(NoOperationsInterfaceSigVoidSignalCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::unsubscribeFromSigVoid
    */
    void unsubscribeFromSigVoid(long handleId) override;

    /**
    * Implementation of INoOperationsInterfacePublisher::subscribeToSigBool
    */
    long subscribeToSigBool(NoOperationsInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of INoOperationsInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(long handleId) override;

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
