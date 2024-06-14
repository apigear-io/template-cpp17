#pragma once

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif
#include <nlohmann/json.hpp>
#include "extern_types/generated/api/datastructs.api.h"
#include "extern_types/generated/api/common.h"

// do the specialization of the adl_serializer for the in the nlohmann namespace
// we do not want to modify the external namespace
namespace nlohmann {

    template <>
    struct TEST_EXTERN_TYPES_EXPORT adl_serializer<Eigen::Vector3f> {
        static Eigen::Vector3f from_json(const json& j) {
            (void) j;
            // Do deserialization here, e.g.
            //return {j.template get<int>()};
            return {};
        }

        static void to_json(json& j, Eigen::Vector3f t) {
            (void) j;
            (void) t;
            // Do serialization here, e.g.
            // j = t.i;
        }
    };

} // namespace nlohmann
