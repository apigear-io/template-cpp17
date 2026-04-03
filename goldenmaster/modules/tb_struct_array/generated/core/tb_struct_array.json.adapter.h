#pragma once

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif
#include <nlohmann/json.hpp>
#include "tb_struct_array/generated/api/datastructs.api.h"
#include "tb_struct_array/generated/api/common.h"

namespace Test {
namespace TbStructArray {
/** Function that converts json formated data into Point.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p Point that will be filled with data from j.
*  In case data is malformed or not convertable to Point the function will throw.
*/
void TEST_TB_STRUCT_ARRAY_EXPORT from_json(const nlohmann::json& j, Point& p);
/** Function that converts json formated data into Point
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input Point/'}
' from which json data will be filled
*/
void TEST_TB_STRUCT_ARRAY_EXPORT to_json(nlohmann::json& j, const Point& p);

/**
 * @brief Overloads the << operator to allow printing of Point objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The Point object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TB_STRUCT_ARRAY_EXPORT std::ostream& operator<<(std::ostream& os, const Point& obj);

/** Function that converts json formated data into StructWithArrayOfStructs.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructWithArrayOfStructs that will be filled with data from j.
*  In case data is malformed or not convertable to StructWithArrayOfStructs the function will throw.
*/
void TEST_TB_STRUCT_ARRAY_EXPORT from_json(const nlohmann::json& j, StructWithArrayOfStructs& p);
/** Function that converts json formated data into StructWithArrayOfStructs
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructWithArrayOfStructs/'}
' from which json data will be filled
*/
void TEST_TB_STRUCT_ARRAY_EXPORT to_json(nlohmann::json& j, const StructWithArrayOfStructs& p);

/**
 * @brief Overloads the << operator to allow printing of StructWithArrayOfStructs objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructWithArrayOfStructs object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TB_STRUCT_ARRAY_EXPORT std::ostream& operator<<(std::ostream& os, const StructWithArrayOfStructs& obj);

/** Function that converts json formated data into StructWithArrayOfEnums.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructWithArrayOfEnums that will be filled with data from j.
*  In case data is malformed or not convertable to StructWithArrayOfEnums the function will throw.
*/
void TEST_TB_STRUCT_ARRAY_EXPORT from_json(const nlohmann::json& j, StructWithArrayOfEnums& p);
/** Function that converts json formated data into StructWithArrayOfEnums
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructWithArrayOfEnums/'}
' from which json data will be filled
*/
void TEST_TB_STRUCT_ARRAY_EXPORT to_json(nlohmann::json& j, const StructWithArrayOfEnums& p);

/**
 * @brief Overloads the << operator to allow printing of StructWithArrayOfEnums objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructWithArrayOfEnums object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TB_STRUCT_ARRAY_EXPORT std::ostream& operator<<(std::ostream& os, const StructWithArrayOfEnums& obj);

/** Function that converts json formated data into StructWithArrayOfInts.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructWithArrayOfInts that will be filled with data from j.
*  In case data is malformed or not convertable to StructWithArrayOfInts the function will throw.
*/
void TEST_TB_STRUCT_ARRAY_EXPORT from_json(const nlohmann::json& j, StructWithArrayOfInts& p);
/** Function that converts json formated data into StructWithArrayOfInts
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructWithArrayOfInts/'}
' from which json data will be filled
*/
void TEST_TB_STRUCT_ARRAY_EXPORT to_json(nlohmann::json& j, const StructWithArrayOfInts& p);

/**
 * @brief Overloads the << operator to allow printing of StructWithArrayOfInts objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructWithArrayOfInts object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TB_STRUCT_ARRAY_EXPORT std::ostream& operator<<(std::ostream& os, const StructWithArrayOfInts& obj);

/** Function that converts json formated data into MixedStruct.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p MixedStruct that will be filled with data from j.
*  In case data is malformed or not convertable to MixedStruct the function will throw.
*/
void TEST_TB_STRUCT_ARRAY_EXPORT from_json(const nlohmann::json& j, MixedStruct& p);
/** Function that converts json formated data into MixedStruct
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input MixedStruct/'}
' from which json data will be filled
*/
void TEST_TB_STRUCT_ARRAY_EXPORT to_json(nlohmann::json& j, const MixedStruct& p);

/**
 * @brief Overloads the << operator to allow printing of MixedStruct objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The MixedStruct object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TB_STRUCT_ARRAY_EXPORT std::ostream& operator<<(std::ostream& os, const MixedStruct& obj);

} // namespace TbStructArray
} // namespace Test
