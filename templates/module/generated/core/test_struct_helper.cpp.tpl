{{- /* Copyright (c) ApiGear UG 2024 */}}
{{- $namespacePrefix := printf "%s::" (Camel .Module.Name) -}}

#include "test_struct_helper.h"

using namespace {{ Camel .System.Name }};

{{- range .Module.Structs }}
	{{- $structName := printf "test_%s" (snake .Name)}}
	{{- $structType := .Name}}

void {{ Camel .Module.Name }}::fillTest{{Camel .Name }}({{Camel .Module.Name }}::{{$structType}}& {{$structName}})
{
{{- range .Fields }}
	{{- if .IsArray }}
	auto local_{{snake .Name}}_array = {{ cppDefault $namespacePrefix . }};
	{{- if not ( or (eq .KindType "extern") ( or .IsPrimitive  (eq .KindType "enum") ) )}}
	auto element{{snake .Name}} = {{ cppDefault $namespacePrefix . }};
	fillTest{{Camel .Type }}(element{{snake .Name}});
	{{- else}}
	auto element{{snake .Name}} = {{cppTestValue $namespacePrefix . }};
	{{- end }}
	local_{{snake .Name}}_array.push_back(element{{snake .Name}});
	{{$structName}}.{{.Name }} = local_{{snake .Name}}_array;
	{{- else if not ( or (eq .KindType "extern") ( or .IsPrimitive  (eq .KindType "enum") ) )}}
	fillTest{{Camel .Type }}({{$structName}}.{{.Name }});
	{{- else }}
	{{$structName}}.{{.Name }} = {{ cppTestValue $namespacePrefix . }};
	{{- end }}
{{- end }}
}
{{- end }}
