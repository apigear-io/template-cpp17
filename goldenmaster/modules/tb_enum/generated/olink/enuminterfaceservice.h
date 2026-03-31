
#pragma once

#include "tb_enum/generated/api/tb_enum.h"
#include "tb_enum/generated/api/common.h"
THIRD_PARTY_INCLUDES_START
#include "olink/iobjectsource.h"
THIRD_PARTY_INCLUDES_END


namespace ApiGear {
namespace ObjectLink {

class RemoteRegistry;
class IRemoteNode;

}} //namespace ApiGear::ObjectLink

namespace Test {
namespace TbEnum {
namespace olink {
/**
* Server side for EnumInterface implements the EnumInterface service.
* It is a source of data for EnumInterface clients.
* Sends and receives data over the network with ObjectLink protocol. 
* see https://objectlinkprotocol.net for Object Link Details
*/
class TEST_TB_ENUM_EXPORT EnumInterfaceService : public ApiGear::ObjectLink::IObjectSource, public IEnumInterfaceSubscriber
{
public:
    /**
    * ctor
    * @param EnumInterface The service source object, the actual EnumInterface object which is exposed for remote clients with olink.
    * @param registry The global registry that keeps track of the object source services associated with network nodes.
    */
    explicit EnumInterfaceService(std::shared_ptr<IEnumInterface> EnumInterface, ApiGear::ObjectLink::RemoteRegistry& registry);
    virtual ~EnumInterfaceService() override;

    /**
    * The name of the object for which this service is created, object on client side has to have the same name.
    * It serves as an identifier for the source registry, it has to be unique for the pair source object - remote node.
    * Passed in the olink messages as an object identifier.
    */
    std::string olinkObjectName() override;
    /**
    * Applies received method invocation with given arguments on the EnumInterface object.
    * @param name Path of the method to invoke. Contains object name and the method name.
    * @param args Arguments required to invoke a method in json format.
    * @return the result of the invoked method (if applicable) that needs to be sent back to the clients.
    */
    nlohmann::json olinkInvoke(const std::string& methodId, const nlohmann::json& args) override;
    /**
    * Applies received change property request to EnumInterface object.
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
    * Gets the current state of EnumInterface object.
    * @return the set of properties with their current values for the EnumInterface object in json format.
    */
    nlohmann::json olinkCollectProperties() override;
    /**
    * Forwards emitted sig0 through network if the connection is established.
    */
    void onSig0(Enum0Enum param0) override;
    /**
    * Forwards emitted sig1 through network if the connection is established.
    */
    void onSig1(Enum1Enum param1) override;
    /**
    * Forwards emitted sig2 through network if the connection is established.
    */
    void onSig2(Enum2Enum param2) override;
    /**
    * Forwards emitted sig3 through network if the connection is established.
    */
    void onSig3(Enum3Enum param3) override;
    /**
    * Forwards prop0 change through network if the connection is established.
    */
    void onProp0Changed(Enum0Enum prop0) override;
    /**
    * Forwards prop1 change through network if the connection is established.
    */
    void onProp1Changed(Enum1Enum prop1) override;
    /**
    * Forwards prop2 change through network if the connection is established.
    */
    void onProp2Changed(Enum2Enum prop2) override;
    /**
    * Forwards prop3 change through network if the connection is established.
    */
    void onProp3Changed(Enum3Enum prop3) override;

private:
    /**
    * The EnumInterface used for object source.
    */
    std::shared_ptr<IEnumInterface> m_EnumInterface;
    /**
    * A global registry that keeps track of object sources associated with their network layer nodes.
    */
    ApiGear::ObjectLink::RemoteRegistry& m_registry;
};
} // namespace olink
} // namespace TbEnum
} // namespace Test
