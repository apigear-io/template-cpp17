{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $class := printf "%sTraceDecorator" $interfaceName }}
{{- $sub_class := printf "I%sSubscriber" $interfaceName }}
{{- $pub_class := printf "I%sPublisher" $interfaceName }}
#pragma once
#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {

class {{.Interface.Name}}Tracer;

class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}} : public {{$interfaceClass}}, public {{$sub_class}}
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The {{.Interface.Name}} object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit {{$class}}({{$interfaceClass}}& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the {{$class}} object.
    * @param impl The {{.Interface.Name}} object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<{{$class}}> connect({{$interfaceClass}}& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~{{$class}}();
{{- nl}}

{{- range .Interface.Operations}}
{{- $operation := . }}
    /** Traces {{$operation.Name}} and forwards call to {{$interfaceNameOriginal}} implementation. */
    {{cppReturn "" $operation.Return}} {{lower1 $operation.Name}}({{cppParams "" $operation.Params}}) override;
    /** Traces {{$operation.Name}} and forwards call to {{$interfaceNameOriginal}} implementation. */
    std::future<{{cppReturn "" $operation.Return}}> {{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}}) override;
    {{ end -}}
{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
    /** Forwards call to {{$interfaceNameOriginal}} implementation. */
    void set{{Camel $property.Name}}({{cppParam  "" $property }}) override;
{{- end }}
    /** Forwards call to {{$interfaceNameOriginal}} implementation. */
    {{cppTypeRef "" $property}} get{{Camel $property.Name}}() const override;
    {{ end -}}

{{- range .Interface.Signals}}
{{- $signal := . }}
    /**
    Traces {{$signal.Name}} emission.
    */
    void on{{Camel $signal.Name}}({{cppParams "" $signal.Params}}) override;
{{- end }}
{{- range .Interface.Properties}}
{{- $property := . }}
    /**
    Traces {{$property.Name}} changed.
    */
    void on{{Camel $property.Name}}Changed({{cppParam "" $property}}) override;
{{- end }}

    /**
    * Access to a publisher, use it to subscribe for {{.Interface.Name}} changes and signal emission.
    * @return The publisher for {{.Interface.Name}}.
    */
    {{$pub_class}}& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given {{.Interface.Name}} object. */
    std::unique_ptr<{{.Interface.Name}}Tracer> m_tracer;
    /** The {{.Interface.Name}} object which is traced */
    {{$interfaceClass}}& m_impl;
};
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
