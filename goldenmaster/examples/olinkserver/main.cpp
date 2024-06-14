
#include "testbed2/implementation/manyparaminterface.h"
#include "testbed2/generated/olink/manyparaminterfaceservice.h"
#include "testbed2/generated/core/manyparaminterface.threadsafedecorator.h"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "testbed2/generated/olink/nestedstruct1interfaceservice.h"
#include "testbed2/generated/core/nestedstruct1interface.threadsafedecorator.h"
#include "testbed2/implementation/nestedstruct2interface.h"
#include "testbed2/generated/olink/nestedstruct2interfaceservice.h"
#include "testbed2/generated/core/nestedstruct2interface.threadsafedecorator.h"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/olink/nestedstruct3interfaceservice.h"
#include "testbed2/generated/core/nestedstruct3interface.threadsafedecorator.h"
#include "tb_enum/implementation/enuminterface.h"
#include "tb_enum/generated/olink/enuminterfaceservice.h"
#include "tb_enum/generated/core/enuminterface.threadsafedecorator.h"
#include "tb_same1/implementation/samestruct1interface.h"
#include "tb_same1/generated/olink/samestruct1interfaceservice.h"
#include "tb_same1/generated/core/samestruct1interface.threadsafedecorator.h"
#include "tb_same1/implementation/samestruct2interface.h"
#include "tb_same1/generated/olink/samestruct2interfaceservice.h"
#include "tb_same1/generated/core/samestruct2interface.threadsafedecorator.h"
#include "tb_same1/implementation/sameenum1interface.h"
#include "tb_same1/generated/olink/sameenum1interfaceservice.h"
#include "tb_same1/generated/core/sameenum1interface.threadsafedecorator.h"
#include "tb_same1/implementation/sameenum2interface.h"
#include "tb_same1/generated/olink/sameenum2interfaceservice.h"
#include "tb_same1/generated/core/sameenum2interface.threadsafedecorator.h"
#include "tb_same2/implementation/samestruct1interface.h"
#include "tb_same2/generated/olink/samestruct1interfaceservice.h"
#include "tb_same2/generated/core/samestruct1interface.threadsafedecorator.h"
#include "tb_same2/implementation/samestruct2interface.h"
#include "tb_same2/generated/olink/samestruct2interfaceservice.h"
#include "tb_same2/generated/core/samestruct2interface.threadsafedecorator.h"
#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/olink/sameenum1interfaceservice.h"
#include "tb_same2/generated/core/sameenum1interface.threadsafedecorator.h"
#include "tb_same2/implementation/sameenum2interface.h"
#include "tb_same2/generated/olink/sameenum2interfaceservice.h"
#include "tb_same2/generated/core/sameenum2interface.threadsafedecorator.h"
#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/olink/voidinterfaceservice.h"
#include "tb_simple/generated/core/voidinterface.threadsafedecorator.h"
#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/olink/simpleinterfaceservice.h"
#include "tb_simple/generated/core/simpleinterface.threadsafedecorator.h"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/olink/simplearrayinterfaceservice.h"
#include "tb_simple/generated/core/simplearrayinterface.threadsafedecorator.h"
#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/olink/nopropertiesinterfaceservice.h"
#include "tb_simple/generated/core/nopropertiesinterface.threadsafedecorator.h"
#include "tb_simple/implementation/nooperationsinterface.h"
#include "tb_simple/generated/olink/nooperationsinterfaceservice.h"
#include "tb_simple/generated/core/nooperationsinterface.threadsafedecorator.h"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/olink/nosignalsinterfaceservice.h"
#include "tb_simple/generated/core/nosignalsinterface.threadsafedecorator.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/olink/structinterfaceservice.h"
#include "testbed1/generated/core/structinterface.threadsafedecorator.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/olink/structarrayinterfaceservice.h"
#include "testbed1/generated/core/structarrayinterface.threadsafedecorator.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/olink/namesservice.h"
#include "tb_names/generated/core/names.threadsafedecorator.h"
#include "counter/implementation/counter.h"
#include "counter/generated/olink/counterservice.h"
#include "counter/generated/core/counter.threadsafedecorator.h"

#include "apigear/olink/olinklogadapter.h"
#include "olink/remoteregistry.h"
#include "apigear/olink/olinkhost.h"

#include <iostream>
#include <sstream>
#include <cstdlib>

ApiGear::Utilities::WriteLogFunc getLogging(){

    ApiGear::Utilities::WriteLogFunc logConsoleFunc = nullptr;
    ApiGear::Utilities::LogLevel logLevel = ApiGear::Utilities::LogLevel::Warning;

    // check whether logging level is set via env
    if (const char* envLogLevel = std::getenv("LOG_LEVEL"))
    {
        int logLevelNumber = 255;
        std::stringstream(envLogLevel) >> logLevelNumber;
        logLevel = static_cast<ApiGear::Utilities::LogLevel>(logLevelNumber);
    }

    logConsoleFunc = ApiGear::Utilities::getConsoleLogFunc(logLevel);
    // check whether logging was disabled
    if (logLevel > ApiGear::Utilities::LogLevel::Error) {
        logConsoleFunc = nullptr;
    }

    // set global log function
    ApiGear::Utilities::setLog(logConsoleFunc);

    return logConsoleFunc;
}

using namespace Test;

int main(){
    ApiGear::ObjectLink::RemoteRegistry registry;
    auto logConsoleFunc = getLogging();
    registry.onLog(ApiGear::Utilities::logAdapter(logConsoleFunc));

    ApiGear::PocoImpl::OLinkHost testserver(registry, ApiGear::Utilities::logAdapter(logConsoleFunc));
    auto testbed2ManyParamInterface = std::make_shared<Testbed2::ManyParamInterface>();
    auto testbed2ManyParamInterfaceThreadSafe = std::make_shared<Testbed2::ManyParamInterfaceThreadSafeDecorator>(testbed2ManyParamInterface);
    auto testbed2OlinkManyParamInterfaceService = std::make_shared<Testbed2::olink::ManyParamInterfaceService>(testbed2ManyParamInterfaceThreadSafe, registry);
    registry.addSource(testbed2OlinkManyParamInterfaceService);
    auto testbed2NestedStruct1Interface = std::make_shared<Testbed2::NestedStruct1Interface>();
    auto testbed2NestedStruct1InterfaceThreadSafe = std::make_shared<Testbed2::NestedStruct1InterfaceThreadSafeDecorator>(testbed2NestedStruct1Interface);
    auto testbed2OlinkNestedStruct1InterfaceService = std::make_shared<Testbed2::olink::NestedStruct1InterfaceService>(testbed2NestedStruct1InterfaceThreadSafe, registry);
    registry.addSource(testbed2OlinkNestedStruct1InterfaceService);
    auto testbed2NestedStruct2Interface = std::make_shared<Testbed2::NestedStruct2Interface>();
    auto testbed2NestedStruct2InterfaceThreadSafe = std::make_shared<Testbed2::NestedStruct2InterfaceThreadSafeDecorator>(testbed2NestedStruct2Interface);
    auto testbed2OlinkNestedStruct2InterfaceService = std::make_shared<Testbed2::olink::NestedStruct2InterfaceService>(testbed2NestedStruct2InterfaceThreadSafe, registry);
    registry.addSource(testbed2OlinkNestedStruct2InterfaceService);
    auto testbed2NestedStruct3Interface = std::make_shared<Testbed2::NestedStruct3Interface>();
    auto testbed2NestedStruct3InterfaceThreadSafe = std::make_shared<Testbed2::NestedStruct3InterfaceThreadSafeDecorator>(testbed2NestedStruct3Interface);
    auto testbed2OlinkNestedStruct3InterfaceService = std::make_shared<Testbed2::olink::NestedStruct3InterfaceService>(testbed2NestedStruct3InterfaceThreadSafe, registry);
    registry.addSource(testbed2OlinkNestedStruct3InterfaceService);
    auto tbEnumEnumInterface = std::make_shared<TbEnum::EnumInterface>();
    auto tbEnumEnumInterfaceThreadSafe = std::make_shared<TbEnum::EnumInterfaceThreadSafeDecorator>(tbEnumEnumInterface);
    auto tbEnumOlinkEnumInterfaceService = std::make_shared<TbEnum::olink::EnumInterfaceService>(tbEnumEnumInterfaceThreadSafe, registry);
    registry.addSource(tbEnumOlinkEnumInterfaceService);
    auto tbSame1SameStruct1Interface = std::make_shared<TbSame1::SameStruct1Interface>();
    auto tbSame1SameStruct1InterfaceThreadSafe = std::make_shared<TbSame1::SameStruct1InterfaceThreadSafeDecorator>(tbSame1SameStruct1Interface);
    auto tbSame1OlinkSameStruct1InterfaceService = std::make_shared<TbSame1::olink::SameStruct1InterfaceService>(tbSame1SameStruct1InterfaceThreadSafe, registry);
    registry.addSource(tbSame1OlinkSameStruct1InterfaceService);
    auto tbSame1SameStruct2Interface = std::make_shared<TbSame1::SameStruct2Interface>();
    auto tbSame1SameStruct2InterfaceThreadSafe = std::make_shared<TbSame1::SameStruct2InterfaceThreadSafeDecorator>(tbSame1SameStruct2Interface);
    auto tbSame1OlinkSameStruct2InterfaceService = std::make_shared<TbSame1::olink::SameStruct2InterfaceService>(tbSame1SameStruct2InterfaceThreadSafe, registry);
    registry.addSource(tbSame1OlinkSameStruct2InterfaceService);
    auto tbSame1SameEnum1Interface = std::make_shared<TbSame1::SameEnum1Interface>();
    auto tbSame1SameEnum1InterfaceThreadSafe = std::make_shared<TbSame1::SameEnum1InterfaceThreadSafeDecorator>(tbSame1SameEnum1Interface);
    auto tbSame1OlinkSameEnum1InterfaceService = std::make_shared<TbSame1::olink::SameEnum1InterfaceService>(tbSame1SameEnum1InterfaceThreadSafe, registry);
    registry.addSource(tbSame1OlinkSameEnum1InterfaceService);
    auto tbSame1SameEnum2Interface = std::make_shared<TbSame1::SameEnum2Interface>();
    auto tbSame1SameEnum2InterfaceThreadSafe = std::make_shared<TbSame1::SameEnum2InterfaceThreadSafeDecorator>(tbSame1SameEnum2Interface);
    auto tbSame1OlinkSameEnum2InterfaceService = std::make_shared<TbSame1::olink::SameEnum2InterfaceService>(tbSame1SameEnum2InterfaceThreadSafe, registry);
    registry.addSource(tbSame1OlinkSameEnum2InterfaceService);
    auto tbSame2SameStruct1Interface = std::make_shared<TbSame2::SameStruct1Interface>();
    auto tbSame2SameStruct1InterfaceThreadSafe = std::make_shared<TbSame2::SameStruct1InterfaceThreadSafeDecorator>(tbSame2SameStruct1Interface);
    auto tbSame2OlinkSameStruct1InterfaceService = std::make_shared<TbSame2::olink::SameStruct1InterfaceService>(tbSame2SameStruct1InterfaceThreadSafe, registry);
    registry.addSource(tbSame2OlinkSameStruct1InterfaceService);
    auto tbSame2SameStruct2Interface = std::make_shared<TbSame2::SameStruct2Interface>();
    auto tbSame2SameStruct2InterfaceThreadSafe = std::make_shared<TbSame2::SameStruct2InterfaceThreadSafeDecorator>(tbSame2SameStruct2Interface);
    auto tbSame2OlinkSameStruct2InterfaceService = std::make_shared<TbSame2::olink::SameStruct2InterfaceService>(tbSame2SameStruct2InterfaceThreadSafe, registry);
    registry.addSource(tbSame2OlinkSameStruct2InterfaceService);
    auto tbSame2SameEnum1Interface = std::make_shared<TbSame2::SameEnum1Interface>();
    auto tbSame2SameEnum1InterfaceThreadSafe = std::make_shared<TbSame2::SameEnum1InterfaceThreadSafeDecorator>(tbSame2SameEnum1Interface);
    auto tbSame2OlinkSameEnum1InterfaceService = std::make_shared<TbSame2::olink::SameEnum1InterfaceService>(tbSame2SameEnum1InterfaceThreadSafe, registry);
    registry.addSource(tbSame2OlinkSameEnum1InterfaceService);
    auto tbSame2SameEnum2Interface = std::make_shared<TbSame2::SameEnum2Interface>();
    auto tbSame2SameEnum2InterfaceThreadSafe = std::make_shared<TbSame2::SameEnum2InterfaceThreadSafeDecorator>(tbSame2SameEnum2Interface);
    auto tbSame2OlinkSameEnum2InterfaceService = std::make_shared<TbSame2::olink::SameEnum2InterfaceService>(tbSame2SameEnum2InterfaceThreadSafe, registry);
    registry.addSource(tbSame2OlinkSameEnum2InterfaceService);
    auto tbSimpleVoidInterface = std::make_shared<TbSimple::VoidInterface>();
    auto tbSimpleVoidInterfaceThreadSafe = std::make_shared<TbSimple::VoidInterfaceThreadSafeDecorator>(tbSimpleVoidInterface);
    auto tbSimpleOlinkVoidInterfaceService = std::make_shared<TbSimple::olink::VoidInterfaceService>(tbSimpleVoidInterfaceThreadSafe, registry);
    registry.addSource(tbSimpleOlinkVoidInterfaceService);
    auto tbSimpleSimpleInterface = std::make_shared<TbSimple::SimpleInterface>();
    auto tbSimpleSimpleInterfaceThreadSafe = std::make_shared<TbSimple::SimpleInterfaceThreadSafeDecorator>(tbSimpleSimpleInterface);
    auto tbSimpleOlinkSimpleInterfaceService = std::make_shared<TbSimple::olink::SimpleInterfaceService>(tbSimpleSimpleInterfaceThreadSafe, registry);
    registry.addSource(tbSimpleOlinkSimpleInterfaceService);
    auto tbSimpleSimpleArrayInterface = std::make_shared<TbSimple::SimpleArrayInterface>();
    auto tbSimpleSimpleArrayInterfaceThreadSafe = std::make_shared<TbSimple::SimpleArrayInterfaceThreadSafeDecorator>(tbSimpleSimpleArrayInterface);
    auto tbSimpleOlinkSimpleArrayInterfaceService = std::make_shared<TbSimple::olink::SimpleArrayInterfaceService>(tbSimpleSimpleArrayInterfaceThreadSafe, registry);
    registry.addSource(tbSimpleOlinkSimpleArrayInterfaceService);
    auto tbSimpleNoPropertiesInterface = std::make_shared<TbSimple::NoPropertiesInterface>();
    auto tbSimpleNoPropertiesInterfaceThreadSafe = std::make_shared<TbSimple::NoPropertiesInterfaceThreadSafeDecorator>(tbSimpleNoPropertiesInterface);
    auto tbSimpleOlinkNoPropertiesInterfaceService = std::make_shared<TbSimple::olink::NoPropertiesInterfaceService>(tbSimpleNoPropertiesInterfaceThreadSafe, registry);
    registry.addSource(tbSimpleOlinkNoPropertiesInterfaceService);
    auto tbSimpleNoOperationsInterface = std::make_shared<TbSimple::NoOperationsInterface>();
    auto tbSimpleNoOperationsInterfaceThreadSafe = std::make_shared<TbSimple::NoOperationsInterfaceThreadSafeDecorator>(tbSimpleNoOperationsInterface);
    auto tbSimpleOlinkNoOperationsInterfaceService = std::make_shared<TbSimple::olink::NoOperationsInterfaceService>(tbSimpleNoOperationsInterfaceThreadSafe, registry);
    registry.addSource(tbSimpleOlinkNoOperationsInterfaceService);
    auto tbSimpleNoSignalsInterface = std::make_shared<TbSimple::NoSignalsInterface>();
    auto tbSimpleNoSignalsInterfaceThreadSafe = std::make_shared<TbSimple::NoSignalsInterfaceThreadSafeDecorator>(tbSimpleNoSignalsInterface);
    auto tbSimpleOlinkNoSignalsInterfaceService = std::make_shared<TbSimple::olink::NoSignalsInterfaceService>(tbSimpleNoSignalsInterfaceThreadSafe, registry);
    registry.addSource(tbSimpleOlinkNoSignalsInterfaceService);
    auto testbed1StructInterface = std::make_shared<Testbed1::StructInterface>();
    auto testbed1StructInterfaceThreadSafe = std::make_shared<Testbed1::StructInterfaceThreadSafeDecorator>(testbed1StructInterface);
    auto testbed1OlinkStructInterfaceService = std::make_shared<Testbed1::olink::StructInterfaceService>(testbed1StructInterfaceThreadSafe, registry);
    registry.addSource(testbed1OlinkStructInterfaceService);
    auto testbed1StructArrayInterface = std::make_shared<Testbed1::StructArrayInterface>();
    auto testbed1StructArrayInterfaceThreadSafe = std::make_shared<Testbed1::StructArrayInterfaceThreadSafeDecorator>(testbed1StructArrayInterface);
    auto testbed1OlinkStructArrayInterfaceService = std::make_shared<Testbed1::olink::StructArrayInterfaceService>(testbed1StructArrayInterfaceThreadSafe, registry);
    registry.addSource(testbed1OlinkStructArrayInterfaceService);
    auto tbNamesNamEs = std::make_shared<TbNames::NamEs>();
    auto tbNamesNamEsThreadSafe = std::make_shared<TbNames::NamEsThreadSafeDecorator>(tbNamesNamEs);
    auto tbNamesOlinkNamEsService = std::make_shared<TbNames::olink::Nam_EsService>(tbNamesNamEsThreadSafe, registry);
    registry.addSource(tbNamesOlinkNamEsService);
    auto counterCounter = std::make_shared<Counter::Counter>();
    auto counterCounterThreadSafe = std::make_shared<Counter::CounterThreadSafeDecorator>(counterCounter);
    auto counterOlinkCounterService = std::make_shared<Counter::olink::CounterService>(counterCounterThreadSafe, registry);
    registry.addSource(counterOlinkCounterService);

    testserver.listen(8000);

    bool keepRunning = true;
    std::string cmd;
    do {
        std::cout << "Enter command:" << std::endl;
        getline (std::cin, cmd);

        if(cmd == "quit"){
            testserver.close();
            keepRunning = false;
        }
    } while(keepRunning);
    registry.removeSource(testbed2OlinkManyParamInterfaceService->olinkObjectName());
    registry.removeSource(testbed2OlinkNestedStruct1InterfaceService->olinkObjectName());
    registry.removeSource(testbed2OlinkNestedStruct2InterfaceService->olinkObjectName());
    registry.removeSource(testbed2OlinkNestedStruct3InterfaceService->olinkObjectName());
    registry.removeSource(tbEnumOlinkEnumInterfaceService->olinkObjectName());
    registry.removeSource(tbSame1OlinkSameStruct1InterfaceService->olinkObjectName());
    registry.removeSource(tbSame1OlinkSameStruct2InterfaceService->olinkObjectName());
    registry.removeSource(tbSame1OlinkSameEnum1InterfaceService->olinkObjectName());
    registry.removeSource(tbSame1OlinkSameEnum2InterfaceService->olinkObjectName());
    registry.removeSource(tbSame2OlinkSameStruct1InterfaceService->olinkObjectName());
    registry.removeSource(tbSame2OlinkSameStruct2InterfaceService->olinkObjectName());
    registry.removeSource(tbSame2OlinkSameEnum1InterfaceService->olinkObjectName());
    registry.removeSource(tbSame2OlinkSameEnum2InterfaceService->olinkObjectName());
    registry.removeSource(tbSimpleOlinkVoidInterfaceService->olinkObjectName());
    registry.removeSource(tbSimpleOlinkSimpleInterfaceService->olinkObjectName());
    registry.removeSource(tbSimpleOlinkSimpleArrayInterfaceService->olinkObjectName());
    registry.removeSource(tbSimpleOlinkNoPropertiesInterfaceService->olinkObjectName());
    registry.removeSource(tbSimpleOlinkNoOperationsInterfaceService->olinkObjectName());
    registry.removeSource(tbSimpleOlinkNoSignalsInterfaceService->olinkObjectName());
    registry.removeSource(testbed1OlinkStructInterfaceService->olinkObjectName());
    registry.removeSource(testbed1OlinkStructArrayInterfaceService->olinkObjectName());
    registry.removeSource(tbNamesOlinkNamEsService->olinkObjectName());
    registry.removeSource(counterOlinkCounterService->olinkObjectName());
    
    return 0;
}
