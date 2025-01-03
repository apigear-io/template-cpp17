#pragma once

#include <cmath>
#include <type_traits>
#include <limits>
#include <algorithm>

namespace ApiGear {
namespace Utilities {

/**
 * @brief Checks if two double values are approximately equal.
 * Use this function instead of direct equality check to avoid issues related to floating-point precision.
 * @param a The first floating-point value to compare.
 * @param b The second floating-point value to compare.
 * @param relativeTolerance The maximum allowed relative difference between the values.
 *                          Used to compare non-zero close numbers. Default value is 1e-9
 * @param absoluteTolerance The maximum allowed absolute difference for numbers close to zero.
 *                          Default is std::numeric_limits<double>::epsilon() * 100, the smallest
 *                          representable difference for a double.
 * @return True if the two numbers are approximately equal within the specified tolerances, false otherwise.
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
bool fuzzyCompare(T a, T b, T relativeTolerance = static_cast<T>(1e-9), T absoluteTolerance = std::numeric_limits<T>::epsilon() * 100)
{
    auto diff = std::fabs(a - b);
    if (diff <= absoluteTolerance)
    {
        return true;
    }
    return diff <= relativeTolerance * std::max(std::fabs(a), std::fabs(b));
}
}} // namespace ApiGear::Utilities