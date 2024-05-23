{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#pragma once

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif
#include <nlohmann/json.hpp>
{{- if len .Module.Structs }}
#include "{{snake .Module.Name}}/generated/api/datastructs.api.h"
#include "{{snake .Module.Name}}/generated/api/common.h"
{{ $system:= .System }}
{{- $module:= .Module }}
namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {
{{- range  .Module.Structs }}
{{- $class:= .Name }}
/** Function that converts json formated data into {{$class}}.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p {{$class}} that will be filled with data from j.
*  In case data is malformed or not convertable to {{$class}} the function will throw.
*/
void {{ SNAKE $system.Name  }}_{{ SNAKE $module.Name  }}_EXPORT from_json(const nlohmann::json& j, {{$class}}& p);
/** Function that converts json formated data into {{$class}}
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input {{$class}}/'}
' from which json data will be filled
*/
void {{ SNAKE $system.Name  }}_{{ SNAKE $module.Name  }}_EXPORT to_json(nlohmann::json& j, const {{$class}}& p);

/**
 * @brief Overloads the << operator to allow printing of {{$class}} objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The {{$class}} object to be printed.
 * @return std::ostream& The modified output stream.
 */
{{ SNAKE $system.Name  }}_{{ SNAKE $module.Name  }}_EXPORT std::ostream& operator<<(std::ostream& os, const {{$class}}& obj);
{{- nl}}
{{- end }}
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
{{- end }}
