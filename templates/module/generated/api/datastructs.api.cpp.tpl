{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#include "{{snake .Module.Name}}/generated/api/datastructs.api.h"

{{- if or ( len .Module.Structs ) ( len .Module.Enums ) }}

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {

{{- range .Module.Enums }}
{{- $class := .Name }}

// ********************************************************************
// Enumeration {{$class}}
// ********************************************************************
{{$class}}Enum to{{Camel $class}}Enum(std::uint8_t v, bool *ok)
{
    if (ok != nullptr) {
        *ok = true;
    }
    switch (v) {
{{- range .Members }}
{{- $member := . }}
        case {{$member.Value}}: return {{$class}}Enum::{{$member.Name}};
{{- end }}
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return {{$class}}Enum::{{ .Default.Name -}} ;
    }
}
{{- end }}

{{- range .Module.Structs }}
{{- $class := .Name }}
// ********************************************************************
// Struct {{$class}}
// ********************************************************************
{{$class}}::{{$class}}() = default;
{{$class}}::{{$class}}({{ cppParams "" .Fields }})
{{- range $idx, $elem := .Fields }}
{{- $field := . -}}
{{ if $idx }},{{else}}:{{- end }}
    {{$field.Name}}({{$field.Name}})
{{- end }}
{
}

bool operator==(const {{$class}}& lhs, const {{$class}}& rhs) noexcept
{
    return (
{{- range $idx, $elem := .Fields }}
        {{- $field := . }}
        {{- if $idx }} &&{{ end }}
        lhs.{{$field.Name}} == rhs.{{$field.Name}}
{{- end }}

    );
}

bool operator!=(const {{$class}}& lhs, const {{$class}}& rhs) noexcept
{
    return !(lhs == rhs);
}

{{- end }}
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
{{- end }}
