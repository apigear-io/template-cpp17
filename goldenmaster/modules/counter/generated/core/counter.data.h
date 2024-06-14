#pragma once

#include "counter/generated/api/counter.h"


namespace Test
{
namespace Counter
{

/**
* A helper structure for implementations of Counter. Stores all the properties.
*/
struct CounterData
{
    Test::CustomTypes::Vector3D m_vector {Test::CustomTypes::Vector3D()};
    Eigen::Vector3f m_extern_vector {Eigen::Vector3f(0,0,0)};
};

}
}