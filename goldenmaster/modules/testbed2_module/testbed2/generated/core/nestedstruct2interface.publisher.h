/**
NO TITLE
Copyright (C) 2020 ApiGear UG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#include "testbed2/generated/api/datastructs.api.h"
#include "testbed2/generated/api/nestedstruct2interface.api.h"
#include "testbed2/generated/api/common.h"

#include <vector>
#include <map>
#include <functional>

namespace Test {
namespace Testbed2 {

/**
 * The implementation of a NestedStruct2InterfacePublisher.
 * Use this class to store clients of the NestedStruct2Interface and inform them about the change
 * on call of the appropriate publish function.
 */
class TEST_TESTBED2_EXPORT NestedStruct2InterfacePublisher : public INestedStruct2InterfacePublisher
{
public:
    /**
    * Implementation of INestedStruct2InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(INestedStruct2InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(INestedStruct2InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of INestedStruct2InterfacePublisher::subscribeToProp1Changed
    */
    long subscribeToProp1Changed(NestedStruct2InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(long handleId) override;

    /**
    * Implementation of INestedStruct2InterfacePublisher::subscribeToProp2Changed
    */
    long subscribeToProp2Changed(NestedStruct2InterfaceProp2PropertyCb callback) override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::subscribeToProp2Changed
    */
    void unsubscribeFromProp2Changed(long handleId) override;

    /**
    * Implementation of INestedStruct2InterfacePublisher::subscribeToSig1
    */
    long subscribeToSig1(NestedStruct2InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(long handleId) override;

    /**
    * Implementation of INestedStruct2InterfacePublisher::subscribeToSig2
    */
    long subscribeToSig2(NestedStruct2InterfaceSig2SignalCb callback) override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::unsubscribeFromSig2
    */
    void unsubscribeFromSig2(long handleId) override;

    /**
    * Implementation of INestedStruct2InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(const NestedStruct1& prop1) const override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::publishProp2Changed
    */
    void publishProp2Changed(const NestedStruct2& prop2) const override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::publishSig1
    */
    void publishSig1(const NestedStruct1& param1) const override;
    /**
    * Implementation of INestedStruct2InterfacePublisher::publishSig2
    */
    void publishSig2(const NestedStruct1& param1,const NestedStruct2& param2) const override;
private:
    // Subscribers informed about any property change or singal emited in NestedStruct2Interface
    std::vector<std::reference_wrapper<INestedStruct2InterfaceSubscriber>> m_allChangesSubscribers;
    // Next free unique identifier to subscribe for the Prop1 change.
    long m_prop1ChangedCallbackNextId = 0;
    // Subscribed callbacks for the Prop1 change.
    std::map<long, NestedStruct2InterfaceProp1PropertyCb> m_prop1Callbacks;
    // Next free unique identifier to subscribe for the Prop2 change.
    long m_prop2ChangedCallbackNextId = 0;
    // Subscribed callbacks for the Prop2 change.
    std::map<long, NestedStruct2InterfaceProp2PropertyCb> m_prop2Callbacks;
    // Next free unique identifier to subscribe for the Sig1 emission.
    long m_sig1SignalCallbackNextId = 0;
    // Subscribed callbacks for the Sig1 emission.
    std::map<long, NestedStruct2InterfaceSig1SignalCb > m_sig1Callbacks;
    // Next free unique identifier to subscribe for the Sig2 emission.
    long m_sig2SignalCallbackNextId = 0;
    // Subscribed callbacks for the Sig2 emission.
    std::map<long, NestedStruct2InterfaceSig2SignalCb > m_sig2Callbacks;
};

} // namespace Testbed2
} // namespace Test