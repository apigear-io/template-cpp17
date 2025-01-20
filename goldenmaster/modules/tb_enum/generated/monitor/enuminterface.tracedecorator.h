
#pragma once
#include "tb_enum/generated/api/tb_enum.h"
#include "tb_enum/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbEnum {

class EnumInterfaceTracer;

class TEST_TB_ENUM_EXPORT EnumInterfaceTraceDecorator : public IEnumInterface, public IEnumInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The EnumInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit EnumInterfaceTraceDecorator(IEnumInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the EnumInterfaceTraceDecorator object.
    * @param impl The EnumInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<EnumInterfaceTraceDecorator> connect(IEnumInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~EnumInterfaceTraceDecorator();

    /** Traces func0 and forwards call to EnumInterface implementation. */
    Enum0Enum func0(Enum0Enum param0) override;
    /** Traces func0 and forwards call to EnumInterface implementation. */
    std::future<Enum0Enum> func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback = nullptr) override;
    
    /** Traces func1 and forwards call to EnumInterface implementation. */
    Enum1Enum func1(Enum1Enum param1) override;
    /** Traces func1 and forwards call to EnumInterface implementation. */
    std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) override;
    
    /** Traces func2 and forwards call to EnumInterface implementation. */
    Enum2Enum func2(Enum2Enum param2) override;
    /** Traces func2 and forwards call to EnumInterface implementation. */
    std::future<Enum2Enum> func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback = nullptr) override;
    
    /** Traces func3 and forwards call to EnumInterface implementation. */
    Enum3Enum func3(Enum3Enum param3) override;
    /** Traces func3 and forwards call to EnumInterface implementation. */
    std::future<Enum3Enum> func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback = nullptr) override;
    
    /** Forwards call to EnumInterface implementation. */
    void setProp0(Enum0Enum prop0) override;
    /** Forwards call to EnumInterface implementation. */
    Enum0Enum getProp0() const override;
    
    /** Forwards call to EnumInterface implementation. */
    void setProp1(Enum1Enum prop1) override;
    /** Forwards call to EnumInterface implementation. */
    Enum1Enum getProp1() const override;
    
    /** Forwards call to EnumInterface implementation. */
    void setProp2(Enum2Enum prop2) override;
    /** Forwards call to EnumInterface implementation. */
    Enum2Enum getProp2() const override;
    
    /** Forwards call to EnumInterface implementation. */
    void setProp3(Enum3Enum prop3) override;
    /** Forwards call to EnumInterface implementation. */
    Enum3Enum getProp3() const override;
    
    /**
    Traces sig0 emission.
    */
    void onSig0(Enum0Enum param0) override;
    /**
    Traces sig1 emission.
    */
    void onSig1(Enum1Enum param1) override;
    /**
    Traces sig2 emission.
    */
    void onSig2(Enum2Enum param2) override;
    /**
    Traces sig3 emission.
    */
    void onSig3(Enum3Enum param3) override;
    /**
    Traces prop0 changed.
    */
    void onProp0Changed(Enum0Enum prop0) override;
    /**
    Traces prop1 changed.
    */
    void onProp1Changed(Enum1Enum prop1) override;
    /**
    Traces prop2 changed.
    */
    void onProp2Changed(Enum2Enum prop2) override;
    /**
    Traces prop3 changed.
    */
    void onProp3Changed(Enum3Enum prop3) override;

    /**
    * Access to a publisher, use it to subscribe for EnumInterface changes and signal emission.
    * @return The publisher for EnumInterface.
    */
    IEnumInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given EnumInterface object. */
    std::unique_ptr<EnumInterfaceTracer> m_tracer;
    /** The EnumInterface object which is traced */
    IEnumInterface& m_impl;
};
} // namespace TbEnum
} // namespace Test
