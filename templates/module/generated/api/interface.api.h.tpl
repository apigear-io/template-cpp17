{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#pragma once

#include <future>
#include "{{snake .Module.Name}}/generated/api/common.h"
#include "{{snake .Module.Name}}/generated/api/datastructs.api.h"
{{- range .Module.Imports }}
#include "{{snake .Name}}/generated/api/datastructs.api.h"
{{- end }}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $class := printf "I%s" $interfaceName }}
{{- $interface := .Interface }}

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {

{{- $sub_class := printf "%sSubscriber" $class }}
{{- $pub_class := printf "%sPublisher" $class }}

class {{$sub_class}};
class {{$pub_class}};

/**
{{- if .Interface.Description }}
 * {{.Interface.Description}}
{{- end }}   {{- /* end if interface description */}}
*
* {{$class}} provides an interface for
 *  - methods defined for your {{.Interface.Name}} 
 *  - property setters and getters for defined properties
 * The {{$class}} also provides an interface to access a publisher {{$pub_class}}, a class used by {{$sub_class}} clients.
 * The implementation should notify the publisher {{$pub_class}} about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also {{$sub_class}}, {{$pub_class}}
 * and the example implementation {{.Interface.Name}}  or the
 */
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}}
{
public:
    virtual ~{{$class}}() = default;
{{- nl }}
{{- range .Interface.Operations }}
{{ $operation := . }}
{{- if $operation.Description }}
    /**
    * {{ $operation.Description }}
{{- range $operation.Params }}
{{- $param := . }}
{{- if $param.Description }}
    * @param {{$param}} {{$param.Description}}
{{- end }}   {{- /* end if param description */}}
{{- end }}   {{- /* end range operation param*/}}  
    */
{{- end }}   {{- /* end if operations description */}}
    virtual {{ cppReturn "" $operation.Return}} {{lower1 $operation.Name }}({{cppParams "" $operation.Params}}) = 0;
    /**
    * Asynchronous version of {{ $operation.Name}}({{ cppParams "" $operation.Params}})
{{- if $operation.Description }}
    * {{$operation.Description}}
{{- end }}   {{- /* end if description */}}
{{- range $operation.Params }}
{{- $param := . }}
{{- if $param.Description }}
    * @param {{$param}} {{$param.Description}}
{{- end }}   {{- /* end if description */}}
{{- end }}   {{- /* end range operation params */}}
    * @return Promise of type {{cppReturn "" $operation.Return}} which is set once the function has completed
    */
    virtual std::future<{{cppReturn "" $operation.Return}}> {{lower1 $operation.Name }}Async({{cppParams "" $operation.Params}}) = 0;
{{ end }}   {{- /* end range operations */}}

{{- range .Interface.Properties }}
{{- $property := . }}
{{- if not .IsReadOnly }}
    /**
    * Sets the value of the {{$property.Name}} property.
    {{- if $property.Description }}
    * @param {{$property.Name}} {{$property.Description}}
    {{- end }}    {{- /* end if property.Description */}}
    */
    virtual void set{{Camel $property.Name}}({{ cppParam "" $property }}) = 0;
{{- end }}
    /**
    * Gets the value of the {{$property.Name}} property.
    {{- if $property.Description }}
    * @return {{$property.Description}}
    {{- end }}    {{- /* end if property.Description */}}
    */
    virtual {{cppTypeRef "" $property}} get{{Camel $property.Name }}() const = 0;
{{ end }}    {{- /* end range properties */}}
    /**
    * Access to a publisher, use it to subscribe for {{.Interface.Name}} changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for {{.Interface.Name}}.
    */
    virtual {{$pub_class}}& _getPublisher() const = 0;
};


/**
 * The {{$sub_class}} contains functions to allow informing about signals or property changes of the {{$class}} implementation.
 * The implementation for {{$class}} should provide mechanism for subscription of the {{$sub_class}} clients.
 * See {{$pub_class}}, which provides facilitation for this purpose.
 * The implementation for {{$class}} should call the {{$sub_class}} interface functions on either signal emit or property change.
 * You can use {{$sub_class}} class to implement clients of the {{$class}} or the network adapter - see Olink Server and Client example.
 */
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$sub_class}}
{
public:
    virtual ~{{$sub_class}}() = default;
{{- range .Interface.Signals }}
{{- $signal := . }}
    /**
    * Called by the {{$pub_class}} when the {{$interface.Name}} emits {{$signal.Name}}, if subscribed for the {{$signal.Name}}.
    {{- if $signal.Description }}
    * {{$signal.Description}}
    {{- end }}
    {{- range $signal.Params }}
    {{- $param := . }}
    * @param {{$param.Name}} {{$param.Description}}
    {{- end -}} {{/* range singal.Params */}}
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void on{{Camel $signal.Name }}({{ cppParams "" $signal.Params }}) = 0;
{{- end }}   {{- /* end range signals */}}
{{- range .Interface.Properties }}
{{- $property:= . }}
    /**
    * Called by the {{$pub_class}} when {{$property.Name}} value has changed if subscribed for the {{$property.Name}} change.
    {{- if $property.Description }}
    * @param {{$property.Name}} {{$property.Description}}
    {{- end }}
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void on{{Camel $property.Name}}Changed({{cppParam "" $property}}) = 0;
{{- end }}
};
{{ range .Interface.Properties }}
{{- $property:= . }}
/** Callback for changes of {{$property.Name}} */
using {{Camel $interface.Name}}{{Camel $property.Name}}PropertyCb = std::function<void( {{- cppParam "" $property -}} )>;
{{- end }}
{{- range .Interface.Signals }}
{{- $signal := . }}
/** Callback for {{$signal.Name}} signal triggers */
using {{ Camel $interface.Name }}{{Camel $signal.Name }}SignalCb = std::function<void({{ cppParams "" $signal.Params }})> ;
{{- end }}


/**
 * The {{$pub_class}} provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your {{$class}} implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a {{$sub_class}} objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the I{{$class}} on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$pub_class}}
{
public:
    virtual ~{{$pub_class}}() = default;

    /**
    * Use this function to subscribe for any change of the {{.Interface.Name}}.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param {{$sub_class}} which is subscribed in this function to any change of the {{.Interface.Name}}.
    */
    virtual void subscribeToAllChanges({{$sub_class}}& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the {{.Interface.Name}}.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param {{$sub_class}} which subscription for any change of the {{.Interface.Name}} is removed.
    */
    virtual void unsubscribeFromAllChanges({{$sub_class}}& subscriber) = 0;

{{- range .Interface.Properties }}
{{ $property:= . }}
    /**
    * Use this function to subscribe for {{$property.Name}} value changes.
    * If your subscriber uses subscription with {{$sub_class}} interface, you will get two notifications, one for each subscription mechanism.
    * @param {{Camel $interface.Name }}{{Camel $property.Name }}PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeTo{{Camel $property.Name}}Changed({{Camel $interface.Name }}{{Camel $property.Name }}PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from {{$property.Name}} property changes.
    * If your subscriber uses subscription with {{$sub_class}} interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFrom{{Camel $property.Name }}Changed(long handleId) = 0;
{{- end -}} {{/* range .Interface.Properties*/}}
{{- range .Interface.Signals }}
{{ $signal := . }}
    /**
    * Use this function to subscribe for {{$signal.Name}} signal changes.
    * @param {{Camel $interface.Name }}{{Camel $signal.Name }}SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeTo{{Camel $signal.Name }}({{Camel $interface.Name }}{{Camel $signal.Name }}SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from {{$signal.Name}} signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFrom{{Camel $signal.Name }}(long handleId) = 0;
{{- end -}} {{/* range .Interface.Signals*/}}
{{- nl }}
{{- range .Interface.Properties }}
{{- $property:= . }}
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the {{$interface.Name}} implementation when property {{$property.Name}} changes.
    * @param The new value of {{$property.Name}}.
    {{- if $property.Description }}
    * {{$property.Description}}
    {{- end }}
    */
    virtual void publish{{Camel $property.Name}}Changed({{cppParam "" $property}}) const = 0;
{{- end -}} {{/* range .Interface.Properties*/}}
{{- range .Interface.Signals }}
{{- $signal:= . }}
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the {{$interface.Name}} implementation when {{$signal.Name}} is emitted.
    {{- if $signal.Description }}
    * Signal {{$signal.Description}}
    {{- end }}
    {{- range  $signal.Params }}
    {{- $param := . }}
    * @param {{$param.Name}} {{$param.Description}}
    {{- end }}
    */
    virtual void publish{{Camel $signal.Name}}({{ cppParams "" $signal.Params }}) const = 0;
{{- end -}} {{/* range .Interface.Properties*/}}
};


} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
