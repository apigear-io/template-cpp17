{{/* Copyright (c) ApiGear UG 2020 */}}
#pragma once

#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/api/common.h"
#include "olink/iobjectsource.h"
{{ $class := printf "%sService" .Interface.Name  }}
{{ $interfaceNameOriginal := .Interface.Name  }}
{{ $interfaceName := Camel .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName -}}

namespace ApiGear {
namespace ObjectLink {

class RemoteRegistry;
class IRemoteNode;

}} //namespace ApiGear::ObjectLink

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {
namespace olink {
/**
* Server side for {{$interfaceNameOriginal}} implements the {{$interfaceNameOriginal}} service.
* It is a source of data for {{$interfaceNameOriginal}} clients.
* Sends and receives data over the network with ObjectLink protocol. 
* see https://objectlinkprotocol.net for Object Link Details
*/
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}} : public ApiGear::ObjectLink::IObjectSource, public {{$interfaceClass}}Subscriber
{
public:
    /**
    * ctor
    * @param {{$interfaceNameOriginal}} The service source object, the actual {{$interfaceNameOriginal}} object which is exposed for remote clients with olink.
    * @param registry The global registry that keeps track of the object source services associated with network nodes.
    */
    explicit {{$class}}(std::shared_ptr<{{$interfaceClass}}> {{$interfaceNameOriginal}}, ApiGear::ObjectLink::RemoteRegistry& registry);
    virtual ~{{$class}}() override;

    /**
    * The name of the object for which this service is created, object on client side has to have the same name.
    * It serves as an identifier for the source registry, it has to be unique for the pair source object - remote node.
    * Passed in the olink messages as an object identifier.
    */
    std::string olinkObjectName() override;
    /**
    * Applies received method invocation with given arguments on the {{$interfaceNameOriginal}} object.
    * @param name Path of the method to invoke. Contains object name and the method name.
    * @param args Arguments required to invoke a method in json format.
    * @return the result of the invoked method (if applicable) that needs to be sent back to the clients.
    */
    nlohmann::json olinkInvoke(const std::string& methodId, const nlohmann::json& args) override;
    /**
    * Applies received change property request to {{$interfaceNameOriginal}} object.
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
    * Gets the current state of {{$interfaceNameOriginal}} object.
    * @return the set of properties with their current values for the {{$interfaceNameOriginal}} object in json format.
    */
    nlohmann::json olinkCollectProperties() override;

{{- range .Interface.Signals}}
{{- $signal := . }}
    /**
    * Forwards emitted {{$signal.Name}} through network if the connection is established.
    */
    void on{{Camel $signal.Name}}({{cppParams "" $signal.Params}}) override;
{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
    /**
    * Forwards {{$property.Name}} change through network if the connection is established.
    */
    void on{{Camel $property.Name}}Changed({{cppParam "" $property}}) override;
{{- end }}

private:
    /**
    * The {{$interfaceNameOriginal}} used for object source.
    */
    std::shared_ptr<{{$interfaceClass}}> m_{{$interfaceNameOriginal}};
    {{- if or (len .Interface.Signals) (len .Interface.Properties)  }}
    /**
    * A global registry that keeps track of object sources associated with their network layer nodes.
    */
    ApiGear::ObjectLink::RemoteRegistry& m_registry;
    {{- end}}
};
} // namespace olink
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
