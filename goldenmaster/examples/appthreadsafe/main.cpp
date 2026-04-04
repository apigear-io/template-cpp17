
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
#include "tb_simple/implementation/emptyinterface.h"
#include "tb_simple/generated/core/emptyinterface.threadsafedecorator.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/core/structinterface.threadsafedecorator.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/core/structarrayinterface.threadsafedecorator.h"
#include "testbed1/implementation/structarray2interface.h"
#include "testbed1/generated/core/structarray2interface.threadsafedecorator.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/core/names.threadsafedecorator.h"
#include "counter/implementation/counter.h"
#include "counter/generated/core/counter.threadsafedecorator.h"
#include "tb_struct_array/implementation/structarrayfieldinterface.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.threadsafedecorator.h"
#include <iostream>


void testTestbed2ManyParamInterface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<IManyParamInterface> testManyParamInterface = std::make_unique<ManyParamInterfaceThreadSafeDecorator>(std::make_shared<ManyParamInterface>());

    // Thread safe access
    auto l_prop1 = 0;
    l_prop1 = testManyParamInterface->getProp1();
    std::cout << "  ManyParamInterface::Prop1 retrieved" << std::endl;
    testManyParamInterface->setProp1(l_prop1);
    std::cout << "  ManyParamInterface::Prop1 set" << std::endl;
    auto l_prop2 = 0;
    l_prop2 = testManyParamInterface->getProp2();
    std::cout << "  ManyParamInterface::Prop2 retrieved" << std::endl;
    testManyParamInterface->setProp2(l_prop2);
    std::cout << "  ManyParamInterface::Prop2 set" << std::endl;
    auto l_prop3 = 0;
    l_prop3 = testManyParamInterface->getProp3();
    std::cout << "  ManyParamInterface::Prop3 retrieved" << std::endl;
    testManyParamInterface->setProp3(l_prop3);
    std::cout << "  ManyParamInterface::Prop3 set" << std::endl;
    auto l_prop4 = 0;
    l_prop4 = testManyParamInterface->getProp4();
    std::cout << "  ManyParamInterface::Prop4 retrieved" << std::endl;
    testManyParamInterface->setProp4(l_prop4);
    std::cout << "  ManyParamInterface::Prop4 set" << std::endl;
}

void testTestbed2NestedStruct1Interface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<INestedStruct1Interface> testNestedStruct1Interface = std::make_unique<NestedStruct1InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct1Interface>());

    // Thread safe access
    auto l_prop1 = NestedStruct1();
    l_prop1 = testNestedStruct1Interface->getProp1();
    std::cout << "  NestedStruct1Interface::Prop1 retrieved" << std::endl;
    testNestedStruct1Interface->setProp1(l_prop1);
    std::cout << "  NestedStruct1Interface::Prop1 set" << std::endl;
}

void testTestbed2NestedStruct2Interface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<INestedStruct2Interface> testNestedStruct2Interface = std::make_unique<NestedStruct2InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct2Interface>());

    // Thread safe access
    auto l_prop1 = NestedStruct1();
    l_prop1 = testNestedStruct2Interface->getProp1();
    std::cout << "  NestedStruct2Interface::Prop1 retrieved" << std::endl;
    testNestedStruct2Interface->setProp1(l_prop1);
    std::cout << "  NestedStruct2Interface::Prop1 set" << std::endl;
    auto l_prop2 = NestedStruct2();
    l_prop2 = testNestedStruct2Interface->getProp2();
    std::cout << "  NestedStruct2Interface::Prop2 retrieved" << std::endl;
    testNestedStruct2Interface->setProp2(l_prop2);
    std::cout << "  NestedStruct2Interface::Prop2 set" << std::endl;
}

void testTestbed2NestedStruct3Interface()
{
    using namespace Test::Testbed2;

    std::unique_ptr<INestedStruct3Interface> testNestedStruct3Interface = std::make_unique<NestedStruct3InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct3Interface>());

    // Thread safe access
    auto l_prop1 = NestedStruct1();
    l_prop1 = testNestedStruct3Interface->getProp1();
    std::cout << "  NestedStruct3Interface::Prop1 retrieved" << std::endl;
    testNestedStruct3Interface->setProp1(l_prop1);
    std::cout << "  NestedStruct3Interface::Prop1 set" << std::endl;
    auto l_prop2 = NestedStruct2();
    l_prop2 = testNestedStruct3Interface->getProp2();
    std::cout << "  NestedStruct3Interface::Prop2 retrieved" << std::endl;
    testNestedStruct3Interface->setProp2(l_prop2);
    std::cout << "  NestedStruct3Interface::Prop2 set" << std::endl;
    auto l_prop3 = NestedStruct3();
    l_prop3 = testNestedStruct3Interface->getProp3();
    std::cout << "  NestedStruct3Interface::Prop3 retrieved" << std::endl;
    testNestedStruct3Interface->setProp3(l_prop3);
    std::cout << "  NestedStruct3Interface::Prop3 set" << std::endl;
}

void testTbEnumEnumInterface()
{
    using namespace Test::TbEnum;

    std::unique_ptr<IEnumInterface> testEnumInterface = std::make_unique<EnumInterfaceThreadSafeDecorator>(std::make_shared<EnumInterface>());

    // Thread safe access
    auto l_prop0 = Enum0Enum::value0;
    l_prop0 = testEnumInterface->getProp0();
    std::cout << "  EnumInterface::Prop0 retrieved" << std::endl;
    testEnumInterface->setProp0(l_prop0);
    std::cout << "  EnumInterface::Prop0 set" << std::endl;
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testEnumInterface->getProp1();
    std::cout << "  EnumInterface::Prop1 retrieved" << std::endl;
    testEnumInterface->setProp1(l_prop1);
    std::cout << "  EnumInterface::Prop1 set" << std::endl;
    auto l_prop2 = Enum2Enum::value2;
    l_prop2 = testEnumInterface->getProp2();
    std::cout << "  EnumInterface::Prop2 retrieved" << std::endl;
    testEnumInterface->setProp2(l_prop2);
    std::cout << "  EnumInterface::Prop2 set" << std::endl;
    auto l_prop3 = Enum3Enum::value3;
    l_prop3 = testEnumInterface->getProp3();
    std::cout << "  EnumInterface::Prop3 retrieved" << std::endl;
    testEnumInterface->setProp3(l_prop3);
    std::cout << "  EnumInterface::Prop3 set" << std::endl;
}

void testTbSame1SameStruct1Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameStruct1Interface> testSameStruct1Interface = std::make_unique<SameStruct1InterfaceThreadSafeDecorator>(std::make_shared<SameStruct1Interface>());

    // Thread safe access
    auto l_prop1 = Struct1();
    l_prop1 = testSameStruct1Interface->getProp1();
    std::cout << "  SameStruct1Interface::Prop1 retrieved" << std::endl;
    testSameStruct1Interface->setProp1(l_prop1);
    std::cout << "  SameStruct1Interface::Prop1 set" << std::endl;
}

void testTbSame1SameStruct2Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameStruct2Interface> testSameStruct2Interface = std::make_unique<SameStruct2InterfaceThreadSafeDecorator>(std::make_shared<SameStruct2Interface>());

    // Thread safe access
    auto l_prop1 = Struct2();
    l_prop1 = testSameStruct2Interface->getProp1();
    std::cout << "  SameStruct2Interface::Prop1 retrieved" << std::endl;
    testSameStruct2Interface->setProp1(l_prop1);
    std::cout << "  SameStruct2Interface::Prop1 set" << std::endl;
    auto l_prop2 = Struct2();
    l_prop2 = testSameStruct2Interface->getProp2();
    std::cout << "  SameStruct2Interface::Prop2 retrieved" << std::endl;
    testSameStruct2Interface->setProp2(l_prop2);
    std::cout << "  SameStruct2Interface::Prop2 set" << std::endl;
}

void testTbSame1SameEnum1Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameEnum1Interface> testSameEnum1Interface = std::make_unique<SameEnum1InterfaceThreadSafeDecorator>(std::make_shared<SameEnum1Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum1Interface->getProp1();
    std::cout << "  SameEnum1Interface::Prop1 retrieved" << std::endl;
    testSameEnum1Interface->setProp1(l_prop1);
    std::cout << "  SameEnum1Interface::Prop1 set" << std::endl;
}

void testTbSame1SameEnum2Interface()
{
    using namespace Test::TbSame1;

    std::unique_ptr<ISameEnum2Interface> testSameEnum2Interface = std::make_unique<SameEnum2InterfaceThreadSafeDecorator>(std::make_shared<SameEnum2Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum2Interface->getProp1();
    std::cout << "  SameEnum2Interface::Prop1 retrieved" << std::endl;
    testSameEnum2Interface->setProp1(l_prop1);
    std::cout << "  SameEnum2Interface::Prop1 set" << std::endl;
    auto l_prop2 = Enum2Enum::value1;
    l_prop2 = testSameEnum2Interface->getProp2();
    std::cout << "  SameEnum2Interface::Prop2 retrieved" << std::endl;
    testSameEnum2Interface->setProp2(l_prop2);
    std::cout << "  SameEnum2Interface::Prop2 set" << std::endl;
}

void testTbSame2SameStruct1Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameStruct1Interface> testSameStruct1Interface = std::make_unique<SameStruct1InterfaceThreadSafeDecorator>(std::make_shared<SameStruct1Interface>());

    // Thread safe access
    auto l_prop1 = Struct1();
    l_prop1 = testSameStruct1Interface->getProp1();
    std::cout << "  SameStruct1Interface::Prop1 retrieved" << std::endl;
    testSameStruct1Interface->setProp1(l_prop1);
    std::cout << "  SameStruct1Interface::Prop1 set" << std::endl;
}

void testTbSame2SameStruct2Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameStruct2Interface> testSameStruct2Interface = std::make_unique<SameStruct2InterfaceThreadSafeDecorator>(std::make_shared<SameStruct2Interface>());

    // Thread safe access
    auto l_prop1 = Struct2();
    l_prop1 = testSameStruct2Interface->getProp1();
    std::cout << "  SameStruct2Interface::Prop1 retrieved" << std::endl;
    testSameStruct2Interface->setProp1(l_prop1);
    std::cout << "  SameStruct2Interface::Prop1 set" << std::endl;
    auto l_prop2 = Struct2();
    l_prop2 = testSameStruct2Interface->getProp2();
    std::cout << "  SameStruct2Interface::Prop2 retrieved" << std::endl;
    testSameStruct2Interface->setProp2(l_prop2);
    std::cout << "  SameStruct2Interface::Prop2 set" << std::endl;
}

void testTbSame2SameEnum1Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameEnum1Interface> testSameEnum1Interface = std::make_unique<SameEnum1InterfaceThreadSafeDecorator>(std::make_shared<SameEnum1Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum1Interface->getProp1();
    std::cout << "  SameEnum1Interface::Prop1 retrieved" << std::endl;
    testSameEnum1Interface->setProp1(l_prop1);
    std::cout << "  SameEnum1Interface::Prop1 set" << std::endl;
}

void testTbSame2SameEnum2Interface()
{
    using namespace Test::TbSame2;

    std::unique_ptr<ISameEnum2Interface> testSameEnum2Interface = std::make_unique<SameEnum2InterfaceThreadSafeDecorator>(std::make_shared<SameEnum2Interface>());

    // Thread safe access
    auto l_prop1 = Enum1Enum::value1;
    l_prop1 = testSameEnum2Interface->getProp1();
    std::cout << "  SameEnum2Interface::Prop1 retrieved" << std::endl;
    testSameEnum2Interface->setProp1(l_prop1);
    std::cout << "  SameEnum2Interface::Prop1 set" << std::endl;
    auto l_prop2 = Enum2Enum::value1;
    l_prop2 = testSameEnum2Interface->getProp2();
    std::cout << "  SameEnum2Interface::Prop2 retrieved" << std::endl;
    testSameEnum2Interface->setProp2(l_prop2);
    std::cout << "  SameEnum2Interface::Prop2 set" << std::endl;
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
    std::cout << "  SimpleInterface::PropBool retrieved" << std::endl;
    testSimpleInterface->setPropBool(l_propBool);
    std::cout << "  SimpleInterface::PropBool set" << std::endl;
    auto l_propInt = 0;
    l_propInt = testSimpleInterface->getPropInt();
    std::cout << "  SimpleInterface::PropInt retrieved" << std::endl;
    testSimpleInterface->setPropInt(l_propInt);
    std::cout << "  SimpleInterface::PropInt set" << std::endl;
    auto l_propInt32 = 0;
    l_propInt32 = testSimpleInterface->getPropInt32();
    std::cout << "  SimpleInterface::PropInt32 retrieved" << std::endl;
    testSimpleInterface->setPropInt32(l_propInt32);
    std::cout << "  SimpleInterface::PropInt32 set" << std::endl;
    auto l_propInt64 = 0LL;
    l_propInt64 = testSimpleInterface->getPropInt64();
    std::cout << "  SimpleInterface::PropInt64 retrieved" << std::endl;
    testSimpleInterface->setPropInt64(l_propInt64);
    std::cout << "  SimpleInterface::PropInt64 set" << std::endl;
    auto l_propFloat = 0.0f;
    l_propFloat = testSimpleInterface->getPropFloat();
    std::cout << "  SimpleInterface::PropFloat retrieved" << std::endl;
    testSimpleInterface->setPropFloat(l_propFloat);
    std::cout << "  SimpleInterface::PropFloat set" << std::endl;
    auto l_propFloat32 = 0.0f;
    l_propFloat32 = testSimpleInterface->getPropFloat32();
    std::cout << "  SimpleInterface::PropFloat32 retrieved" << std::endl;
    testSimpleInterface->setPropFloat32(l_propFloat32);
    std::cout << "  SimpleInterface::PropFloat32 set" << std::endl;
    auto l_propFloat64 = 0.0;
    l_propFloat64 = testSimpleInterface->getPropFloat64();
    std::cout << "  SimpleInterface::PropFloat64 retrieved" << std::endl;
    testSimpleInterface->setPropFloat64(l_propFloat64);
    std::cout << "  SimpleInterface::PropFloat64 set" << std::endl;
    auto l_propString = std::string();
    l_propString = testSimpleInterface->getPropString();
    std::cout << "  SimpleInterface::PropString retrieved" << std::endl;
    testSimpleInterface->setPropString(l_propString);
    std::cout << "  SimpleInterface::PropString set" << std::endl;
}

void testTbSimpleSimpleArrayInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<ISimpleArrayInterface> testSimpleArrayInterface = std::make_unique<SimpleArrayInterfaceThreadSafeDecorator>(std::make_shared<SimpleArrayInterface>());

    // Thread safe access
    auto l_propBool = std::list<bool>();
    l_propBool = testSimpleArrayInterface->getPropBool();
    std::cout << "  SimpleArrayInterface::PropBool retrieved" << std::endl;
    testSimpleArrayInterface->setPropBool(l_propBool);
    std::cout << "  SimpleArrayInterface::PropBool set" << std::endl;
    auto l_propInt = std::list<int>();
    l_propInt = testSimpleArrayInterface->getPropInt();
    std::cout << "  SimpleArrayInterface::PropInt retrieved" << std::endl;
    testSimpleArrayInterface->setPropInt(l_propInt);
    std::cout << "  SimpleArrayInterface::PropInt set" << std::endl;
    auto l_propInt32 = std::list<int32_t>();
    l_propInt32 = testSimpleArrayInterface->getPropInt32();
    std::cout << "  SimpleArrayInterface::PropInt32 retrieved" << std::endl;
    testSimpleArrayInterface->setPropInt32(l_propInt32);
    std::cout << "  SimpleArrayInterface::PropInt32 set" << std::endl;
    auto l_propInt64 = std::list<int64_t>();
    l_propInt64 = testSimpleArrayInterface->getPropInt64();
    std::cout << "  SimpleArrayInterface::PropInt64 retrieved" << std::endl;
    testSimpleArrayInterface->setPropInt64(l_propInt64);
    std::cout << "  SimpleArrayInterface::PropInt64 set" << std::endl;
    auto l_propFloat = std::list<float>();
    l_propFloat = testSimpleArrayInterface->getPropFloat();
    std::cout << "  SimpleArrayInterface::PropFloat retrieved" << std::endl;
    testSimpleArrayInterface->setPropFloat(l_propFloat);
    std::cout << "  SimpleArrayInterface::PropFloat set" << std::endl;
    auto l_propFloat32 = std::list<float>();
    l_propFloat32 = testSimpleArrayInterface->getPropFloat32();
    std::cout << "  SimpleArrayInterface::PropFloat32 retrieved" << std::endl;
    testSimpleArrayInterface->setPropFloat32(l_propFloat32);
    std::cout << "  SimpleArrayInterface::PropFloat32 set" << std::endl;
    auto l_propFloat64 = std::list<double>();
    l_propFloat64 = testSimpleArrayInterface->getPropFloat64();
    std::cout << "  SimpleArrayInterface::PropFloat64 retrieved" << std::endl;
    testSimpleArrayInterface->setPropFloat64(l_propFloat64);
    std::cout << "  SimpleArrayInterface::PropFloat64 set" << std::endl;
    auto l_propString = std::list<std::string>();
    l_propString = testSimpleArrayInterface->getPropString();
    std::cout << "  SimpleArrayInterface::PropString retrieved" << std::endl;
    testSimpleArrayInterface->setPropString(l_propString);
    std::cout << "  SimpleArrayInterface::PropString set" << std::endl;
    auto l_propReadOnlyString = std::string();
    l_propReadOnlyString = testSimpleArrayInterface->getPropReadOnlyString();
    std::cout << "  SimpleArrayInterface::PropReadOnlyString retrieved" << std::endl;
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
    std::cout << "  NoOperationsInterface::PropBool retrieved" << std::endl;
    testNoOperationsInterface->setPropBool(l_propBool);
    std::cout << "  NoOperationsInterface::PropBool set" << std::endl;
    auto l_propInt = 0;
    l_propInt = testNoOperationsInterface->getPropInt();
    std::cout << "  NoOperationsInterface::PropInt retrieved" << std::endl;
    testNoOperationsInterface->setPropInt(l_propInt);
    std::cout << "  NoOperationsInterface::PropInt set" << std::endl;
}

void testTbSimpleNoSignalsInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<INoSignalsInterface> testNoSignalsInterface = std::make_unique<NoSignalsInterfaceThreadSafeDecorator>(std::make_shared<NoSignalsInterface>());

    // Thread safe access
    auto l_propBool = false;
    l_propBool = testNoSignalsInterface->getPropBool();
    std::cout << "  NoSignalsInterface::PropBool retrieved" << std::endl;
    testNoSignalsInterface->setPropBool(l_propBool);
    std::cout << "  NoSignalsInterface::PropBool set" << std::endl;
    auto l_propInt = 0;
    l_propInt = testNoSignalsInterface->getPropInt();
    std::cout << "  NoSignalsInterface::PropInt retrieved" << std::endl;
    testNoSignalsInterface->setPropInt(l_propInt);
    std::cout << "  NoSignalsInterface::PropInt set" << std::endl;
}

void testTbSimpleEmptyInterface()
{
    using namespace Test::TbSimple;

    std::unique_ptr<IEmptyInterface> testEmptyInterface = std::make_unique<EmptyInterfaceThreadSafeDecorator>(std::make_shared<EmptyInterface>());

    // Thread safe access
}

void testTestbed1StructInterface()
{
    using namespace Test::Testbed1;

    std::unique_ptr<IStructInterface> testStructInterface = std::make_unique<StructInterfaceThreadSafeDecorator>(std::make_shared<StructInterface>());

    // Thread safe access
    auto l_propBool = StructBool();
    l_propBool = testStructInterface->getPropBool();
    std::cout << "  StructInterface::PropBool retrieved" << std::endl;
    testStructInterface->setPropBool(l_propBool);
    std::cout << "  StructInterface::PropBool set" << std::endl;
    auto l_propInt = StructInt();
    l_propInt = testStructInterface->getPropInt();
    std::cout << "  StructInterface::PropInt retrieved" << std::endl;
    testStructInterface->setPropInt(l_propInt);
    std::cout << "  StructInterface::PropInt set" << std::endl;
    auto l_propFloat = StructFloat();
    l_propFloat = testStructInterface->getPropFloat();
    std::cout << "  StructInterface::PropFloat retrieved" << std::endl;
    testStructInterface->setPropFloat(l_propFloat);
    std::cout << "  StructInterface::PropFloat set" << std::endl;
    auto l_propString = StructString();
    l_propString = testStructInterface->getPropString();
    std::cout << "  StructInterface::PropString retrieved" << std::endl;
    testStructInterface->setPropString(l_propString);
    std::cout << "  StructInterface::PropString set" << std::endl;
}

void testTestbed1StructArrayInterface()
{
    using namespace Test::Testbed1;

    std::unique_ptr<IStructArrayInterface> testStructArrayInterface = std::make_unique<StructArrayInterfaceThreadSafeDecorator>(std::make_shared<StructArrayInterface>());

    // Thread safe access
    auto l_propBool = std::list<StructBool>();
    l_propBool = testStructArrayInterface->getPropBool();
    std::cout << "  StructArrayInterface::PropBool retrieved" << std::endl;
    testStructArrayInterface->setPropBool(l_propBool);
    std::cout << "  StructArrayInterface::PropBool set" << std::endl;
    auto l_propInt = std::list<StructInt>();
    l_propInt = testStructArrayInterface->getPropInt();
    std::cout << "  StructArrayInterface::PropInt retrieved" << std::endl;
    testStructArrayInterface->setPropInt(l_propInt);
    std::cout << "  StructArrayInterface::PropInt set" << std::endl;
    auto l_propFloat = std::list<StructFloat>();
    l_propFloat = testStructArrayInterface->getPropFloat();
    std::cout << "  StructArrayInterface::PropFloat retrieved" << std::endl;
    testStructArrayInterface->setPropFloat(l_propFloat);
    std::cout << "  StructArrayInterface::PropFloat set" << std::endl;
    auto l_propString = std::list<StructString>();
    l_propString = testStructArrayInterface->getPropString();
    std::cout << "  StructArrayInterface::PropString retrieved" << std::endl;
    testStructArrayInterface->setPropString(l_propString);
    std::cout << "  StructArrayInterface::PropString set" << std::endl;
    auto l_propEnum = std::list<Enum0Enum>();
    l_propEnum = testStructArrayInterface->getPropEnum();
    std::cout << "  StructArrayInterface::PropEnum retrieved" << std::endl;
    testStructArrayInterface->setPropEnum(l_propEnum);
    std::cout << "  StructArrayInterface::PropEnum set" << std::endl;
}

void testTestbed1StructArray2Interface()
{
    using namespace Test::Testbed1;

    std::unique_ptr<IStructArray2Interface> testStructArray2Interface = std::make_unique<StructArray2InterfaceThreadSafeDecorator>(std::make_shared<StructArray2Interface>());

    // Thread safe access
    auto l_propBool = StructBoolWithArray();
    l_propBool = testStructArray2Interface->getPropBool();
    std::cout << "  StructArray2Interface::PropBool retrieved" << std::endl;
    testStructArray2Interface->setPropBool(l_propBool);
    std::cout << "  StructArray2Interface::PropBool set" << std::endl;
    auto l_propInt = StructIntWithArray();
    l_propInt = testStructArray2Interface->getPropInt();
    std::cout << "  StructArray2Interface::PropInt retrieved" << std::endl;
    testStructArray2Interface->setPropInt(l_propInt);
    std::cout << "  StructArray2Interface::PropInt set" << std::endl;
    auto l_propFloat = StructFloatWithArray();
    l_propFloat = testStructArray2Interface->getPropFloat();
    std::cout << "  StructArray2Interface::PropFloat retrieved" << std::endl;
    testStructArray2Interface->setPropFloat(l_propFloat);
    std::cout << "  StructArray2Interface::PropFloat set" << std::endl;
    auto l_propString = StructStringWithArray();
    l_propString = testStructArray2Interface->getPropString();
    std::cout << "  StructArray2Interface::PropString retrieved" << std::endl;
    testStructArray2Interface->setPropString(l_propString);
    std::cout << "  StructArray2Interface::PropString set" << std::endl;
    auto l_propEnum = StructEnumWithArray();
    l_propEnum = testStructArray2Interface->getPropEnum();
    std::cout << "  StructArray2Interface::PropEnum retrieved" << std::endl;
    testStructArray2Interface->setPropEnum(l_propEnum);
    std::cout << "  StructArray2Interface::PropEnum set" << std::endl;
}

void testTbNamesNamEs()
{
    using namespace Test::TbNames;

    std::unique_ptr<INamEs> testNamEs = std::make_unique<NamEsThreadSafeDecorator>(std::make_shared<NamEs>());

    // Thread safe access
    auto l_switch = false;
    l_switch = testNamEs->getSwitch();
    std::cout << "  NamEs::Switch retrieved" << std::endl;
    testNamEs->setSwitch(l_switch);
    std::cout << "  NamEs::Switch set" << std::endl;
    auto l_someProperty = 0;
    l_someProperty = testNamEs->getSomeProperty();
    std::cout << "  NamEs::SomeProperty retrieved" << std::endl;
    testNamEs->setSomeProperty(l_someProperty);
    std::cout << "  NamEs::SomeProperty set" << std::endl;
    auto l_somePoperty2 = 0;
    l_somePoperty2 = testNamEs->getSomePoperty2();
    std::cout << "  NamEs::SomePoperty2 retrieved" << std::endl;
    testNamEs->setSomePoperty2(l_somePoperty2);
    std::cout << "  NamEs::SomePoperty2 set" << std::endl;
    auto l_enumProperty = Enum_With_Under_scoresEnum::First_Value;
    l_enumProperty = testNamEs->getEnumProperty();
    std::cout << "  NamEs::EnumProperty retrieved" << std::endl;
    testNamEs->setEnumProperty(l_enumProperty);
    std::cout << "  NamEs::EnumProperty set" << std::endl;
}

void testCounterCounter()
{
    using namespace Test::Counter;

    std::unique_ptr<ICounter> testCounter = std::make_unique<CounterThreadSafeDecorator>(std::make_shared<Counter>());

    // Thread safe access
    auto l_vector = Test::CustomTypes::Vector3D();
    l_vector = testCounter->getVector();
    std::cout << "  Counter::Vector retrieved" << std::endl;
    testCounter->setVector(l_vector);
    std::cout << "  Counter::Vector set" << std::endl;
    auto l_externVector = Eigen::Vector3f(0,0,0);
    l_externVector = testCounter->getExternVector();
    std::cout << "  Counter::ExternVector retrieved" << std::endl;
    testCounter->setExternVector(l_externVector);
    std::cout << "  Counter::ExternVector set" << std::endl;
    auto l_vectorArray = std::list<Test::CustomTypes::Vector3D>();
    l_vectorArray = testCounter->getVectorArray();
    std::cout << "  Counter::VectorArray retrieved" << std::endl;
    testCounter->setVectorArray(l_vectorArray);
    std::cout << "  Counter::VectorArray set" << std::endl;
    auto l_externVectorArray = std::list<Eigen::Vector3f>();
    l_externVectorArray = testCounter->getExternVectorArray();
    std::cout << "  Counter::ExternVectorArray retrieved" << std::endl;
    testCounter->setExternVectorArray(l_externVectorArray);
    std::cout << "  Counter::ExternVectorArray set" << std::endl;
}

void testTbStructArrayStructArrayFieldInterface()
{
    using namespace Test::TbStructArray;

    std::unique_ptr<IStructArrayFieldInterface> testStructArrayFieldInterface = std::make_unique<StructArrayFieldInterfaceThreadSafeDecorator>(std::make_shared<StructArrayFieldInterface>());

    // Thread safe access
    auto l_propStructArray = StructWithArrayOfStructs();
    l_propStructArray = testStructArrayFieldInterface->getPropStructArray();
    std::cout << "  StructArrayFieldInterface::PropStructArray retrieved" << std::endl;
    testStructArrayFieldInterface->setPropStructArray(l_propStructArray);
    std::cout << "  StructArrayFieldInterface::PropStructArray set" << std::endl;
    auto l_propEnumArray = StructWithArrayOfEnums();
    l_propEnumArray = testStructArrayFieldInterface->getPropEnumArray();
    std::cout << "  StructArrayFieldInterface::PropEnumArray retrieved" << std::endl;
    testStructArrayFieldInterface->setPropEnumArray(l_propEnumArray);
    std::cout << "  StructArrayFieldInterface::PropEnumArray set" << std::endl;
    auto l_propIntArray = StructWithArrayOfInts();
    l_propIntArray = testStructArrayFieldInterface->getPropIntArray();
    std::cout << "  StructArrayFieldInterface::PropIntArray retrieved" << std::endl;
    testStructArrayFieldInterface->setPropIntArray(l_propIntArray);
    std::cout << "  StructArrayFieldInterface::PropIntArray set" << std::endl;
    auto l_propMixed = MixedStruct();
    l_propMixed = testStructArrayFieldInterface->getPropMixed();
    std::cout << "  StructArrayFieldInterface::PropMixed retrieved" << std::endl;
    testStructArrayFieldInterface->setPropMixed(l_propMixed);
    std::cout << "  StructArrayFieldInterface::PropMixed set" << std::endl;
}


int main(){
    std::cout << "Testing Testbed2::ManyParamInterface (thread-safe)" << std::endl;
    testTestbed2ManyParamInterface();
    std::cout << "Testing Testbed2::NestedStruct1Interface (thread-safe)" << std::endl;
    testTestbed2NestedStruct1Interface();
    std::cout << "Testing Testbed2::NestedStruct2Interface (thread-safe)" << std::endl;
    testTestbed2NestedStruct2Interface();
    std::cout << "Testing Testbed2::NestedStruct3Interface (thread-safe)" << std::endl;
    testTestbed2NestedStruct3Interface();
    std::cout << "Testing TbEnum::EnumInterface (thread-safe)" << std::endl;
    testTbEnumEnumInterface();
    std::cout << "Testing TbSame1::SameStruct1Interface (thread-safe)" << std::endl;
    testTbSame1SameStruct1Interface();
    std::cout << "Testing TbSame1::SameStruct2Interface (thread-safe)" << std::endl;
    testTbSame1SameStruct2Interface();
    std::cout << "Testing TbSame1::SameEnum1Interface (thread-safe)" << std::endl;
    testTbSame1SameEnum1Interface();
    std::cout << "Testing TbSame1::SameEnum2Interface (thread-safe)" << std::endl;
    testTbSame1SameEnum2Interface();
    std::cout << "Testing TbSame2::SameStruct1Interface (thread-safe)" << std::endl;
    testTbSame2SameStruct1Interface();
    std::cout << "Testing TbSame2::SameStruct2Interface (thread-safe)" << std::endl;
    testTbSame2SameStruct2Interface();
    std::cout << "Testing TbSame2::SameEnum1Interface (thread-safe)" << std::endl;
    testTbSame2SameEnum1Interface();
    std::cout << "Testing TbSame2::SameEnum2Interface (thread-safe)" << std::endl;
    testTbSame2SameEnum2Interface();
    std::cout << "Testing TbSimple::VoidInterface (thread-safe)" << std::endl;
    testTbSimpleVoidInterface();
    std::cout << "Testing TbSimple::SimpleInterface (thread-safe)" << std::endl;
    testTbSimpleSimpleInterface();
    std::cout << "Testing TbSimple::SimpleArrayInterface (thread-safe)" << std::endl;
    testTbSimpleSimpleArrayInterface();
    std::cout << "Testing TbSimple::NoPropertiesInterface (thread-safe)" << std::endl;
    testTbSimpleNoPropertiesInterface();
    std::cout << "Testing TbSimple::NoOperationsInterface (thread-safe)" << std::endl;
    testTbSimpleNoOperationsInterface();
    std::cout << "Testing TbSimple::NoSignalsInterface (thread-safe)" << std::endl;
    testTbSimpleNoSignalsInterface();
    std::cout << "Testing TbSimple::EmptyInterface (thread-safe)" << std::endl;
    testTbSimpleEmptyInterface();
    std::cout << "Testing Testbed1::StructInterface (thread-safe)" << std::endl;
    testTestbed1StructInterface();
    std::cout << "Testing Testbed1::StructArrayInterface (thread-safe)" << std::endl;
    testTestbed1StructArrayInterface();
    std::cout << "Testing Testbed1::StructArray2Interface (thread-safe)" << std::endl;
    testTestbed1StructArray2Interface();
    std::cout << "Testing TbNames::NamEs (thread-safe)" << std::endl;
    testTbNamesNamEs();
    std::cout << "Testing Counter::Counter (thread-safe)" << std::endl;
    testCounterCounter();
    std::cout << "Testing TbStructArray::StructArrayFieldInterface (thread-safe)" << std::endl;
    testTbStructArrayStructArrayFieldInterface();

    std::cout << "AppThreadSafe example finished." << std::endl;
    return 0;
}
