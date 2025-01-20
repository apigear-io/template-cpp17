

#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/core/nosignalsinterface.publisher.h"
#include "tb_simple/generated/core/nosignalsinterface.data.h"

using namespace Test::TbSimple;

NoSignalsInterface::NoSignalsInterface()
    : m_publisher(std::make_unique<NoSignalsInterfacePublisher>())
{
}
NoSignalsInterface::~NoSignalsInterface()
{
}

void NoSignalsInterface::setPropBool(bool propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

bool NoSignalsInterface::getPropBool() const
{
    return m_data.m_propBool;
}

void NoSignalsInterface::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int NoSignalsInterface::getPropInt() const
{
    return m_data.m_propInt;
}

void NoSignalsInterface::funcVoid()
{
    // do business logic here
}

std::future<void> NoSignalsInterface::funcVoidAsync( std::function<void(void)> callback)
{
    return std::async(std::launch::async, [this, callback]()
        {funcVoid();
            if (callback)
            {
                callback();
            }
        }
    );
}

bool NoSignalsInterface::funcBool(bool paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return false;
}

std::future<bool> NoSignalsInterface::funcBoolAsync(bool paramBool, std::function<void(bool)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramBool]()
        {auto result = funcBool(paramBool);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

INoSignalsInterfacePublisher& NoSignalsInterface::_getPublisher() const
{
    return *m_publisher;
}
