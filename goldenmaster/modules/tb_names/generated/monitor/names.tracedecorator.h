
#pragma once
#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbNames {

class Nam_EsTracer;

class TEST_TB_NAMES_EXPORT NamEsTraceDecorator : public INamEs, public INamEsSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The Nam_Es object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit NamEsTraceDecorator(INamEs& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the NamEsTraceDecorator object.
    * @param impl The Nam_Es object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<NamEsTraceDecorator> connect(INamEs& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~NamEsTraceDecorator();

    /** Traces SOME_FUNCTION and forwards call to Nam_Es implementation. */
    void sOME_FUNCTION(bool SOME_PARAM) override;
    /** Traces SOME_FUNCTION and forwards call to Nam_Es implementation. */
    std::future<void> sOME_FUNCTIONAsync(bool SOME_PARAM) override;
    
    /** Traces Some_Function2 and forwards call to Nam_Es implementation. */
    void some_Function2(bool Some_Param) override;
    /** Traces Some_Function2 and forwards call to Nam_Es implementation. */
    std::future<void> some_Function2Async(bool Some_Param) override;
    
    /** Forwards call to Nam_Es implementation. */
    void setSwitch(bool Switch) override;
    /** Forwards call to Nam_Es implementation. */
    bool getSwitch() const override;
    
    /** Forwards call to Nam_Es implementation. */
    void setSomeProperty(int SOME_PROPERTY) override;
    /** Forwards call to Nam_Es implementation. */
    int getSomeProperty() const override;
    
    /** Forwards call to Nam_Es implementation. */
    void setSomePoperty2(int Some_Poperty2) override;
    /** Forwards call to Nam_Es implementation. */
    int getSomePoperty2() const override;
    
    /** Forwards call to Nam_Es implementation. */
    void setEnumProperty(Enum_With_Under_scoresEnum enum_property) override;
    /** Forwards call to Nam_Es implementation. */
    Enum_With_Under_scoresEnum getEnumProperty() const override;
    
    /**
    Traces SOME_SIGNAL emission.
    */
    void onSomeSignal(bool SOME_PARAM) override;
    /**
    Traces Some_Signal2 emission.
    */
    void onSomeSignal2(bool Some_Param) override;
    /**
    Traces Switch changed.
    */
    void onSwitchChanged(bool Switch) override;
    /**
    Traces SOME_PROPERTY changed.
    */
    void onSomePropertyChanged(int SOME_PROPERTY) override;
    /**
    Traces Some_Poperty2 changed.
    */
    void onSomePoperty2Changed(int Some_Poperty2) override;
    /**
    Traces enum_property changed.
    */
    void onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property) override;

    /**
    * Access to a publisher, use it to subscribe for Nam_Es changes and signal emission.
    * @return The publisher for Nam_Es.
    */
    INamEsPublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given Nam_Es object. */
    std::unique_ptr<Nam_EsTracer> m_tracer;
    /** The Nam_Es object which is traced */
    INamEs& m_impl;
};
} // namespace TbNames
} // namespace Test
