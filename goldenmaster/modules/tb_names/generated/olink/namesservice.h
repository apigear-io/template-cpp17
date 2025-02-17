
#pragma once

#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/api/common.h"
#include "olink/iobjectsource.h"


namespace ApiGear {
namespace ObjectLink {

class RemoteRegistry;
class IRemoteNode;

}} //namespace ApiGear::ObjectLink

namespace Test {
namespace TbNames {
namespace olink {
/**
* Server side for Nam_Es implements the Nam_Es service.
* It is a source of data for Nam_Es clients.
* Sends and receives data over the network with ObjectLink protocol. 
* see https://objectlinkprotocol.net for Object Link Details
*/
class TEST_TB_NAMES_EXPORT Nam_EsService : public ApiGear::ObjectLink::IObjectSource, public INamEsSubscriber
{
public:
    /**
    * ctor
    * @param Nam_Es The service source object, the actual Nam_Es object which is exposed for remote clients with olink.
    * @param registry The global registry that keeps track of the object source services associated with network nodes.
    */
    explicit Nam_EsService(std::shared_ptr<INamEs> Nam_Es, ApiGear::ObjectLink::RemoteRegistry& registry);
    virtual ~Nam_EsService() override;

    /**
    * The name of the object for which this service is created, object on client side has to have the same name.
    * It serves as an identifier for the source registry, it has to be unique for the pair source object - remote node.
    * Passed in the olink messages as an object identifier.
    */
    std::string olinkObjectName() override;
    /**
    * Applies received method invocation with given arguments on the Nam_Es object.
    * @param name Path of the method to invoke. Contains object name and the method name.
    * @param args Arguments required to invoke a method in json format.
    * @return the result of the invoked method (if applicable) that needs to be sent back to the clients.
    */
    nlohmann::json olinkInvoke(const std::string& methodId, const nlohmann::json& args) override;
    /**
    * Applies received change property request to Nam_Es object.
    * @param name Path the property to change. Contains object name and the property name.
    * @param args Value in json format requested to set for the property.
    */
    void olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) override;
    /**
    * Informs this service source that the link was established.
    * @param name The name of the object for which link was established.
    * @param the initialized link endpoint.
    */
    void olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode *node) override;
    /**
    * Informs this service source that the link was disconnected and cannot be used anymore.
    */
    void olinkUnlinked(const std::string& objectId) override;

    /**
    * Gets the current state of Nam_Es object.
    * @return the set of properties with their current values for the Nam_Es object in json format.
    */
    nlohmann::json olinkCollectProperties() override;
    /**
    * Forwards emitted SOME_SIGNAL through network if the connection is established.
    */
    void onSomeSignal(bool SOME_PARAM) override;
    /**
    * Forwards emitted Some_Signal2 through network if the connection is established.
    */
    void onSomeSignal2(bool Some_Param) override;
    /**
    * Forwards Switch change through network if the connection is established.
    */
    void onSwitchChanged(bool Switch) override;
    /**
    * Forwards SOME_PROPERTY change through network if the connection is established.
    */
    void onSomePropertyChanged(int SOME_PROPERTY) override;
    /**
    * Forwards Some_Poperty2 change through network if the connection is established.
    */
    void onSomePoperty2Changed(int Some_Poperty2) override;
    /**
    * Forwards enum_property change through network if the connection is established.
    */
    void onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property) override;

private:
    /**
    * The Nam_Es used for object source.
    */
    std::shared_ptr<INamEs> m_Nam_Es;
    /**
    * A global registry that keeps track of object sources associated with their network layer nodes.
    */
    ApiGear::ObjectLink::RemoteRegistry& m_registry;
};
} // namespace olink
} // namespace TbNames
} // namespace Test
