

#include "tb_names/generated/core/names.threadsafedecorator.h"

using namespace Test::TbNames;
NamEsThreadSafeDecorator::NamEsThreadSafeDecorator(std::shared_ptr<INamEs> impl)
    : m_impl(impl)
{
}
void NamEsThreadSafeDecorator::sOME_FUNCTION(bool SOME_PARAM)
{
    return m_impl->sOME_FUNCTION(SOME_PARAM);
}

std::future<void> NamEsThreadSafeDecorator::sOME_FUNCTIONAsync(bool SOME_PARAM)
{
    return m_impl->sOME_FUNCTIONAsync(SOME_PARAM);
}
void NamEsThreadSafeDecorator::some_Function2(bool Some_Param)
{
    return m_impl->some_Function2(Some_Param);
}

std::future<void> NamEsThreadSafeDecorator::some_Function2Async(bool Some_Param)
{
    return m_impl->some_Function2Async(Some_Param);
}
void NamEsThreadSafeDecorator::setSwitch(bool Switch)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_switchMutex);
    m_impl->setSwitch(Switch);
}

bool NamEsThreadSafeDecorator::getSwitch() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_switchMutex);
    return m_impl->getSwitch();
}
void NamEsThreadSafeDecorator::setSomeProperty(int SOME_PROPERTY)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_somePropertyMutex);
    m_impl->setSomeProperty(SOME_PROPERTY);
}

int NamEsThreadSafeDecorator::getSomeProperty() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_somePropertyMutex);
    return m_impl->getSomeProperty();
}
void NamEsThreadSafeDecorator::setSomePoperty2(int Some_Poperty2)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_somePoperty2Mutex);
    m_impl->setSomePoperty2(Some_Poperty2);
}

int NamEsThreadSafeDecorator::getSomePoperty2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_somePoperty2Mutex);
    return m_impl->getSomePoperty2();
}
void NamEsThreadSafeDecorator::setEnumProperty(Enum_With_Under_scoresEnum enum_property)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_enumPropertyMutex);
    m_impl->setEnumProperty(enum_property);
}

Enum_With_Under_scoresEnum NamEsThreadSafeDecorator::getEnumProperty() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_enumPropertyMutex);
    return m_impl->getEnumProperty();
}

INamEsPublisher& NamEsThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}