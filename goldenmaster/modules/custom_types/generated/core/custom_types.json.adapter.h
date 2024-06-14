#pragma once

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif
#include <nlohmann/json.hpp>
#include "custom_types/generated/api/datastructs.api.h"
#include "custom_types/generated/api/common.h"

namespace Test {
namespace CustomTypes {
/** Function that converts json formated data into Vector3D.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p Vector3D that will be filled with data from j.
*  In case data is malformed or not convertable to Vector3D the function will throw.
*/
void TEST_CUSTOM_TYPES_EXPORT from_json(const nlohmann::json& j, Vector3D& p);
/** Function that converts json formated data into Vector3D
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input Vector3D/'}
' from which json data will be filled
*/
void TEST_CUSTOM_TYPES_EXPORT to_json(nlohmann::json& j, const Vector3D& p);

/**
 * @brief Overloads the << operator to allow printing of Vector3D objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The Vector3D object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_CUSTOM_TYPES_EXPORT std::ostream& operator<<(std::ostream& os, const Vector3D& obj);

} // namespace CustomTypes
} // namespace Test
