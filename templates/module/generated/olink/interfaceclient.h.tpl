{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $class := printf "%sClient" .Interface.Name }}
{{- $sub_class := printf "I%sSubscriber" $interfaceName }}
{{- $pub_class := printf "I%sPublisher" $interfaceName }}
#pragma once

#include "{{snake .Module.Name}}/generated/api/common.h"
#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/core/{{lower $interfaceName}}.data.h"

#include "olink/iobjectsink.h"

#include <future>
{{- if .Interface.Properties}}
#include <shared_mutex>
{{- end }}
#include <memory>

namespace ApiGear{
namespace ObjectLink{
class IClientNode;
}
}

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {
namespace olink {
/**
* Adapts the general OLink Client handler to a {{$interfaceNameOriginal}} publisher in a way it provides access 
* to remote {{$interfaceNameOriginal}} services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect {{$class}} to it.
* Use on client side to request changes of the {{$interfaceNameOriginal}} on the server side 
* and to subscribe for the {{$interfaceNameOriginal}} changes.
*/
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}} : public {{$interfaceClass}},
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit {{$class}}();
    /** dtor */
    virtual ~{{$class}}() = default;

{{- range .Interface.Properties}}
{{- $property := . }}
    /**
    * Property getter
    * @return Locally stored locally value for {{Camel $property.Name}}.
    */
    {{cppTypeRef "" $property}} get{{Camel $property.Name}}() const override;
{{- if not .IsReadOnly }}
    /**
    * Request setting a property on the {{$interfaceNameOriginal}} service.
    * @param The value to which set request is send for the {{Camel $property.Name}}.
    */
    void set{{Camel $property.Name}}({{cppParam "" $property}}) override;
{{- end }}
{{- end }}
{{- range .Interface.Operations}}
{{- $operation := . }}
    /**
    * Remote call of {{$interfaceClass}}::{{$operation.Name}} on the {{$interfaceNameOriginal}} service.
    * Uses {{$operation.Name}}Async
    */
    {{cppReturn "" $operation.Return}} {{lower1 $operation.Name}}({{cppParams "" $operation.Params}}) override;
    /**
    * Remote call of {{$interfaceClass}}::{{$operation.Name}} on the {{$interfaceNameOriginal}} service.
    */
    std::future<{{cppReturn "" $operation.Return}}> {{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}}) override;
{{- end }}

    /** The publisher to subscribe to. */
    {{$pub_class}}& _getPublisher() const override;
    
    /**
    * Informs if the {{$class}} is ready to send and receive messages.
    * @return true if {{$interfaceNameOriginal}} is operable, false otherwise.
    */
    bool isReady() const;

    /**
    * The name of the object for which this sink is created, object on server side has to have the same name.
    * It serves as an identifier for the client registry, it has to be unique for the pair sink object - client node.
    * Passed in the olink messages as an object identifier.
    */
    std::string olinkObjectName() override;
    
    /**
    * Information about signal emission on a server side to all subscribers.
    * @param signalId Unique identifier for the signal emitted from object.
    * @param args The arguments for the signal.
    */
    void olinkOnSignal(const std::string& signalId, const nlohmann::json& args) override;
    
    /**
    * Applies the information about the property changed on server side.
    * @param propertyId Unique identifier of a changed property in object .
    * @param value The value of the property.
    */
    void olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value) override;
    
    /** Informs this object sink that connection was is established.
    * @param interfaceId The name of the object for which link was established.
    * @param props Initial values obtained from the {{$interfaceNameOriginal}} service
    * @param the initialized link endpoint for this sink.
    */
    void olinkOnInit(const std::string& interfaceId, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node) override;
    /**
    * Informs this object source that the link was disconnected and cannot be used anymore.
    */
    void olinkOnRelease() override;

private:
    /**
    * Applies received data to local state and publishes changes to subscribers.
    * @param the data received from {{$interfaceNameOriginal}} service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
{{- range .Interface.Properties}}
{{- $property := . }}
    /**  Updates local value for {{Camel $property.Name}} and informs subscriber about the change*/
    void set{{Camel $property.Name}}Local({{cppParam "" $property}});
    /* Mutex for {{lower1 (Camel $property.Name)}} property */
    mutable std::shared_timed_mutex m_{{lower1 (Camel $property.Name)}}Mutex;

{{- end }}
{{ if .Interface.Properties}}
    /** Local storage for properties values. */
    {{$interfaceName}}Data m_data;
{{ end }}
    /** 
    * An abstraction layer over the connection with service for the {{$class}}.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for {{$interfaceNameOriginal}} */
    std::unique_ptr<{{$pub_class}}> m_publisher;
};
} // namespace olink
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
