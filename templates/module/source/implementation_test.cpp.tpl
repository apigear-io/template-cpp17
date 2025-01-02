{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#include <memory>
#include "catch2/catch.hpp"
#include "{{snake .Module.Name}}/implementation/{{lower (camel .Interface.Name)}}.h"
#include "apigear/utilities/fuzzy_compare.h"

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
{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
    SECTION("Test property {{$property.Name}}") {
        // Do implement test here
        {{- if not .IsReadOnly }}
        test{{$class}}->set{{Camel $property.Name}}({{cppDefault "" $property}});
        {{- end }}
        auto actual = test{{$class}}->get{{Camel $property.Name}}();
        auto expected =  {{cppDefault "" $property}};
        REQUIRE({{- if ( or ( eq (cppType "" $property) "float") ( eq (cppType "" $property) "double") ) -}}
            ApiGear::Utilities::fuzzyCompare(actual, expected)
        {{- else -}}
            actual == expected
        {{- end -}} 
        );
    }
{{- end }}
}
