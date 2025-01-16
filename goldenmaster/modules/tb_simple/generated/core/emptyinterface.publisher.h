#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/emptyinterface.api.h"
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
 * The implementation of a EmptyInterfacePublisher.
 * Use this class to store clients of the EmptyInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TB_SIMPLE_EXPORT EmptyInterfacePublisher : public IEmptyInterfacePublisher
{
public:
    /**
    * Implementation of IEmptyInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IEmptyInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IEmptyInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IEmptyInterfaceSubscriber& subscriber) override;

private:
    // Subscribers informed about any property change or signal emitted in EmptyInterface
    std::vector<std::reference_wrapper<IEmptyInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
};

} // namespace TbSimple
} // namespace Test
