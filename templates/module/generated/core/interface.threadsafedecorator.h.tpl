{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $class := printf "%sThreadSafeDecorator" $interfaceName }}
{{- $sub_class := printf "I%sSubscriber" $interfaceName }}
{{- $pub_class := printf "I%sPublisher" $interfaceName }}
#pragma once
#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {

/** 
* @brief The {{$class}} can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the {{.Interface.Name}} interface.
* @see {{.Interface.Name}}
*
\code{.cpp}
using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};

std::unique_ptr<{{$interfaceClass}}> test{{$interfaceName}} = std::make_unique<{{$class}}>(std::make_shared<{{$interfaceName}}>());

// Thread safe access
{{- range .Interface.Properties}}
{{- $property := . }}
auto {{lower1 (Camel $property.Name)}} = test{{$interfaceName}}->get{{Camel $property.Name}}();
{{- if not .IsReadOnly }}
test{{$interfaceName}}->set{{Camel $property.Name}}({{cppDefault "" $property}});
{{- end }}
{{- end }}
\endcode
*/
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}} : public {{$interfaceClass}}
{
public:
    /** 
    * ctor
    * @param impl The {{$interfaceNameOriginal}} object to make thread safe.
    */
    explicit {{$class}}(std::shared_ptr<{{$interfaceClass}}> impl);{{nl}}
{{- range .Interface.Operations}}
{{- $operation := . }}
    /** 
    * Forwards call to {{$interfaceNameOriginal}} implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    {{cppReturn "" $operation.Return}} {{lower1 $operation.Name}}({{cppParams "" $operation.Params}}) override;
    /** 
    * Forwards call to {{$interfaceNameOriginal}} implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<{{cppReturn "" $operation.Return}}> {{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}}) override;
{{- nl }}
{{- end }}
{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
    /** Guards and forwards call to {{$interfaceNameOriginal}} implementation. */
    void set{{Camel $property.Name}}({{cppParam  "" $property }}) override;
{{- end }}
    /** Guards and forwards call to {{$interfaceNameOriginal}} implementation. */
    {{cppTypeRef "" $property}} get{{Camel $property.Name}}() const override;
{{- nl }}
{{- end }}
    /**
    * Access to a publisher, use it to subscribe for {{$interfaceNameOriginal}} changes and signal emission.
    * This call is thread safe.
    * @return The publisher for {{$interfaceNameOriginal}}.
    */
    {{$pub_class}}& _getPublisher() const override;
private:
    /** The {{$interfaceNameOriginal}} object which is guarded */
    std::shared_ptr<{{$interfaceClass}}> m_impl;
{{- range .Interface.Properties}}
{{- $property := . }}
    // Mutex for {{lower1 (Camel $property.Name)}} property
    mutable std::shared_timed_mutex m_{{lower1 (Camel $property.Name)}}Mutex;
{{- end }}
};
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
