

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

void Counter::setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    if (m_data.m_vectorArray != vectorArray) {
        m_data.m_vectorArray = vectorArray;
        m_publisher->publishVectorArrayChanged(vectorArray);
    }
}

const std::list<Test::CustomTypes::Vector3D>& Counter::getVectorArray() const
{
    return m_data.m_vectorArray;
}

void Counter::setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    if (m_data.m_extern_vectorArray != extern_vectorArray) {
        m_data.m_extern_vectorArray = extern_vectorArray;
        m_publisher->publishExternVectorArrayChanged(extern_vectorArray);
    }
}

const std::list<Eigen::Vector3f>& Counter::getExternVectorArray() const
{
    return m_data.m_extern_vectorArray;
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

std::list<Eigen::Vector3f> Counter::incrementArray(const std::list<Eigen::Vector3f>& vec)
{
    (void) vec; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<Eigen::Vector3f>();
}

std::future<std::list<Eigen::Vector3f>> Counter::incrementArrayAsync(const std::list<Eigen::Vector3f>& vec)
{
    return std::async(std::launch::async, [this,
                    vec]()
        {
            return incrementArray(vec);
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

std::list<Test::CustomTypes::Vector3D> Counter::decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    (void) vec; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<Test::CustomTypes::Vector3D>();
}

std::future<std::list<Test::CustomTypes::Vector3D>> Counter::decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    return std::async(std::launch::async, [this,
                    vec]()
        {
            return decrementArray(vec);
        }
    );
}

ICounterPublisher& Counter::_getPublisher() const
{
    return *m_publisher;
}
