{{- /* Copyright (c) ApiGear UG 2024 */}}
#pragma once

{{- $export :=  printf "%s_%s_EXPORT"  (SNAKE .System.Name) ( SNAKE .Module.Name  ) }}
#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/api/common.h"
{{- if len .Module.Externs }}
THIRD_PARTY_INCLUDES_START
{{- end }}
{{- range .Module.Externs }}
{{- $class := cppExtern . }}
{{- if $class.Include }}
#include <{{$class.Include}}>
{{- end }}
{{- end }}
{{- if len .Module.Externs }}
THIRD_PARTY_INCLUDES_END
{{- end }}

{{- range .Module.Imports }}
{{- $includeName :=  printf "\"%s/generated/api/%s.h\"" (snake .Name) (snake .Name) }}
#include {{$includeName}}
{{- end }}


namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {

{{- range .Module.Structs }}
	{{- $structName := printf "test_%s" (snake .Name)}}
	{{- $structType := .Name}}

{{ $export }} void fillTest{{Camel .Name }}({{$structType}}& {{$structName}});
{{- end }}

}
}
