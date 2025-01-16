{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#pragma once

#include "{{snake .Module.Name}}/generated/api/datastructs.api.h"
#include "{{snake .Module.Name}}/generated/api/{{lower (camel .Interface.Name)}}.api.h"
#include "{{snake .Module.Name}}/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

{{- $interfaceName := Camel .Interface.Name  }}
{{- $class := printf "I%s" $interfaceName }}
{{- $sub_class := printf "%sSubscriber" $class }}
{{- $pub_interface := printf "%sPublisher" $class }}
{{- $pub_class := printf "%sPublisher" $interfaceName }}

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {

/**
 * The implementation of a {{$pub_class}}.
 * Use this class to store clients of the {{.Interface.Name}} and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$pub_class}} : public {{$pub_interface}}
{
public:
    /**
    * Implementation of {{$pub_interface}}::subscribeToAllChanges
    */
    void subscribeToAllChanges({{$sub_class}}& subscriber) override;
    /**
    * Implementation of {{$pub_interface}}::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges({{$sub_class}}& subscriber) override;
{{- nl}}
{{- range .Interface.Properties}}
{{- $property := . }}
    /**
    * Implementation of {{$pub_interface}}::subscribeTo{{Camel $property.Name}}Changed
    */
    long subscribeTo{{Camel $property.Name}}Changed({{$interfaceName}}{{Camel $property.Name}}PropertyCb callback) override;
    /**
    * Implementation of {{$pub_interface}}::subscribeTo{{Camel $property.Name}}Changed
    */
    void unsubscribeFrom{{Camel $property.Name}}Changed(long handleId) override;
{{- nl}}
{{- end }}
{{- range .Interface.Signals}}
{{- $signal := . }}
    /**
    * Implementation of {{$pub_interface}}::subscribeTo{{Camel $signal.Name}}
    */
    long subscribeTo{{Camel $signal.Name}}({{$interfaceName}}{{Camel $signal.Name}}SignalCb callback) override;
    /**
    * Implementation of {{$pub_interface}}::unsubscribeFrom{{Camel $signal.Name}}
    */
    void unsubscribeFrom{{Camel $signal.Name}}(long handleId) override;
{{- nl}}
{{- end }}
{{- range .Interface.Properties}}
{{- $property := . }}
    /**
    * Implementation of {{$pub_interface}}::publish{{Camel $property.Name}}Changed
    */
    void publish{{Camel $property.Name}}Changed({{cppParam "" $property}}) const override;
{{- end }}
{{- range .Interface.Signals}}
{{- $signal := . }}
    /**
    * Implementation of {{$pub_interface}}::publish{{Camel $signal.Name}}
    */
    void publish{{Camel $signal.Name}}({{cppParams "" $signal.Params}}) const override;
{{- end }}
private:
    // Subscribers informed about any property change or signal emitted in {{.Interface.Name}}
    std::vector<std::reference_wrapper<{{$sub_class}}>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
{{- range .Interface.Properties}}
{{- $property := . }}
    ApiGear::Utilities::SinglePub< {{- cppType "" $property -}}> {{Camel $property.Name}}Publisher;
{{- end }}
{{- range .Interface.Signals}}
{{- $signal := . }}
    ApiGear::Utilities::SinglePub<{{- range $idx, $elem := $signal.Params }}
        {{- $param := . -}}
                {{- if $idx }},{{- end -}}
                {{cppType "" $param}}
        {{- end -}}> {{Camel $signal.Name}}Publisher;

{{- end }}
};
{{- nl}}
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
