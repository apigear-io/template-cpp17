#include <iostream>
#include "testbed2/generated/olink/manyparaminterfaceclient.h"
#include "testbed2/generated/monitor/manyparaminterface.tracedecorator.h"
#include "testbed2/generated/olink/nestedstruct1interfaceclient.h"
#include "testbed2/generated/monitor/nestedstruct1interface.tracedecorator.h"
#include "testbed2/generated/olink/nestedstruct2interfaceclient.h"
#include "testbed2/generated/monitor/nestedstruct2interface.tracedecorator.h"
#include "testbed2/generated/olink/nestedstruct3interfaceclient.h"
#include "testbed2/generated/monitor/nestedstruct3interface.tracedecorator.h"
#include "tb_enum/generated/olink/enuminterfaceclient.h"
#include "tb_enum/generated/monitor/enuminterface.tracedecorator.h"
#include "tb_same1/generated/olink/samestruct1interfaceclient.h"
#include "tb_same1/generated/monitor/samestruct1interface.tracedecorator.h"
#include "tb_same1/generated/olink/samestruct2interfaceclient.h"
#include "tb_same1/generated/monitor/samestruct2interface.tracedecorator.h"
#include "tb_same1/generated/olink/sameenum1interfaceclient.h"
#include "tb_same1/generated/monitor/sameenum1interface.tracedecorator.h"
#include "tb_same1/generated/olink/sameenum2interfaceclient.h"
#include "tb_same1/generated/monitor/sameenum2interface.tracedecorator.h"
#include "tb_same2/generated/olink/samestruct1interfaceclient.h"
#include "tb_same2/generated/monitor/samestruct1interface.tracedecorator.h"
#include "tb_same2/generated/olink/samestruct2interfaceclient.h"
#include "tb_same2/generated/monitor/samestruct2interface.tracedecorator.h"
#include "tb_same2/generated/olink/sameenum1interfaceclient.h"
#include "tb_same2/generated/monitor/sameenum1interface.tracedecorator.h"
#include "tb_same2/generated/olink/sameenum2interfaceclient.h"
#include "tb_same2/generated/monitor/sameenum2interface.tracedecorator.h"
#include "tb_simple/generated/olink/voidinterfaceclient.h"
#include "tb_simple/generated/monitor/voidinterface.tracedecorator.h"
#include "tb_simple/generated/olink/simpleinterfaceclient.h"
#include "tb_simple/generated/monitor/simpleinterface.tracedecorator.h"
#include "tb_simple/generated/olink/simplearrayinterfaceclient.h"
#include "tb_simple/generated/monitor/simplearrayinterface.tracedecorator.h"
#include "tb_simple/generated/olink/nopropertiesinterfaceclient.h"
#include "tb_simple/generated/monitor/nopropertiesinterface.tracedecorator.h"
#include "tb_simple/generated/olink/nooperationsinterfaceclient.h"
#include "tb_simple/generated/monitor/nooperationsinterface.tracedecorator.h"
#include "tb_simple/generated/olink/nosignalsinterfaceclient.h"
#include "tb_simple/generated/monitor/nosignalsinterface.tracedecorator.h"
#include "testbed1/generated/olink/structinterfaceclient.h"
#include "testbed1/generated/monitor/structinterface.tracedecorator.h"
#include "testbed1/generated/olink/structarrayinterfaceclient.h"
#include "testbed1/generated/monitor/structarrayinterface.tracedecorator.h"
#include "tb_names/generated/olink/namesclient.h"
#include "tb_names/generated/monitor/names.tracedecorator.h"
#include "counter/generated/olink/counterclient.h"
#include "counter/generated/monitor/counter.tracedecorator.h"

#include "apigear/olink/olinkconnection.h"
#include "apigear/tracer/tracer.h"
#include "apigear/olink/olinklogadapter.h"
#include "olink/clientregistry.h"
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
    ApiGear::PocoImpl::Tracer tracer;
    tracer.connect("http://localhost:5555", "testExampleOLinkApp");
    ApiGear::ObjectLink::ClientRegistry registry;
    auto logConsoleFunc = getLogging();
    registry.onLog(ApiGear::Utilities::logAdapter(logConsoleFunc));
    ApiGear::PocoImpl::OlinkConnection clientNetworkEndpoint(registry);
    clientNetworkEndpoint.node()->onLog(ApiGear::Utilities::logAdapter(logConsoleFunc));
    auto testbed2ManyParamInterface = std::make_shared<Testbed2::olink::ManyParamInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(testbed2ManyParamInterface);
    std::unique_ptr<Testbed2::IManyParamInterface> testbed2ManyParamInterfaceTraced = Testbed2::ManyParamInterfaceTraceDecorator::connect(*testbed2ManyParamInterface, tracer);
    auto testbed2NestedStruct1Interface = std::make_shared<Testbed2::olink::NestedStruct1InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(testbed2NestedStruct1Interface);
    std::unique_ptr<Testbed2::INestedStruct1Interface> testbed2NestedStruct1InterfaceTraced = Testbed2::NestedStruct1InterfaceTraceDecorator::connect(*testbed2NestedStruct1Interface, tracer);
    auto testbed2NestedStruct2Interface = std::make_shared<Testbed2::olink::NestedStruct2InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(testbed2NestedStruct2Interface);
    std::unique_ptr<Testbed2::INestedStruct2Interface> testbed2NestedStruct2InterfaceTraced = Testbed2::NestedStruct2InterfaceTraceDecorator::connect(*testbed2NestedStruct2Interface, tracer);
    auto testbed2NestedStruct3Interface = std::make_shared<Testbed2::olink::NestedStruct3InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(testbed2NestedStruct3Interface);
    std::unique_ptr<Testbed2::INestedStruct3Interface> testbed2NestedStruct3InterfaceTraced = Testbed2::NestedStruct3InterfaceTraceDecorator::connect(*testbed2NestedStruct3Interface, tracer);
    auto tbEnumEnumInterface = std::make_shared<TbEnum::olink::EnumInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbEnumEnumInterface);
    std::unique_ptr<TbEnum::IEnumInterface> tbEnumEnumInterfaceTraced = TbEnum::EnumInterfaceTraceDecorator::connect(*tbEnumEnumInterface, tracer);
    auto tbSame1SameStruct1Interface = std::make_shared<TbSame1::olink::SameStruct1InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame1SameStruct1Interface);
    std::unique_ptr<TbSame1::ISameStruct1Interface> tbSame1SameStruct1InterfaceTraced = TbSame1::SameStruct1InterfaceTraceDecorator::connect(*tbSame1SameStruct1Interface, tracer);
    auto tbSame1SameStruct2Interface = std::make_shared<TbSame1::olink::SameStruct2InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame1SameStruct2Interface);
    std::unique_ptr<TbSame1::ISameStruct2Interface> tbSame1SameStruct2InterfaceTraced = TbSame1::SameStruct2InterfaceTraceDecorator::connect(*tbSame1SameStruct2Interface, tracer);
    auto tbSame1SameEnum1Interface = std::make_shared<TbSame1::olink::SameEnum1InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame1SameEnum1Interface);
    std::unique_ptr<TbSame1::ISameEnum1Interface> tbSame1SameEnum1InterfaceTraced = TbSame1::SameEnum1InterfaceTraceDecorator::connect(*tbSame1SameEnum1Interface, tracer);
    auto tbSame1SameEnum2Interface = std::make_shared<TbSame1::olink::SameEnum2InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame1SameEnum2Interface);
    std::unique_ptr<TbSame1::ISameEnum2Interface> tbSame1SameEnum2InterfaceTraced = TbSame1::SameEnum2InterfaceTraceDecorator::connect(*tbSame1SameEnum2Interface, tracer);
    auto tbSame2SameStruct1Interface = std::make_shared<TbSame2::olink::SameStruct1InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame2SameStruct1Interface);
    std::unique_ptr<TbSame2::ISameStruct1Interface> tbSame2SameStruct1InterfaceTraced = TbSame2::SameStruct1InterfaceTraceDecorator::connect(*tbSame2SameStruct1Interface, tracer);
    auto tbSame2SameStruct2Interface = std::make_shared<TbSame2::olink::SameStruct2InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame2SameStruct2Interface);
    std::unique_ptr<TbSame2::ISameStruct2Interface> tbSame2SameStruct2InterfaceTraced = TbSame2::SameStruct2InterfaceTraceDecorator::connect(*tbSame2SameStruct2Interface, tracer);
    auto tbSame2SameEnum1Interface = std::make_shared<TbSame2::olink::SameEnum1InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame2SameEnum1Interface);
    std::unique_ptr<TbSame2::ISameEnum1Interface> tbSame2SameEnum1InterfaceTraced = TbSame2::SameEnum1InterfaceTraceDecorator::connect(*tbSame2SameEnum1Interface, tracer);
    auto tbSame2SameEnum2Interface = std::make_shared<TbSame2::olink::SameEnum2InterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSame2SameEnum2Interface);
    std::unique_ptr<TbSame2::ISameEnum2Interface> tbSame2SameEnum2InterfaceTraced = TbSame2::SameEnum2InterfaceTraceDecorator::connect(*tbSame2SameEnum2Interface, tracer);
    auto tbSimpleVoidInterface = std::make_shared<TbSimple::olink::VoidInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSimpleVoidInterface);
    std::unique_ptr<TbSimple::IVoidInterface> tbSimpleVoidInterfaceTraced = TbSimple::VoidInterfaceTraceDecorator::connect(*tbSimpleVoidInterface, tracer);
    auto tbSimpleSimpleInterface = std::make_shared<TbSimple::olink::SimpleInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSimpleSimpleInterface);
    std::unique_ptr<TbSimple::ISimpleInterface> tbSimpleSimpleInterfaceTraced = TbSimple::SimpleInterfaceTraceDecorator::connect(*tbSimpleSimpleInterface, tracer);
    auto tbSimpleSimpleArrayInterface = std::make_shared<TbSimple::olink::SimpleArrayInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSimpleSimpleArrayInterface);
    std::unique_ptr<TbSimple::ISimpleArrayInterface> tbSimpleSimpleArrayInterfaceTraced = TbSimple::SimpleArrayInterfaceTraceDecorator::connect(*tbSimpleSimpleArrayInterface, tracer);
    auto tbSimpleNoPropertiesInterface = std::make_shared<TbSimple::olink::NoPropertiesInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSimpleNoPropertiesInterface);
    std::unique_ptr<TbSimple::INoPropertiesInterface> tbSimpleNoPropertiesInterfaceTraced = TbSimple::NoPropertiesInterfaceTraceDecorator::connect(*tbSimpleNoPropertiesInterface, tracer);
    auto tbSimpleNoOperationsInterface = std::make_shared<TbSimple::olink::NoOperationsInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSimpleNoOperationsInterface);
    std::unique_ptr<TbSimple::INoOperationsInterface> tbSimpleNoOperationsInterfaceTraced = TbSimple::NoOperationsInterfaceTraceDecorator::connect(*tbSimpleNoOperationsInterface, tracer);
    auto tbSimpleNoSignalsInterface = std::make_shared<TbSimple::olink::NoSignalsInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbSimpleNoSignalsInterface);
    std::unique_ptr<TbSimple::INoSignalsInterface> tbSimpleNoSignalsInterfaceTraced = TbSimple::NoSignalsInterfaceTraceDecorator::connect(*tbSimpleNoSignalsInterface, tracer);
    auto testbed1StructInterface = std::make_shared<Testbed1::olink::StructInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(testbed1StructInterface);
    std::unique_ptr<Testbed1::IStructInterface> testbed1StructInterfaceTraced = Testbed1::StructInterfaceTraceDecorator::connect(*testbed1StructInterface, tracer);
    auto testbed1StructArrayInterface = std::make_shared<Testbed1::olink::StructArrayInterfaceClient>();
    clientNetworkEndpoint.connectAndLinkObject(testbed1StructArrayInterface);
    std::unique_ptr<Testbed1::IStructArrayInterface> testbed1StructArrayInterfaceTraced = Testbed1::StructArrayInterfaceTraceDecorator::connect(*testbed1StructArrayInterface, tracer);
    auto tbNamesNamEs = std::make_shared<TbNames::olink::Nam_EsClient>();
    clientNetworkEndpoint.connectAndLinkObject(tbNamesNamEs);
    std::unique_ptr<TbNames::INamEs> tbNamesNamEsTraced = TbNames::NamEsTraceDecorator::connect(*tbNamesNamEs, tracer);
    auto counterCounter = std::make_shared<Counter::olink::CounterClient>();
    clientNetworkEndpoint.connectAndLinkObject(counterCounter);
    std::unique_ptr<Counter::ICounter> counterCounterTraced = Counter::CounterTraceDecorator::connect(*counterCounter, tracer);
    
    clientNetworkEndpoint.connectToHost(Poco::URI("ws://localhost:8000"));

    bool keepRunning = true;
    std::string cmd;
    do {
        std::cout << "Enter command:" << std::endl;
        getline (std::cin, cmd);

        if(cmd == "quit"){
            keepRunning = false;
            clientNetworkEndpoint.disconnect();
        }
    } while(keepRunning);
    clientNetworkEndpoint.disconnectAndUnlink(testbed2ManyParamInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(testbed2NestedStruct1Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(testbed2NestedStruct2Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(testbed2NestedStruct3Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbEnumEnumInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame1SameStruct1Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame1SameStruct2Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame1SameEnum1Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame1SameEnum2Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame2SameStruct1Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame2SameStruct2Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame2SameEnum1Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSame2SameEnum2Interface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSimpleVoidInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSimpleSimpleInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSimpleSimpleArrayInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSimpleNoPropertiesInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSimpleNoOperationsInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbSimpleNoSignalsInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(testbed1StructInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(testbed1StructArrayInterface->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(tbNamesNamEs->olinkObjectName());
    clientNetworkEndpoint.disconnectAndUnlink(counterCounter->olinkObjectName());

    return 0;
}
