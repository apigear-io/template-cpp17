{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#include <memory>
#include "catch2/catch.hpp"
#include "{{snake .Module.Name}}/implementation/{{lower (camel .Interface.Name)}}.h"

{{- $class := Camel .Interface.Name  }}

using namespace {{ Camel .System.Name }}::{{Camel .Module.Name }};
TEST_CASE("Testing {{$class}}", "[{{$class}}]"){
    std::unique_ptr<I{{$class}}> test{{$class}} = std::make_unique<{{$class}}>();
    // setup your test

{{- range .Interface.Operations}}
{{- $operation := . }}
    SECTION("Test operation {{$operation.Name}}") {
        // Do implement test here
        test{{$class}}->{{lower1 $operation.Name}}(
            {{- range  $idx, $elem := $operation.Params -}}
            {{- $param := . -}}
                {{- if $idx}}, {{end}}
                {{- cppDefault "" $param -}}
            {{- end -}}
            );
    }

    SECTION("Test operation async {{$operation.Name}}") {
        // Do implement test here

        auto future = test{{$class}}->{{lower1 $operation.Name}}Async(
            {{- range  $idx, $elem := $operation.Params -}}
            {{- $param := . -}}
                {{- if $idx}}, {{end}}
                {{- cppDefault "" $param -}}
            {{- end -}}
            );
    }

    SECTION("Test operation async {{$operation.Name}} with a callback") {
        // Do implement test here

        auto future = test{{$class}}->{{lower1 $operation.Name}}Async(
            {{- range  $idx, $elem := $operation.Params -}}
            {{- $param := . -}}
                {{- if $idx}}, {{end}}
                {{- cppDefault "" $param -}}
            {{- end -}}{{- if (len .Params) }},{{end -}}
            []({{- if (not .Return.IsVoid) }}{{cppType "" .Return}} value){ (void)value; {{ else}} ){ {{end}}/* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
    SECTION("Test property {{$property.Name}}") {
        // Do implement test here
        {{- if not .IsReadOnly }}
        test{{$class}}->set{{Camel $property.Name}}({{cppDefault "" $property}});
        {{- end }}
        REQUIRE( test{{$class}}->get{{Camel $property.Name}}() =={{ if ( eq (cppType "" $property) "float") }} Approx({{- end }} {{cppDefault "" $property}}{{ if ( eq (cppType "" $property) "float")}} ){{- end }} );
    }
{{- end }}
}
