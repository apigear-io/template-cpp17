{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $module_id := snake .Module.Name}}
{{- $moduleNamespace := Camel .Module.Name}}
{{- $systemNamespace := Camel .System.Name}}
{{- $moduleUpper :=  SNAKE .Module.Name -}}
{{- $systemUpper :=  SNAKE .System.Name -}}
#pragma once

#include <cinttypes>
#include <string>
#include <list>

#include "{{$module_id}}/generated/api/common.h"

{{- if or ( len .Module.Structs ) ( len .Module.Enums ) }}

namespace {{ $systemNamespace }} {
namespace {{ $moduleNamespace }} {
  
{{- range .Module.Structs }}
struct {{.Name}};
{{- end }}

{{- /* ***************************************************************** */ -}}
{{- /* *** ENUMERATIONS                                              *** */ -}}
{{- /* ***************************************************************** */ -}}

{{- range .Module.Enums }}
{{- $class := .Name }}

/**
 * Enumeration {{$class}}
 {{- if .Description }}
 *
 * {{.Description}}
{{- end }}
 */
enum class {{$class}}Enum {
{{- range $idx, $elem := .Members }}
    {{- if $idx}},{{end}}
    {{ .Name }} = {{ .Value }} 
    {{- if .Description -}}
    /** .Description */
    {{- end }}
{{- end }}
};
{{ $systemUpper }}_{{ $moduleUpper }}_EXPORT {{$class}}Enum to{{ upper1 $class }}Enum(std::uint8_t v, bool *ok);

{{- end }}

{{- /* ***************************************************************** */ -}}
{{- /* *** STRUCTS                                                   *** */ -}}
{{- /* ***************************************************************** */ -}}

{{- range .Module.Structs }}
{{- $class := .Name}}

/**
 * Struct {{$class}}
 {{- if .Description }}
 *
 * {{.Description}}
{{- end }}
 */
struct {{ $systemUpper }}_{{ $moduleUpper }}_EXPORT {{$class}}
{
    {{$class}}();
    {{- /* constructor with parameters for all members */}}
    {{$class}}({{ cppParams "" .Fields }});
{{/* members */}}
{{- range  .Fields }}
{{- if .Description }}
    /**
     * {{.Description}}
     */
{{- end }}
    {{ cppType "" . }} {{.Name}}{};
{{- end }}

};
bool {{ $systemUpper }}_{{ $moduleUpper }}_EXPORT operator==(const {{$class}} &, const {{$class}} &) noexcept;
bool {{ $systemUpper }}_{{ $moduleUpper }}_EXPORT operator!=(const {{$class}} &, const {{$class}} &) noexcept;
{{- end }}
} // namespace {{ $moduleNamespace }}
} // namespace {{ $systemNamespace }}
{{- end }}
