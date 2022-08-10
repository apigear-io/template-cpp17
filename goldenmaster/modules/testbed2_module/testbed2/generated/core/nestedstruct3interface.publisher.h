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
#include "testbed2/generated/api/nestedstruct3interface.api.h"
#include "testbed2/generated/api/common.h"

#include <vector>
#include <map>
#include <functional>

namespace Test {
namespace Testbed2 {

/**
 * The implementation of a NestedStruct3InterfacePublisher.
 * Use this class to store clients of the NestedStruct3Interface and inform them about the change
 * on call of the appropriate publish function.
 */
class TEST_TESTBED2_EXPORT NestedStruct3InterfacePublisher : public INestedStruct3InterfacePublisher
{
public:
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(INestedStruct3InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(INestedStruct3InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp1Changed
    */
    long subscribeToProp1Changed(NestedStruct3InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(long handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp2Changed
    */
    long subscribeToProp2Changed(NestedStruct3InterfaceProp2PropertyCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp2Changed
    */
    void unsubscribeFromProp2Changed(long handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp3Changed
    */
    long subscribeToProp3Changed(NestedStruct3InterfaceProp3PropertyCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp3Changed
    */
    void unsubscribeFromProp3Changed(long handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToSig1
    */
    long subscribeToSig1(NestedStruct3InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(long handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToSig2
    */
    long subscribeToSig2(NestedStruct3InterfaceSig2SignalCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromSig2
    */
    void unsubscribeFromSig2(long handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToSig3
    */
    long subscribeToSig3(NestedStruct3InterfaceSig3SignalCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromSig3
    */
    void unsubscribeFromSig3(long handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(const NestedStruct1& prop1) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishProp2Changed
    */
    void publishProp2Changed(const NestedStruct2& prop2) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishProp3Changed
    */
    void publishProp3Changed(const NestedStruct3& prop3) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishSig1
    */
    void publishSig1(const NestedStruct1& param1) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishSig2
    */
    void publishSig2(const NestedStruct1& param1,const NestedStruct2& param2) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishSig3
    */
    void publishSig3(const NestedStruct1& param1,const NestedStruct2& param2,const NestedStruct3& param3) const override;
private:
    // Subscribers informed about any property change or singal emited in NestedStruct3Interface
    std::vector<std::reference_wrapper<INestedStruct3InterfaceSubscriber>> m_allChangesSubscribers;
    // Next free unique identifier to subscribe for the Prop1 change.
    long m_prop1ChangedCallbackNextId = 0;
    // Subscribed callbacks for the Prop1 change.
    std::map<long, NestedStruct3InterfaceProp1PropertyCb> m_prop1Callbacks;
    // Next free unique identifier to subscribe for the Prop2 change.
    long m_prop2ChangedCallbackNextId = 0;
    // Subscribed callbacks for the Prop2 change.
    std::map<long, NestedStruct3InterfaceProp2PropertyCb> m_prop2Callbacks;
    // Next free unique identifier to subscribe for the Prop3 change.
    long m_prop3ChangedCallbackNextId = 0;
    // Subscribed callbacks for the Prop3 change.
    std::map<long, NestedStruct3InterfaceProp3PropertyCb> m_prop3Callbacks;
    // Next free unique identifier to subscribe for the Sig1 emission.
    long m_sig1SignalCallbackNextId = 0;
    // Subscribed callbacks for the Sig1 emission.
    std::map<long, NestedStruct3InterfaceSig1SignalCb > m_sig1Callbacks;
    // Next free unique identifier to subscribe for the Sig2 emission.
    long m_sig2SignalCallbackNextId = 0;
    // Subscribed callbacks for the Sig2 emission.
    std::map<long, NestedStruct3InterfaceSig2SignalCb > m_sig2Callbacks;
    // Next free unique identifier to subscribe for the Sig3 emission.
    long m_sig3SignalCallbackNextId = 0;
    // Subscribed callbacks for the Sig3 emission.
    std::map<long, NestedStruct3InterfaceSig3SignalCb > m_sig3Callbacks;
};

} // namespace Testbed2
} // namespace Test