

#include "tb_names/generated/monitor/names.tracedecorator.h"
#include "tb_names/generated/monitor/names.tracer.h"

using namespace Test::TbNames;
NamEsTraceDecorator::NamEsTraceDecorator(INamEs& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<Nam_EsTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
NamEsTraceDecorator::~NamEsTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<NamEsTraceDecorator> NamEsTraceDecorator::connect(INamEs& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<NamEsTraceDecorator>(new NamEsTraceDecorator(impl, tracer));
}
void NamEsTraceDecorator::sOME_FUNCTION(bool SOME_PARAM)
{
    m_tracer->trace_SOME_FUNCTION(SOME_PARAM);
    return m_impl.sOME_FUNCTION(SOME_PARAM);
}
std::future<void> NamEsTraceDecorator::sOME_FUNCTIONAsync(bool SOME_PARAM)
{
    m_tracer->trace_SOME_FUNCTION(SOME_PARAM);
    return m_impl.sOME_FUNCTIONAsync(SOME_PARAM);
}
void NamEsTraceDecorator::some_Function2(bool Some_Param)
{
    m_tracer->trace_Some_Function2(Some_Param);
    return m_impl.some_Function2(Some_Param);
}
std::future<void> NamEsTraceDecorator::some_Function2Async(bool Some_Param)
{
    m_tracer->trace_Some_Function2(Some_Param);
    return m_impl.some_Function2Async(Some_Param);
}
void NamEsTraceDecorator::setSwitch(bool Switch)
{
    m_impl.setSwitch(Switch);
}

bool NamEsTraceDecorator::getSwitch() const
{
    return m_impl.getSwitch();
}
void NamEsTraceDecorator::setSomeProperty(int SOME_PROPERTY)
{
    m_impl.setSomeProperty(SOME_PROPERTY);
}

int NamEsTraceDecorator::getSomeProperty() const
{
    return m_impl.getSomeProperty();
}
void NamEsTraceDecorator::setSomePoperty2(int Some_Poperty2)
{
    m_impl.setSomePoperty2(Some_Poperty2);
}

int NamEsTraceDecorator::getSomePoperty2() const
{
    return m_impl.getSomePoperty2();
}
void NamEsTraceDecorator::setEnumProperty(Enum_With_Under_scoresEnum enum_property)
{
    m_impl.setEnumProperty(enum_property);
}

Enum_With_Under_scoresEnum NamEsTraceDecorator::getEnumProperty() const
{
    return m_impl.getEnumProperty();
}
void NamEsTraceDecorator::onSomeSignal(bool SOME_PARAM)
{
    m_tracer->trace_SOME_SIGNAL(SOME_PARAM);
}

void NamEsTraceDecorator::onSomeSignal2(bool Some_Param)
{
    m_tracer->trace_Some_Signal2(Some_Param);
}

void NamEsTraceDecorator::onSwitchChanged(bool Switch)
{
    (void) Switch; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void NamEsTraceDecorator::onSomePropertyChanged(int SOME_PROPERTY)
{
    (void) SOME_PROPERTY; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void NamEsTraceDecorator::onSomePoperty2Changed(int Some_Poperty2)
{
    (void) Some_Poperty2; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void NamEsTraceDecorator::onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property)
{
    (void) enum_property; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



INamEsPublisher& NamEsTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
