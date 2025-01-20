

#include "testbed2/generated/monitor/manyparaminterface.tracedecorator.h"
#include "testbed2/generated/monitor/manyparaminterface.tracer.h"

using namespace Test::Testbed2;
ManyParamInterfaceTraceDecorator::ManyParamInterfaceTraceDecorator(IManyParamInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<ManyParamInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
ManyParamInterfaceTraceDecorator::~ManyParamInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<ManyParamInterfaceTraceDecorator> ManyParamInterfaceTraceDecorator::connect(IManyParamInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<ManyParamInterfaceTraceDecorator>(new ManyParamInterfaceTraceDecorator(impl, tracer));
}
int ManyParamInterfaceTraceDecorator::func1(int param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<int> ManyParamInterfaceTraceDecorator::func1Async(int param1, std::function<void(int)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
int ManyParamInterfaceTraceDecorator::func2(int param1, int param2)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2(param1, param2);
}
std::future<int> ManyParamInterfaceTraceDecorator::func2Async(int param1, int param2, std::function<void(int)> callback)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2Async(param1, param2, callback);
}
int ManyParamInterfaceTraceDecorator::func3(int param1, int param2, int param3)
{
    m_tracer->trace_func3(param1, param2, param3);
    return m_impl.func3(param1, param2, param3);
}
std::future<int> ManyParamInterfaceTraceDecorator::func3Async(int param1, int param2, int param3, std::function<void(int)> callback)
{
    m_tracer->trace_func3(param1, param2, param3);
    return m_impl.func3Async(param1, param2, param3, callback);
}
int ManyParamInterfaceTraceDecorator::func4(int param1, int param2, int param3, int param4)
{
    m_tracer->trace_func4(param1, param2, param3, param4);
    return m_impl.func4(param1, param2, param3, param4);
}
std::future<int> ManyParamInterfaceTraceDecorator::func4Async(int param1, int param2, int param3, int param4, std::function<void(int)> callback)
{
    m_tracer->trace_func4(param1, param2, param3, param4);
    return m_impl.func4Async(param1, param2, param3, param4, callback);
}
void ManyParamInterfaceTraceDecorator::setProp1(int prop1)
{
    m_impl.setProp1(prop1);
}

int ManyParamInterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void ManyParamInterfaceTraceDecorator::setProp2(int prop2)
{
    m_impl.setProp2(prop2);
}

int ManyParamInterfaceTraceDecorator::getProp2() const
{
    return m_impl.getProp2();
}
void ManyParamInterfaceTraceDecorator::setProp3(int prop3)
{
    m_impl.setProp3(prop3);
}

int ManyParamInterfaceTraceDecorator::getProp3() const
{
    return m_impl.getProp3();
}
void ManyParamInterfaceTraceDecorator::setProp4(int prop4)
{
    m_impl.setProp4(prop4);
}

int ManyParamInterfaceTraceDecorator::getProp4() const
{
    return m_impl.getProp4();
}
void ManyParamInterfaceTraceDecorator::onSig1(int param1)
{
    m_tracer->trace_sig1(param1);
}

void ManyParamInterfaceTraceDecorator::onSig2(int param1, int param2)
{
    m_tracer->trace_sig2(param1, param2);
}

void ManyParamInterfaceTraceDecorator::onSig3(int param1, int param2, int param3)
{
    m_tracer->trace_sig3(param1, param2, param3);
}

void ManyParamInterfaceTraceDecorator::onSig4(int param1, int param2, int param3, int param4)
{
    m_tracer->trace_sig4(param1, param2, param3, param4);
}

void ManyParamInterfaceTraceDecorator::onProp1Changed(int prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void ManyParamInterfaceTraceDecorator::onProp2Changed(int prop2)
{
    (void) prop2; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void ManyParamInterfaceTraceDecorator::onProp3Changed(int prop3)
{
    (void) prop3; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void ManyParamInterfaceTraceDecorator::onProp4Changed(int prop4)
{
    (void) prop4; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



IManyParamInterfacePublisher& ManyParamInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
