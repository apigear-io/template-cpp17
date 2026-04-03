#pragma once

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif
#include <nlohmann/json.hpp>
#include "testbed1/generated/api/datastructs.api.h"
#include "testbed1/generated/api/common.h"

namespace Test {
namespace Testbed1 {
/** Function that converts json formated data into StructBool.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructBool that will be filled with data from j.
*  In case data is malformed or not convertable to StructBool the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructBool& p);
/** Function that converts json formated data into StructBool
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructBool/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructBool& p);

/**
 * @brief Overloads the << operator to allow printing of StructBool objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructBool object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructBool& obj);

/** Function that converts json formated data into StructInt.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructInt that will be filled with data from j.
*  In case data is malformed or not convertable to StructInt the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructInt& p);
/** Function that converts json formated data into StructInt
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructInt/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructInt& p);

/**
 * @brief Overloads the << operator to allow printing of StructInt objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructInt object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructInt& obj);

/** Function that converts json formated data into StructFloat.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructFloat that will be filled with data from j.
*  In case data is malformed or not convertable to StructFloat the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructFloat& p);
/** Function that converts json formated data into StructFloat
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructFloat/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructFloat& p);

/**
 * @brief Overloads the << operator to allow printing of StructFloat objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructFloat object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructFloat& obj);

/** Function that converts json formated data into StructString.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructString that will be filled with data from j.
*  In case data is malformed or not convertable to StructString the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructString& p);
/** Function that converts json formated data into StructString
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructString/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructString& p);

/**
 * @brief Overloads the << operator to allow printing of StructString objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructString object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructString& obj);

/** Function that converts json formated data into StructStruct.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructStruct that will be filled with data from j.
*  In case data is malformed or not convertable to StructStruct the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructStruct& p);
/** Function that converts json formated data into StructStruct
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructStruct/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructStruct& p);

/**
 * @brief Overloads the << operator to allow printing of StructStruct objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructStruct object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructStruct& obj);

/** Function that converts json formated data into StructEnum.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructEnum that will be filled with data from j.
*  In case data is malformed or not convertable to StructEnum the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructEnum& p);
/** Function that converts json formated data into StructEnum
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructEnum/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructEnum& p);

/**
 * @brief Overloads the << operator to allow printing of StructEnum objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructEnum object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructEnum& obj);

/** Function that converts json formated data into StructBoolWithArray.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructBoolWithArray that will be filled with data from j.
*  In case data is malformed or not convertable to StructBoolWithArray the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructBoolWithArray& p);
/** Function that converts json formated data into StructBoolWithArray
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructBoolWithArray/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructBoolWithArray& p);

/**
 * @brief Overloads the << operator to allow printing of StructBoolWithArray objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructBoolWithArray object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructBoolWithArray& obj);

/** Function that converts json formated data into StructIntWithArray.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructIntWithArray that will be filled with data from j.
*  In case data is malformed or not convertable to StructIntWithArray the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructIntWithArray& p);
/** Function that converts json formated data into StructIntWithArray
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructIntWithArray/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructIntWithArray& p);

/**
 * @brief Overloads the << operator to allow printing of StructIntWithArray objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructIntWithArray object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructIntWithArray& obj);

/** Function that converts json formated data into StructFloatWithArray.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructFloatWithArray that will be filled with data from j.
*  In case data is malformed or not convertable to StructFloatWithArray the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructFloatWithArray& p);
/** Function that converts json formated data into StructFloatWithArray
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructFloatWithArray/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructFloatWithArray& p);

/**
 * @brief Overloads the << operator to allow printing of StructFloatWithArray objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructFloatWithArray object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructFloatWithArray& obj);

/** Function that converts json formated data into StructStringWithArray.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructStringWithArray that will be filled with data from j.
*  In case data is malformed or not convertable to StructStringWithArray the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructStringWithArray& p);
/** Function that converts json formated data into StructStringWithArray
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructStringWithArray/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructStringWithArray& p);

/**
 * @brief Overloads the << operator to allow printing of StructStringWithArray objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructStringWithArray object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructStringWithArray& obj);

/** Function that converts json formated data into StructStructWithArray.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructStructWithArray that will be filled with data from j.
*  In case data is malformed or not convertable to StructStructWithArray the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructStructWithArray& p);
/** Function that converts json formated data into StructStructWithArray
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructStructWithArray/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructStructWithArray& p);

/**
 * @brief Overloads the << operator to allow printing of StructStructWithArray objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructStructWithArray object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructStructWithArray& obj);

/** Function that converts json formated data into StructEnumWithArray.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p StructEnumWithArray that will be filled with data from j.
*  In case data is malformed or not convertable to StructEnumWithArray the function will throw.
*/
void TEST_TESTBED1_EXPORT from_json(const nlohmann::json& j, StructEnumWithArray& p);
/** Function that converts json formated data into StructEnumWithArray
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input StructEnumWithArray/'}
' from which json data will be filled
*/
void TEST_TESTBED1_EXPORT to_json(nlohmann::json& j, const StructEnumWithArray& p);

/**
 * @brief Overloads the << operator to allow printing of StructEnumWithArray objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The StructEnumWithArray object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED1_EXPORT std::ostream& operator<<(std::ostream& os, const StructEnumWithArray& obj);

} // namespace Testbed1
} // namespace Test
