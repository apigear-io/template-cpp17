

#include "tb_simple/implementation/nooperationsinterface.h"
#include "tb_simple/generated/core/nooperationsinterface.publisher.h"
#include "tb_simple/generated/core/nooperationsinterface.data.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSimple;

NoOperationsInterface::NoOperationsInterface()
    : m_publisher(std::make_unique<NoOperationsInterfacePublisher>())
{
}
NoOperationsInterface::~NoOperationsInterface()
{
}

void NoOperationsInterface::setPropBool(bool propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

bool NoOperationsInterface::getPropBool() const
{
    return m_data.m_propBool;
}

void NoOperationsInterface::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int NoOperationsInterface::getPropInt() const
{
    return m_data.m_propInt;
}

INoOperationsInterfacePublisher& NoOperationsInterface::_getPublisher() const
{
    return *m_publisher;
}
