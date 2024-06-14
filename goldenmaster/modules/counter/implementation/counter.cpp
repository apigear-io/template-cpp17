

#include "counter/implementation/counter.h"
#include "counter/generated/core/counter.publisher.h"
#include "counter/generated/core/counter.data.h"

using namespace Test::Counter;

Counter::Counter()
    : m_publisher(std::make_unique<CounterPublisher>())
{
}
Counter::~Counter()
{
}

void Counter::setVector(const Test::CustomTypes::Vector3D& vector)
{
    if (m_data.m_vector != vector) {
        m_data.m_vector = vector;
        m_publisher->publishVectorChanged(vector);
    }
}

const Test::CustomTypes::Vector3D& Counter::getVector() const
{
    return m_data.m_vector;
}

void Counter::setExternVector(const Eigen::Vector3f& extern_vector)
{
    if (m_data.m_extern_vector != extern_vector) {
        m_data.m_extern_vector = extern_vector;
        m_publisher->publishExternVectorChanged(extern_vector);
    }
}

const Eigen::Vector3f& Counter::getExternVector() const
{
    return m_data.m_extern_vector;
}

Eigen::Vector3f Counter::increment(const Eigen::Vector3f& vec)
{
    (void) vec; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Eigen::Vector3f(0,0,0);
}

std::future<Eigen::Vector3f> Counter::incrementAsync(const Eigen::Vector3f& vec)
{
    return std::async(std::launch::async, [this,
                    vec]()
        {
            return increment(vec);
        }
    );
}

Test::CustomTypes::Vector3D Counter::decrement(const Test::CustomTypes::Vector3D& vec)
{
    (void) vec; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Test::CustomTypes::Vector3D();
}

std::future<Test::CustomTypes::Vector3D> Counter::decrementAsync(const Test::CustomTypes::Vector3D& vec)
{
    return std::async(std::launch::async, [this,
                    vec]()
        {
            return decrement(vec);
        }
    );
}

ICounterPublisher& Counter::_getPublisher() const
{
    return *m_publisher;
}
