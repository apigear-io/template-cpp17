

#include "tb_struct_array/implementation/structarrayfieldinterface.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.publisher.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.data.h"

using namespace Test::TbStructArray;

StructArrayFieldInterface::StructArrayFieldInterface()
    : m_publisher(std::make_unique<StructArrayFieldInterfacePublisher>())
{
}
StructArrayFieldInterface::~StructArrayFieldInterface()
{
}

void StructArrayFieldInterface::setPropStructArray(const StructWithArrayOfStructs& propStructArray)
{
    if (m_data.m_propStructArray != propStructArray) {
        m_data.m_propStructArray = propStructArray;
        m_publisher->publishPropStructArrayChanged(propStructArray);
    }
}

const StructWithArrayOfStructs& StructArrayFieldInterface::getPropStructArray() const
{
    return m_data.m_propStructArray;
}

void StructArrayFieldInterface::setPropEnumArray(const StructWithArrayOfEnums& propEnumArray)
{
    if (m_data.m_propEnumArray != propEnumArray) {
        m_data.m_propEnumArray = propEnumArray;
        m_publisher->publishPropEnumArrayChanged(propEnumArray);
    }
}

const StructWithArrayOfEnums& StructArrayFieldInterface::getPropEnumArray() const
{
    return m_data.m_propEnumArray;
}

void StructArrayFieldInterface::setPropIntArray(const StructWithArrayOfInts& propIntArray)
{
    if (m_data.m_propIntArray != propIntArray) {
        m_data.m_propIntArray = propIntArray;
        m_publisher->publishPropIntArrayChanged(propIntArray);
    }
}

const StructWithArrayOfInts& StructArrayFieldInterface::getPropIntArray() const
{
    return m_data.m_propIntArray;
}

void StructArrayFieldInterface::setPropMixed(const MixedStruct& propMixed)
{
    if (m_data.m_propMixed != propMixed) {
        m_data.m_propMixed = propMixed;
        m_publisher->publishPropMixedChanged(propMixed);
    }
}

const MixedStruct& StructArrayFieldInterface::getPropMixed() const
{
    return m_data.m_propMixed;
}

MixedStruct StructArrayFieldInterface::funcMixed(const MixedStruct& paramMixed)
{
    (void) paramMixed; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return MixedStruct();
}

std::future<MixedStruct> StructArrayFieldInterface::funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramMixed]()
        {auto result = funcMixed(paramMixed);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

StructWithArrayOfStructs StructArrayFieldInterface::funcStructArray(const StructWithArrayOfStructs& paramPoints)
{
    (void) paramPoints; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return StructWithArrayOfStructs();
}

std::future<StructWithArrayOfStructs> StructArrayFieldInterface::funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramPoints]()
        {auto result = funcStructArray(paramPoints);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

IStructArrayFieldInterfacePublisher& StructArrayFieldInterface::_getPublisher() const
{
    return *m_publisher;
}
