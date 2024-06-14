
#include "testbed2/implementation/manyparaminterface.h"
#include "testbed2/generated/monitor/manyparaminterface.tracedecorator.h"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "testbed2/generated/monitor/nestedstruct1interface.tracedecorator.h"
#include "testbed2/implementation/nestedstruct2interface.h"
#include "testbed2/generated/monitor/nestedstruct2interface.tracedecorator.h"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/monitor/nestedstruct3interface.tracedecorator.h"
#include "tb_enum/implementation/enuminterface.h"
#include "tb_enum/generated/monitor/enuminterface.tracedecorator.h"
#include "tb_same1/implementation/samestruct1interface.h"
#include "tb_same1/generated/monitor/samestruct1interface.tracedecorator.h"
#include "tb_same1/implementation/samestruct2interface.h"
#include "tb_same1/generated/monitor/samestruct2interface.tracedecorator.h"
#include "tb_same1/implementation/sameenum1interface.h"
#include "tb_same1/generated/monitor/sameenum1interface.tracedecorator.h"
#include "tb_same1/implementation/sameenum2interface.h"
#include "tb_same1/generated/monitor/sameenum2interface.tracedecorator.h"
#include "tb_same2/implementation/samestruct1interface.h"
#include "tb_same2/generated/monitor/samestruct1interface.tracedecorator.h"
#include "tb_same2/implementation/samestruct2interface.h"
#include "tb_same2/generated/monitor/samestruct2interface.tracedecorator.h"
#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/monitor/sameenum1interface.tracedecorator.h"
#include "tb_same2/implementation/sameenum2interface.h"
#include "tb_same2/generated/monitor/sameenum2interface.tracedecorator.h"
#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/monitor/voidinterface.tracedecorator.h"
#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/monitor/simpleinterface.tracedecorator.h"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/monitor/simplearrayinterface.tracedecorator.h"
#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/monitor/nopropertiesinterface.tracedecorator.h"
#include "tb_simple/implementation/nooperationsinterface.h"
#include "tb_simple/generated/monitor/nooperationsinterface.tracedecorator.h"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/monitor/nosignalsinterface.tracedecorator.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/monitor/structinterface.tracedecorator.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/monitor/structarrayinterface.tracedecorator.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/monitor/names.tracedecorator.h"
#include "counter/implementation/counter.h"
#include "counter/generated/monitor/counter.tracedecorator.h"
#include "apigear/tracer/tracer.h"

using namespace Test;

int main(){
    ApiGear::PocoImpl::Tracer tracer;
    tracer.connect("http://localhost:5555", "testExampleApp");
    std::unique_ptr<Testbed2::IManyParamInterface> testTestbed2ManyParamInterface = std::make_unique<Testbed2::ManyParamInterface>();
    std::unique_ptr<Testbed2::IManyParamInterface> testTestbed2ManyParamInterfaceTraceDecorator = Testbed2::ManyParamInterfaceTraceDecorator::connect(*testTestbed2ManyParamInterface, tracer);
    std::unique_ptr<Testbed2::INestedStruct1Interface> testTestbed2NestedStruct1Interface = std::make_unique<Testbed2::NestedStruct1Interface>();
    std::unique_ptr<Testbed2::INestedStruct1Interface> testTestbed2NestedStruct1InterfaceTraceDecorator = Testbed2::NestedStruct1InterfaceTraceDecorator::connect(*testTestbed2NestedStruct1Interface, tracer);
    std::unique_ptr<Testbed2::INestedStruct2Interface> testTestbed2NestedStruct2Interface = std::make_unique<Testbed2::NestedStruct2Interface>();
    std::unique_ptr<Testbed2::INestedStruct2Interface> testTestbed2NestedStruct2InterfaceTraceDecorator = Testbed2::NestedStruct2InterfaceTraceDecorator::connect(*testTestbed2NestedStruct2Interface, tracer);
    std::unique_ptr<Testbed2::INestedStruct3Interface> testTestbed2NestedStruct3Interface = std::make_unique<Testbed2::NestedStruct3Interface>();
    std::unique_ptr<Testbed2::INestedStruct3Interface> testTestbed2NestedStruct3InterfaceTraceDecorator = Testbed2::NestedStruct3InterfaceTraceDecorator::connect(*testTestbed2NestedStruct3Interface, tracer);
    std::unique_ptr<TbEnum::IEnumInterface> testTbEnumEnumInterface = std::make_unique<TbEnum::EnumInterface>();
    std::unique_ptr<TbEnum::IEnumInterface> testTbEnumEnumInterfaceTraceDecorator = TbEnum::EnumInterfaceTraceDecorator::connect(*testTbEnumEnumInterface, tracer);
    std::unique_ptr<TbSame1::ISameStruct1Interface> testTbSame1SameStruct1Interface = std::make_unique<TbSame1::SameStruct1Interface>();
    std::unique_ptr<TbSame1::ISameStruct1Interface> testTbSame1SameStruct1InterfaceTraceDecorator = TbSame1::SameStruct1InterfaceTraceDecorator::connect(*testTbSame1SameStruct1Interface, tracer);
    std::unique_ptr<TbSame1::ISameStruct2Interface> testTbSame1SameStruct2Interface = std::make_unique<TbSame1::SameStruct2Interface>();
    std::unique_ptr<TbSame1::ISameStruct2Interface> testTbSame1SameStruct2InterfaceTraceDecorator = TbSame1::SameStruct2InterfaceTraceDecorator::connect(*testTbSame1SameStruct2Interface, tracer);
    std::unique_ptr<TbSame1::ISameEnum1Interface> testTbSame1SameEnum1Interface = std::make_unique<TbSame1::SameEnum1Interface>();
    std::unique_ptr<TbSame1::ISameEnum1Interface> testTbSame1SameEnum1InterfaceTraceDecorator = TbSame1::SameEnum1InterfaceTraceDecorator::connect(*testTbSame1SameEnum1Interface, tracer);
    std::unique_ptr<TbSame1::ISameEnum2Interface> testTbSame1SameEnum2Interface = std::make_unique<TbSame1::SameEnum2Interface>();
    std::unique_ptr<TbSame1::ISameEnum2Interface> testTbSame1SameEnum2InterfaceTraceDecorator = TbSame1::SameEnum2InterfaceTraceDecorator::connect(*testTbSame1SameEnum2Interface, tracer);
    std::unique_ptr<TbSame2::ISameStruct1Interface> testTbSame2SameStruct1Interface = std::make_unique<TbSame2::SameStruct1Interface>();
    std::unique_ptr<TbSame2::ISameStruct1Interface> testTbSame2SameStruct1InterfaceTraceDecorator = TbSame2::SameStruct1InterfaceTraceDecorator::connect(*testTbSame2SameStruct1Interface, tracer);
    std::unique_ptr<TbSame2::ISameStruct2Interface> testTbSame2SameStruct2Interface = std::make_unique<TbSame2::SameStruct2Interface>();
    std::unique_ptr<TbSame2::ISameStruct2Interface> testTbSame2SameStruct2InterfaceTraceDecorator = TbSame2::SameStruct2InterfaceTraceDecorator::connect(*testTbSame2SameStruct2Interface, tracer);
    std::unique_ptr<TbSame2::ISameEnum1Interface> testTbSame2SameEnum1Interface = std::make_unique<TbSame2::SameEnum1Interface>();
    std::unique_ptr<TbSame2::ISameEnum1Interface> testTbSame2SameEnum1InterfaceTraceDecorator = TbSame2::SameEnum1InterfaceTraceDecorator::connect(*testTbSame2SameEnum1Interface, tracer);
    std::unique_ptr<TbSame2::ISameEnum2Interface> testTbSame2SameEnum2Interface = std::make_unique<TbSame2::SameEnum2Interface>();
    std::unique_ptr<TbSame2::ISameEnum2Interface> testTbSame2SameEnum2InterfaceTraceDecorator = TbSame2::SameEnum2InterfaceTraceDecorator::connect(*testTbSame2SameEnum2Interface, tracer);
    std::unique_ptr<TbSimple::IVoidInterface> testTbSimpleVoidInterface = std::make_unique<TbSimple::VoidInterface>();
    std::unique_ptr<TbSimple::IVoidInterface> testTbSimpleVoidInterfaceTraceDecorator = TbSimple::VoidInterfaceTraceDecorator::connect(*testTbSimpleVoidInterface, tracer);
    std::unique_ptr<TbSimple::ISimpleInterface> testTbSimpleSimpleInterface = std::make_unique<TbSimple::SimpleInterface>();
    std::unique_ptr<TbSimple::ISimpleInterface> testTbSimpleSimpleInterfaceTraceDecorator = TbSimple::SimpleInterfaceTraceDecorator::connect(*testTbSimpleSimpleInterface, tracer);
    std::unique_ptr<TbSimple::ISimpleArrayInterface> testTbSimpleSimpleArrayInterface = std::make_unique<TbSimple::SimpleArrayInterface>();
    std::unique_ptr<TbSimple::ISimpleArrayInterface> testTbSimpleSimpleArrayInterfaceTraceDecorator = TbSimple::SimpleArrayInterfaceTraceDecorator::connect(*testTbSimpleSimpleArrayInterface, tracer);
    std::unique_ptr<TbSimple::INoPropertiesInterface> testTbSimpleNoPropertiesInterface = std::make_unique<TbSimple::NoPropertiesInterface>();
    std::unique_ptr<TbSimple::INoPropertiesInterface> testTbSimpleNoPropertiesInterfaceTraceDecorator = TbSimple::NoPropertiesInterfaceTraceDecorator::connect(*testTbSimpleNoPropertiesInterface, tracer);
    std::unique_ptr<TbSimple::INoOperationsInterface> testTbSimpleNoOperationsInterface = std::make_unique<TbSimple::NoOperationsInterface>();
    std::unique_ptr<TbSimple::INoOperationsInterface> testTbSimpleNoOperationsInterfaceTraceDecorator = TbSimple::NoOperationsInterfaceTraceDecorator::connect(*testTbSimpleNoOperationsInterface, tracer);
    std::unique_ptr<TbSimple::INoSignalsInterface> testTbSimpleNoSignalsInterface = std::make_unique<TbSimple::NoSignalsInterface>();
    std::unique_ptr<TbSimple::INoSignalsInterface> testTbSimpleNoSignalsInterfaceTraceDecorator = TbSimple::NoSignalsInterfaceTraceDecorator::connect(*testTbSimpleNoSignalsInterface, tracer);
    std::unique_ptr<Testbed1::IStructInterface> testTestbed1StructInterface = std::make_unique<Testbed1::StructInterface>();
    std::unique_ptr<Testbed1::IStructInterface> testTestbed1StructInterfaceTraceDecorator = Testbed1::StructInterfaceTraceDecorator::connect(*testTestbed1StructInterface, tracer);
    std::unique_ptr<Testbed1::IStructArrayInterface> testTestbed1StructArrayInterface = std::make_unique<Testbed1::StructArrayInterface>();
    std::unique_ptr<Testbed1::IStructArrayInterface> testTestbed1StructArrayInterfaceTraceDecorator = Testbed1::StructArrayInterfaceTraceDecorator::connect(*testTestbed1StructArrayInterface, tracer);
    std::unique_ptr<TbNames::INamEs> testTbNamesNamEs = std::make_unique<TbNames::NamEs>();
    std::unique_ptr<TbNames::INamEs> testTbNamesNamEsTraceDecorator = TbNames::NamEsTraceDecorator::connect(*testTbNamesNamEs, tracer);
    std::unique_ptr<Counter::ICounter> testCounterCounter = std::make_unique<Counter::Counter>();
    std::unique_ptr<Counter::ICounter> testCounterCounterTraceDecorator = Counter::CounterTraceDecorator::connect(*testCounterCounter, tracer);

    return 0;
}
