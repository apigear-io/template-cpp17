
#include "testbed2/generated/nats/manyparaminterfaceclient.h"
#include "testbed2/generated/nats/nestedstruct1interfaceclient.h"
#include "testbed2/generated/nats/nestedstruct2interfaceclient.h"
#include "testbed2/generated/nats/nestedstruct3interfaceclient.h"
#include "tb_enum/generated/nats/enuminterfaceclient.h"
#include "tb_same1/generated/nats/samestruct1interfaceclient.h"
#include "tb_same1/generated/nats/samestruct2interfaceclient.h"
#include "tb_same1/generated/nats/sameenum1interfaceclient.h"
#include "tb_same1/generated/nats/sameenum2interfaceclient.h"
#include "tb_same2/generated/nats/samestruct1interfaceclient.h"
#include "tb_same2/generated/nats/samestruct2interfaceclient.h"
#include "tb_same2/generated/nats/sameenum1interfaceclient.h"
#include "tb_same2/generated/nats/sameenum2interfaceclient.h"
#include "tb_simple/generated/nats/voidinterfaceclient.h"
#include "tb_simple/generated/nats/simpleinterfaceclient.h"
#include "tb_simple/generated/nats/simplearrayinterfaceclient.h"
#include "tb_simple/generated/nats/nopropertiesinterfaceclient.h"
#include "tb_simple/generated/nats/nooperationsinterfaceclient.h"
#include "tb_simple/generated/nats/nosignalsinterfaceclient.h"
#include "testbed1/generated/nats/structinterfaceclient.h"
#include "testbed1/generated/nats/structarrayinterfaceclient.h"
#include "tb_names/generated/nats/namesclient.h"
#include "counter/generated/nats/counterclient.h"
#include "apigear/utilities/logger.h"
#include <iostream>
#include "apigear/nats/natsclient.h"

using namespace Test;

ApiGear::Utilities::WriteLogFunc getLogging(){

    ApiGear::Utilities::WriteLogFunc logConsoleFunc = nullptr;
    ApiGear::Utilities::LogLevel logLevel = ApiGear::Utilities::LogLevel::Warning;

    logConsoleFunc = ApiGear::Utilities::getConsoleLogFunc(logLevel);
    // check whether logging was disabled
    if (logLevel > ApiGear::Utilities::LogLevel::Error) {
        logConsoleFunc = nullptr;
    }

    // set global log function
    ApiGear::Utilities::setLog(logConsoleFunc);

    return logConsoleFunc;
}

int main(){

    auto client = std::make_shared<ApiGear::Nats::Client>();

    // set up modules
    auto testTestbed2ManyParamInterface = Testbed2::Nats::ManyParamInterfaceClient::create(client);
    auto testTestbed2NestedStruct1Interface = Testbed2::Nats::NestedStruct1InterfaceClient::create(client);
    auto testTestbed2NestedStruct2Interface = Testbed2::Nats::NestedStruct2InterfaceClient::create(client);
    auto testTestbed2NestedStruct3Interface = Testbed2::Nats::NestedStruct3InterfaceClient::create(client);
    auto testTbEnumEnumInterface = TbEnum::Nats::EnumInterfaceClient::create(client);
    auto testTbSame1SameStruct1Interface = TbSame1::Nats::SameStruct1InterfaceClient::create(client);
    auto testTbSame1SameStruct2Interface = TbSame1::Nats::SameStruct2InterfaceClient::create(client);
    auto testTbSame1SameEnum1Interface = TbSame1::Nats::SameEnum1InterfaceClient::create(client);
    auto testTbSame1SameEnum2Interface = TbSame1::Nats::SameEnum2InterfaceClient::create(client);
    auto testTbSame2SameStruct1Interface = TbSame2::Nats::SameStruct1InterfaceClient::create(client);
    auto testTbSame2SameStruct2Interface = TbSame2::Nats::SameStruct2InterfaceClient::create(client);
    auto testTbSame2SameEnum1Interface = TbSame2::Nats::SameEnum1InterfaceClient::create(client);
    auto testTbSame2SameEnum2Interface = TbSame2::Nats::SameEnum2InterfaceClient::create(client);
    auto testTbSimpleVoidInterface = TbSimple::Nats::VoidInterfaceClient::create(client);
    auto testTbSimpleSimpleInterface = TbSimple::Nats::SimpleInterfaceClient::create(client);
    auto testTbSimpleSimpleArrayInterface = TbSimple::Nats::SimpleArrayInterfaceClient::create(client);
    auto testTbSimpleNoPropertiesInterface = TbSimple::Nats::NoPropertiesInterfaceClient::create(client);
    auto testTbSimpleNoOperationsInterface = TbSimple::Nats::NoOperationsInterfaceClient::create(client);
    auto testTbSimpleNoSignalsInterface = TbSimple::Nats::NoSignalsInterfaceClient::create(client);
    auto testTestbed1StructInterface = Testbed1::Nats::StructInterfaceClient::create(client);
    auto testTestbed1StructArrayInterface = Testbed1::Nats::StructArrayInterfaceClient::create(client);
    auto testTbNamesNamEs = TbNames::Nats::Nam_EsClient::create(client);
    auto testCounterCounter = Counter::Nats::CounterClient::create(client);

   
    
    // Try out properties: subscribe for changes
    testTestbed2ManyParamInterface->_getPublisher().subscribeToProp1Changed([](auto value){ std::cout << " Prop1 " << std::endl; });

    // or ask for change, when objest is ready
    auto idSubProp = testTestbed2ManyParamInterface->_subscribeForIsReady(
        [testTestbed2ManyParamInterface](bool connected) 
        {
            if (!connected)
            {
                return;
            }
            auto local_prop1 = 0;//TODO change this value to non default!
            std::cout << " is ready!" << std::endl;
            testTestbed2ManyParamInterface->setProp1(local_prop1);
        });
    
    // Check the signals with subscribing for its change. Emit the signal from server side.
    testTestbed2ManyParamInterface->_getPublisher().subscribeToSig1([](int param1){ std::cout << " Sig1 " << std::endl; });
    
    // Play around executing your operations
    auto idSubOperation = testTestbed2ManyParamInterface->_subscribeForIsReady(
        [testTestbed2ManyParamInterface](bool connected) 
        {
            if (!connected)
            {
                return;
            }
            auto method_result =  testTestbed2ManyParamInterface->func1(0);
        });
    

    //connect
    client->connect("nats://localhost:4222");

    bool keepRunning = true;
    std::string cmd;
    do {
        std::cout << "Enter command:" << std::endl;
        getline (std::cin, cmd);

        if(cmd == "quit"){
            client->disconnect();
            keepRunning = false;
        } else {

        }
    } while(keepRunning);

    return 0;
}
