
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed2 {

class ManyParamInterfaceTracer;

class TEST_TESTBED2_EXPORT ManyParamInterfaceTraceDecorator : public IManyParamInterface, public IManyParamInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The ManyParamInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit ManyParamInterfaceTraceDecorator(IManyParamInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the ManyParamInterfaceTraceDecorator object.
    * @param impl The ManyParamInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<ManyParamInterfaceTraceDecorator> connect(IManyParamInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~ManyParamInterfaceTraceDecorator();

    /** Traces func1 and forwards call to ManyParamInterface implementation. */
    int func1(int param1) override;
    /** Traces func1 and forwards call to ManyParamInterface implementation. */
    std::future<int> func1Async(int param1, std::function<void(int)> callback = nullptr) override;
    
    /** Traces func2 and forwards call to ManyParamInterface implementation. */
    int func2(int param1, int param2) override;
    /** Traces func2 and forwards call to ManyParamInterface implementation. */
    std::future<int> func2Async(int param1, int param2, std::function<void(int)> callback = nullptr) override;
    
    /** Traces func3 and forwards call to ManyParamInterface implementation. */
    int func3(int param1, int param2, int param3) override;
    /** Traces func3 and forwards call to ManyParamInterface implementation. */
    std::future<int> func3Async(int param1, int param2, int param3, std::function<void(int)> callback = nullptr) override;
    
    /** Traces func4 and forwards call to ManyParamInterface implementation. */
    int func4(int param1, int param2, int param3, int param4) override;
    /** Traces func4 and forwards call to ManyParamInterface implementation. */
    std::future<int> func4Async(int param1, int param2, int param3, int param4, std::function<void(int)> callback = nullptr) override;
    
    /** Forwards call to ManyParamInterface implementation. */
    void setProp1(int prop1) override;
    /** Forwards call to ManyParamInterface implementation. */
    int getProp1() const override;
    
    /** Forwards call to ManyParamInterface implementation. */
    void setProp2(int prop2) override;
    /** Forwards call to ManyParamInterface implementation. */
    int getProp2() const override;
    
    /** Forwards call to ManyParamInterface implementation. */
    void setProp3(int prop3) override;
    /** Forwards call to ManyParamInterface implementation. */
    int getProp3() const override;
    
    /** Forwards call to ManyParamInterface implementation. */
    void setProp4(int prop4) override;
    /** Forwards call to ManyParamInterface implementation. */
    int getProp4() const override;
    
    /**
    Traces sig1 emission.
    */
    void onSig1(int param1) override;
    /**
    Traces sig2 emission.
    */
    void onSig2(int param1, int param2) override;
    /**
    Traces sig3 emission.
    */
    void onSig3(int param1, int param2, int param3) override;
    /**
    Traces sig4 emission.
    */
    void onSig4(int param1, int param2, int param3, int param4) override;
    /**
    Traces prop1 changed.
    */
    void onProp1Changed(int prop1) override;
    /**
    Traces prop2 changed.
    */
    void onProp2Changed(int prop2) override;
    /**
    Traces prop3 changed.
    */
    void onProp3Changed(int prop3) override;
    /**
    Traces prop4 changed.
    */
    void onProp4Changed(int prop4) override;

    /**
    * Access to a publisher, use it to subscribe for ManyParamInterface changes and signal emission.
    * @return The publisher for ManyParamInterface.
    */
    IManyParamInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given ManyParamInterface object. */
    std::unique_ptr<ManyParamInterfaceTracer> m_tracer;
    /** The ManyParamInterface object which is traced */
    IManyParamInterface& m_impl;
};
} // namespace Testbed2
} // namespace Test
