
#pragma once
#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbStructArray {

class StructArrayFieldInterfaceTracer;

class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfaceTraceDecorator : public IStructArrayFieldInterface, public IStructArrayFieldInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The StructArrayFieldInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit StructArrayFieldInterfaceTraceDecorator(IStructArrayFieldInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the StructArrayFieldInterfaceTraceDecorator object.
    * @param impl The StructArrayFieldInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<StructArrayFieldInterfaceTraceDecorator> connect(IStructArrayFieldInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~StructArrayFieldInterfaceTraceDecorator();

    /** Traces funcMixed and forwards call to StructArrayFieldInterface implementation. */
    MixedStruct funcMixed(const MixedStruct& paramMixed) override;
    /** Traces funcMixed and forwards call to StructArrayFieldInterface implementation. */
    std::future<MixedStruct> funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback = nullptr) override;
    
    /** Traces funcStructArray and forwards call to StructArrayFieldInterface implementation. */
    StructWithArrayOfStructs funcStructArray(const StructWithArrayOfStructs& paramPoints) override;
    /** Traces funcStructArray and forwards call to StructArrayFieldInterface implementation. */
    std::future<StructWithArrayOfStructs> funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback = nullptr) override;
    
    /** Forwards call to StructArrayFieldInterface implementation. */
    void setPropStructArray(const StructWithArrayOfStructs& propStructArray) override;
    /** Forwards call to StructArrayFieldInterface implementation. */
    const StructWithArrayOfStructs& getPropStructArray() const override;
    
    /** Forwards call to StructArrayFieldInterface implementation. */
    void setPropEnumArray(const StructWithArrayOfEnums& propEnumArray) override;
    /** Forwards call to StructArrayFieldInterface implementation. */
    const StructWithArrayOfEnums& getPropEnumArray() const override;
    
    /** Forwards call to StructArrayFieldInterface implementation. */
    void setPropIntArray(const StructWithArrayOfInts& propIntArray) override;
    /** Forwards call to StructArrayFieldInterface implementation. */
    const StructWithArrayOfInts& getPropIntArray() const override;
    
    /** Forwards call to StructArrayFieldInterface implementation. */
    void setPropMixed(const MixedStruct& propMixed) override;
    /** Forwards call to StructArrayFieldInterface implementation. */
    const MixedStruct& getPropMixed() const override;
    
    /**
    Traces sigMixed emission.
    */
    void onSigMixed(const MixedStruct& paramMixed) override;
    /**
    Traces sigStructArray emission.
    */
    void onSigStructArray(const StructWithArrayOfStructs& paramPoints) override;
    /**
    Traces propStructArray changed.
    */
    void onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray) override;
    /**
    Traces propEnumArray changed.
    */
    void onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray) override;
    /**
    Traces propIntArray changed.
    */
    void onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray) override;
    /**
    Traces propMixed changed.
    */
    void onPropMixedChanged(const MixedStruct& propMixed) override;

    /**
    * Access to a publisher, use it to subscribe for StructArrayFieldInterface changes and signal emission.
    * @return The publisher for StructArrayFieldInterface.
    */
    IStructArrayFieldInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given StructArrayFieldInterface object. */
    std::unique_ptr<StructArrayFieldInterfaceTracer> m_tracer;
    /** The StructArrayFieldInterface object which is traced */
    IStructArrayFieldInterface& m_impl;
};
} // namespace TbStructArray
} // namespace Test
