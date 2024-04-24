#pragma once

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif
#include <nlohmann/json.hpp>
#include "testbed2/generated/api/datastructs.api.h"
#include "testbed2/generated/api/common.h"

namespace Test {
namespace Testbed2 {
/** Function that converts json formated data into Struct1.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p Struct1 that will be filled with data from j.
*  In case data is malformed or not convertable to Struct1 the function will throw.
*/
void TEST_TESTBED2_EXPORT from_json(const nlohmann::json& j, Struct1& p);
/** Function that converts json formated data into Struct1
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input Struct1/'}
' from which json data will be filled
*/
void TEST_TESTBED2_EXPORT to_json(nlohmann::json& j, const Struct1& p);

/**
 * @brief Overloads the << operator to allow printing of Struct1 objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The Struct1 object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED2_EXPORT std::ostream& operator<<(std::ostream& os, const Struct1& obj);

/** Function that converts json formated data into Struct2.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p Struct2 that will be filled with data from j.
*  In case data is malformed or not convertable to Struct2 the function will throw.
*/
void TEST_TESTBED2_EXPORT from_json(const nlohmann::json& j, Struct2& p);
/** Function that converts json formated data into Struct2
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input Struct2/'}
' from which json data will be filled
*/
void TEST_TESTBED2_EXPORT to_json(nlohmann::json& j, const Struct2& p);

/**
 * @brief Overloads the << operator to allow printing of Struct2 objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The Struct2 object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED2_EXPORT std::ostream& operator<<(std::ostream& os, const Struct2& obj);

/** Function that converts json formated data into Struct3.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p Struct3 that will be filled with data from j.
*  In case data is malformed or not convertable to Struct3 the function will throw.
*/
void TEST_TESTBED2_EXPORT from_json(const nlohmann::json& j, Struct3& p);
/** Function that converts json formated data into Struct3
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input Struct3/'}
' from which json data will be filled
*/
void TEST_TESTBED2_EXPORT to_json(nlohmann::json& j, const Struct3& p);

/**
 * @brief Overloads the << operator to allow printing of Struct3 objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The Struct3 object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED2_EXPORT std::ostream& operator<<(std::ostream& os, const Struct3& obj);

/** Function that converts json formated data into Struct4.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p Struct4 that will be filled with data from j.
*  In case data is malformed or not convertable to Struct4 the function will throw.
*/
void TEST_TESTBED2_EXPORT from_json(const nlohmann::json& j, Struct4& p);
/** Function that converts json formated data into Struct4
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input Struct4/'}
' from which json data will be filled
*/
void TEST_TESTBED2_EXPORT to_json(nlohmann::json& j, const Struct4& p);

/**
 * @brief Overloads the << operator to allow printing of Struct4 objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The Struct4 object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED2_EXPORT std::ostream& operator<<(std::ostream& os, const Struct4& obj);

/** Function that converts json formated data into NestedStruct1.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p NestedStruct1 that will be filled with data from j.
*  In case data is malformed or not convertable to NestedStruct1 the function will throw.
*/
void TEST_TESTBED2_EXPORT from_json(const nlohmann::json& j, NestedStruct1& p);
/** Function that converts json formated data into NestedStruct1
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input NestedStruct1/'}
' from which json data will be filled
*/
void TEST_TESTBED2_EXPORT to_json(nlohmann::json& j, const NestedStruct1& p);

/**
 * @brief Overloads the << operator to allow printing of NestedStruct1 objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The NestedStruct1 object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED2_EXPORT std::ostream& operator<<(std::ostream& os, const NestedStruct1& obj);

/** Function that converts json formated data into NestedStruct2.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p NestedStruct2 that will be filled with data from j.
*  In case data is malformed or not convertable to NestedStruct2 the function will throw.
*/
void TEST_TESTBED2_EXPORT from_json(const nlohmann::json& j, NestedStruct2& p);
/** Function that converts json formated data into NestedStruct2
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input NestedStruct2/'}
' from which json data will be filled
*/
void TEST_TESTBED2_EXPORT to_json(nlohmann::json& j, const NestedStruct2& p);

/**
 * @brief Overloads the << operator to allow printing of NestedStruct2 objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The NestedStruct2 object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED2_EXPORT std::ostream& operator<<(std::ostream& os, const NestedStruct2& obj);

/** Function that converts json formated data into NestedStruct3.
* The functions signature must follow the nlohmann from_jason function rules.
* It is automatically called in usage j.get<class>();
* @param j an input json formated data
* @param p NestedStruct3 that will be filled with data from j.
*  In case data is malformed or not convertable to NestedStruct3 the function will throw.
*/
void TEST_TESTBED2_EXPORT from_json(const nlohmann::json& j, NestedStruct3& p);
/** Function that converts json formated data into NestedStruct3
* The functions signature must follow the nlohmann to_jason function rules.
* It is automatically called in usage j = p;
* @param j a json formated data that will be filled with data from p
* @param p an input NestedStruct3/'}
' from which json data will be filled
*/
void TEST_TESTBED2_EXPORT to_json(nlohmann::json& j, const NestedStruct3& p);

/**
 * @brief Overloads the << operator to allow printing of NestedStruct3 objects to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The NestedStruct3 object to be printed.
 * @return std::ostream& The modified output stream.
 */
TEST_TESTBED2_EXPORT std::ostream& operator<<(std::ostream& os, const NestedStruct3& obj);

} // namespace Testbed2
} // namespace Test
