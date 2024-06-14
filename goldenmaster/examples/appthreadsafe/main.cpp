
#include "testbed2/implementation/manyparaminterface.h"
#include "testbed2/generated/core/manyparaminterface.threadsafedecorator.h"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "testbed2/generated/core/nestedstruct1interface.threadsafedecorator.h"
#include "testbed2/implementation/nestedstruct2interface.h"
#include "testbed2/generated/core/nestedstruct2interface.threadsafedecorator.h"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/core/nestedstruct3interface.threadsafedecorator.h"
#include "tb_enum/implementation/enuminterface.h"
#include "tb_enum/generated/core/enuminterface.threadsafedecorator.h"
#include "tb_same1/implementation/samestruct1interface.h"
#include "tb_same1/generated/core/samestruct1interface.threadsafedecorator.h"
#include "tb_same1/implementation/samestruct2interface.h"
#include "tb_same1/generated/core/samestruct2interface.threadsafedecorator.h"
#include "tb_same1/implementation/sameenum1interface.h"
#include "tb_same1/generated/core/sameenum1interface.threadsafedecorator.h"
#include "tb_same1/implementation/sameenum2interface.h"
#include "tb_same1/generated/core/sameenum2interface.threadsafedecorator.h"
#include "tb_same2/implementation/samestruct1interface.h"
#include "tb_same2/generated/core/samestruct1interface.threadsafedecorator.h"
#include "tb_same2/implementation/samestruct2interface.h"
#include "tb_same2/generated/core/samestruct2interface.threadsafedecorator.h"
#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/core/sameenum1interface.threadsafedecorator.h"
#include "tb_same2/implementation/sameenum2interface.h"
#include "tb_same2/generated/core/sameenum2interface.threadsafedecorator.h"
#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/core/voidinterface.threadsafedecorator.h"
#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/core/simpleinterface.threadsafedecorator.h"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/core/simplearrayinterface.threadsafedecorator.h"
#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/core/nopropertiesinterface.threadsafedecorator.h"
#include "tb_simple/implementation/nooperationsinterface.h"
#include "tb_simple/generated/core/nooperationsinterface.threadsafedecorator.h"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/core/nosignalsinterface.threadsafedecorator.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/core/structinterface.threadsafedecorator.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/core/structarrayinterface.threadsafedecorator.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/core/names.threadsafedecorator.h"
#include "counter/implementation/counter.h"
#include "counter/generated/core/counter.threadsafedecorator.h"

void testTestbed2ManyParamInterface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<IManyParamInterface> testManyParamInterface = std::make_unique<ManyParamInterfaceThreadSafeDecorator>(std::make_shared<ManyParamInterface>());

    // Thread safe access
    auto l_prop1 = 0;
    l_prop1 = testManyParamInterface->getProp1();
    testManyParamInterface->setProp1(l_prop1);
    auto l_prop2 = 0;
    l_prop2 = testManyParamInterface->getProp2();
    testManyParamInterface->setProp2(l_prop2);
    auto l_prop3 = 0;
    l_prop3 = testManyParamInterface->getProp3();
    testManyParamInterface->setProp3(l_prop3);
    auto l_prop4 = 0;
    l_prop4 = testManyParamInterface->getProp4();
    testManyParamInterface->setProp4(l_prop4);
}

void testTestbed2NestedStruct1Interface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<INestedStruct1Interface> testNestedStruct1Interface = std::make_unique<NestedStruct1InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct1Interface>());

    // Thread safe access
    auto l_prop1 = NestedStruct1();
    l_prop1 = testNestedStruct1Interface->getProp1();
    testNestedStruct1Interface->setProp1(l_prop1);
}

void testTestbed2NestedStruct2Interface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<INestedStruct2Interface> testNestedStruct2Interface = std::make_unique<NestedStruct2InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct2Interface>());

    // Thread safe access
    auto l_prop1 = NestedStruct1();
    l_prop1 = testNestedStruct2Interface->getProp1();
    testNestedStruct2Interface->setProp1(l_prop1);
    auto l_prop2 = NestedStruct2();
    l_prop2 = testNestedStruct2Interface->getProp2();
    testNestedStruct2Interface->setProp2(l_prop2);
}

void testTestbed2NestedStruct3Interface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<INestedStruct3Interface> testNestedStruct3Interface = std::make_unique<NestedStruct3InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct3Interface>());

    // Thread safe access
    auto l_prop1 = NestedStruct1();
    l_prop1 = testNestedStruct3Interface->getProp1();
    testNestedStruct3Interface->setProp1(l_prop1);
    auto l_prop2 = NestedStruct2();
    l_prop2 = testNestedStruct3Interface->getProp2();
    testNestedStruct3Interface->setProp2(l_prop2);
    auto l_prop3 = NestedStruct3();
    l_prop3 = testNestedStruct3Interface->getProp3();
    testNestedStruct3Interface->setProp3(l_prop3);
}

void testTbEnumEnumInterface()
{
    using namespace Test::TbEnum;

    std::unique_ptr<IEnumInterface> testEnumInterface = std::make_unique<EnumInterfaceThreadSafeDecorator>(std::make_shared<EnumInterface>());

    // Thread safe access
    auto l_prop0 = Enum0Enum::value0;
    l_prop0 = testEnumInterface->getProp0();
    testEnumInterface->setProp0(l_prop0);
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testEnumInterface->getProp1();
    testEnumInterface->setProp1(l_prop1);
    auto l_prop2 = Enum2Enum::value2;
    l_prop2 = testEnumInterface->getProp2();
    testEnumInterface->setProp2(l_prop2);
    auto l_prop3 = Enum3Enum::value3;
    l_prop3 = testEnumInterface->getProp3();
    testEnumInterface->setProp3(l_prop3);
}

void testTbSame1SameStruct1Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameStruct1Interface> testSameStruct1Interface = std::make_unique<SameStruct1InterfaceThreadSafeDecorator>(std::make_shared<SameStruct1Interface>());

    // Thread safe access
    auto l_prop1 = Struct1();
    l_prop1 = testSameStruct1Interface->getProp1();
    testSameStruct1Interface->setProp1(l_prop1);
}

void testTbSame1SameStruct2Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameStruct2Interface> testSameStruct2Interface = std::make_unique<SameStruct2InterfaceThreadSafeDecorator>(std::make_shared<SameStruct2Interface>());

    // Thread safe access
    auto l_prop1 = Struct2();
    l_prop1 = testSameStruct2Interface->getProp1();
    testSameStruct2Interface->setProp1(l_prop1);
    auto l_prop2 = Struct2();
    l_prop2 = testSameStruct2Interface->getProp2();
    testSameStruct2Interface->setProp2(l_prop2);
}

void testTbSame1SameEnum1Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameEnum1Interface> testSameEnum1Interface = std::make_unique<SameEnum1InterfaceThreadSafeDecorator>(std::make_shared<SameEnum1Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum1Interface->getProp1();
    testSameEnum1Interface->setProp1(l_prop1);
}

void testTbSame1SameEnum2Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameEnum2Interface> testSameEnum2Interface = std::make_unique<SameEnum2InterfaceThreadSafeDecorator>(std::make_shared<SameEnum2Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum2Interface->getProp1();
    testSameEnum2Interface->setProp1(l_prop1);
    auto l_prop2 = Enum2Enum::value1;
    l_prop2 = testSameEnum2Interface->getProp2();
    testSameEnum2Interface->setProp2(l_prop2);
}

void testTbSame2SameStruct1Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameStruct1Interface> testSameStruct1Interface = std::make_unique<SameStruct1InterfaceThreadSafeDecorator>(std::make_shared<SameStruct1Interface>());

    // Thread safe access
    auto l_prop1 = Struct1();
    l_prop1 = testSameStruct1Interface->getProp1();
    testSameStruct1Interface->setProp1(l_prop1);
}

void testTbSame2SameStruct2Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameStruct2Interface> testSameStruct2Interface = std::make_unique<SameStruct2InterfaceThreadSafeDecorator>(std::make_shared<SameStruct2Interface>());

    // Thread safe access
    auto l_prop1 = Struct2();
    l_prop1 = testSameStruct2Interface->getProp1();
    testSameStruct2Interface->setProp1(l_prop1);
    auto l_prop2 = Struct2();
    l_prop2 = testSameStruct2Interface->getProp2();
    testSameStruct2Interface->setProp2(l_prop2);
}

void testTbSame2SameEnum1Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameEnum1Interface> testSameEnum1Interface = std::make_unique<SameEnum1InterfaceThreadSafeDecorator>(std::make_shared<SameEnum1Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum1Interface->getProp1();
    testSameEnum1Interface->setProp1(l_prop1);
}

void testTbSame2SameEnum2Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameEnum2Interface> testSameEnum2Interface = std::make_unique<SameEnum2InterfaceThreadSafeDecorator>(std::make_shared<SameEnum2Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum2Interface->getProp1();
    testSameEnum2Interface->setProp1(l_prop1);
    auto l_prop2 = Enum2Enum::value1;
    l_prop2 = testSameEnum2Interface->getProp2();
    testSameEnum2Interface->setProp2(l_prop2);
}

void testTbSimpleVoidInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<IVoidInterface> testVoidInterface = std::make_unique<VoidInterfaceThreadSafeDecorator>(std::make_shared<VoidInterface>());

    // Thread safe access
}

void testTbSimpleSimpleInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<ISimpleInterface> testSimpleInterface = std::make_unique<SimpleInterfaceThreadSafeDecorator>(std::make_shared<SimpleInterface>());

    // Thread safe access
    auto l_propBool = false;
    l_propBool = testSimpleInterface->getPropBool();
    testSimpleInterface->setPropBool(l_propBool);
    auto l_propInt = 0;
    l_propInt = testSimpleInterface->getPropInt();
    testSimpleInterface->setPropInt(l_propInt);
    auto l_propInt32 = 0;
    l_propInt32 = testSimpleInterface->getPropInt32();
    testSimpleInterface->setPropInt32(l_propInt32);
    auto l_propInt64 = 0LL;
    l_propInt64 = testSimpleInterface->getPropInt64();
    testSimpleInterface->setPropInt64(l_propInt64);
    auto l_propFloat = 0.0f;
    l_propFloat = testSimpleInterface->getPropFloat();
    testSimpleInterface->setPropFloat(l_propFloat);
    auto l_propFloat32 = 0.0f;
    l_propFloat32 = testSimpleInterface->getPropFloat32();
    testSimpleInterface->setPropFloat32(l_propFloat32);
    auto l_propFloat64 = 0.0;
    l_propFloat64 = testSimpleInterface->getPropFloat64();
    testSimpleInterface->setPropFloat64(l_propFloat64);
    auto l_propString = std::string();
    l_propString = testSimpleInterface->getPropString();
    testSimpleInterface->setPropString(l_propString);
}

void testTbSimpleSimpleArrayInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<ISimpleArrayInterface> testSimpleArrayInterface = std::make_unique<SimpleArrayInterfaceThreadSafeDecorator>(std::make_shared<SimpleArrayInterface>());

    // Thread safe access
    auto l_propBool = std::list<bool>();
    l_propBool = testSimpleArrayInterface->getPropBool();
    testSimpleArrayInterface->setPropBool(l_propBool);
    auto l_propInt = std::list<int>();
    l_propInt = testSimpleArrayInterface->getPropInt();
    testSimpleArrayInterface->setPropInt(l_propInt);
    auto l_propInt32 = std::list<int32_t>();
    l_propInt32 = testSimpleArrayInterface->getPropInt32();
    testSimpleArrayInterface->setPropInt32(l_propInt32);
    auto l_propInt64 = std::list<int64_t>();
    l_propInt64 = testSimpleArrayInterface->getPropInt64();
    testSimpleArrayInterface->setPropInt64(l_propInt64);
    auto l_propFloat = std::list<float>();
    l_propFloat = testSimpleArrayInterface->getPropFloat();
    testSimpleArrayInterface->setPropFloat(l_propFloat);
    auto l_propFloat32 = std::list<float>();
    l_propFloat32 = testSimpleArrayInterface->getPropFloat32();
    testSimpleArrayInterface->setPropFloat32(l_propFloat32);
    auto l_propFloat64 = std::list<double>();
    l_propFloat64 = testSimpleArrayInterface->getPropFloat64();
    testSimpleArrayInterface->setPropFloat64(l_propFloat64);
    auto l_propString = std::list<std::string>();
    l_propString = testSimpleArrayInterface->getPropString();
    testSimpleArrayInterface->setPropString(l_propString);
    auto l_propReadOnlyString = std::string();
    l_propReadOnlyString = testSimpleArrayInterface->getPropReadOnlyString();
}

void testTbSimpleNoPropertiesInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<INoPropertiesInterface> testNoPropertiesInterface = std::make_unique<NoPropertiesInterfaceThreadSafeDecorator>(std::make_shared<NoPropertiesInterface>());

    // Thread safe access
}

void testTbSimpleNoOperationsInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<INoOperationsInterface> testNoOperationsInterface = std::make_unique<NoOperationsInterfaceThreadSafeDecorator>(std::make_shared<NoOperationsInterface>());

    // Thread safe access
    auto l_propBool = false;
    l_propBool = testNoOperationsInterface->getPropBool();
    testNoOperationsInterface->setPropBool(l_propBool);
    auto l_propInt = 0;
    l_propInt = testNoOperationsInterface->getPropInt();
    testNoOperationsInterface->setPropInt(l_propInt);
}

void testTbSimpleNoSignalsInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<INoSignalsInterface> testNoSignalsInterface = std::make_unique<NoSignalsInterfaceThreadSafeDecorator>(std::make_shared<NoSignalsInterface>());

    // Thread safe access
    auto l_propBool = false;
    l_propBool = testNoSignalsInterface->getPropBool();
    testNoSignalsInterface->setPropBool(l_propBool);
    auto l_propInt = 0;
    l_propInt = testNoSignalsInterface->getPropInt();
    testNoSignalsInterface->setPropInt(l_propInt);
}

void testTestbed1StructInterface()
{
    using namespace Test::Testbed1;

    std::unique_ptr<IStructInterface> testStructInterface = std::make_unique<StructInterfaceThreadSafeDecorator>(std::make_shared<StructInterface>());

    // Thread safe access
    auto l_propBool = StructBool();
    l_propBool = testStructInterface->getPropBool();
    testStructInterface->setPropBool(l_propBool);
    auto l_propInt = StructInt();
    l_propInt = testStructInterface->getPropInt();
    testStructInterface->setPropInt(l_propInt);
    auto l_propFloat = StructFloat();
    l_propFloat = testStructInterface->getPropFloat();
    testStructInterface->setPropFloat(l_propFloat);
    auto l_propString = StructString();
    l_propString = testStructInterface->getPropString();
    testStructInterface->setPropString(l_propString);
}

void testTestbed1StructArrayInterface()
{
    using namespace Test::Testbed1;

    std::unique_ptr<IStructArrayInterface> testStructArrayInterface = std::make_unique<StructArrayInterfaceThreadSafeDecorator>(std::make_shared<StructArrayInterface>());

    // Thread safe access
    auto l_propBool = std::list<StructBool>();
    l_propBool = testStructArrayInterface->getPropBool();
    testStructArrayInterface->setPropBool(l_propBool);
    auto l_propInt = std::list<StructInt>();
    l_propInt = testStructArrayInterface->getPropInt();
    testStructArrayInterface->setPropInt(l_propInt);
    auto l_propFloat = std::list<StructFloat>();
    l_propFloat = testStructArrayInterface->getPropFloat();
    testStructArrayInterface->setPropFloat(l_propFloat);
    auto l_propString = std::list<StructString>();
    l_propString = testStructArrayInterface->getPropString();
    testStructArrayInterface->setPropString(l_propString);
}

void testTbNamesNamEs()
{
    using namespace Test::TbNames;

    std::unique_ptr<INamEs> testNamEs = std::make_unique<NamEsThreadSafeDecorator>(std::make_shared<NamEs>());

    // Thread safe access
    auto l_switch = false;
    l_switch = testNamEs->getSwitch();
    testNamEs->setSwitch(l_switch);
    auto l_someProperty = 0;
    l_someProperty = testNamEs->getSomeProperty();
    testNamEs->setSomeProperty(l_someProperty);
    auto l_somePoperty2 = 0;
    l_somePoperty2 = testNamEs->getSomePoperty2();
    testNamEs->setSomePoperty2(l_somePoperty2);
}

void testCounterCounter()
{
    using namespace Test::Counter;

    std::unique_ptr<ICounter> testCounter = std::make_unique<CounterThreadSafeDecorator>(std::make_shared<Counter>());

    // Thread safe access
    auto l_vector = Test::CustomTypes::Vector3D();
    l_vector = testCounter->getVector();
    testCounter->setVector(l_vector);
    auto l_externVector = Eigen::Vector3f(0,0,0);
    l_externVector = testCounter->getExternVector();
    testCounter->setExternVector(l_externVector);
}


int main(){
    testTestbed2ManyParamInterface();
    testTestbed2NestedStruct1Interface();
    testTestbed2NestedStruct2Interface();
    testTestbed2NestedStruct3Interface();
    testTbEnumEnumInterface();
    testTbSame1SameStruct1Interface();
    testTbSame1SameStruct2Interface();
    testTbSame1SameEnum1Interface();
    testTbSame1SameEnum2Interface();
    testTbSame2SameStruct1Interface();
    testTbSame2SameStruct2Interface();
    testTbSame2SameEnum1Interface();
    testTbSame2SameEnum2Interface();
    testTbSimpleVoidInterface();
    testTbSimpleSimpleInterface();
    testTbSimpleSimpleArrayInterface();
    testTbSimpleNoPropertiesInterface();
    testTbSimpleNoOperationsInterface();
    testTbSimpleNoSignalsInterface();
    testTestbed1StructInterface();
    testTestbed1StructArrayInterface();
    testTbNamesNamEs();
    testCounterCounter();

    return 0;
}
