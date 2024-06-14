#include <iostream>
#include "testbed2/implementation/manyparaminterface.h"
#include "testbed2/generated/mqtt/manyparaminterfaceservice.h"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "testbed2/generated/mqtt/nestedstruct1interfaceservice.h"
#include "testbed2/implementation/nestedstruct2interface.h"
#include "testbed2/generated/mqtt/nestedstruct2interfaceservice.h"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/mqtt/nestedstruct3interfaceservice.h"
#include "tb_enum/implementation/enuminterface.h"
#include "tb_enum/generated/mqtt/enuminterfaceservice.h"
#include "tb_same1/implementation/samestruct1interface.h"
#include "tb_same1/generated/mqtt/samestruct1interfaceservice.h"
#include "tb_same1/implementation/samestruct2interface.h"
#include "tb_same1/generated/mqtt/samestruct2interfaceservice.h"
#include "tb_same1/implementation/sameenum1interface.h"
#include "tb_same1/generated/mqtt/sameenum1interfaceservice.h"
#include "tb_same1/implementation/sameenum2interface.h"
#include "tb_same1/generated/mqtt/sameenum2interfaceservice.h"
#include "tb_same2/implementation/samestruct1interface.h"
#include "tb_same2/generated/mqtt/samestruct1interfaceservice.h"
#include "tb_same2/implementation/samestruct2interface.h"
#include "tb_same2/generated/mqtt/samestruct2interfaceservice.h"
#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/mqtt/sameenum1interfaceservice.h"
#include "tb_same2/implementation/sameenum2interface.h"
#include "tb_same2/generated/mqtt/sameenum2interfaceservice.h"
#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/mqtt/voidinterfaceservice.h"
#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/mqtt/simpleinterfaceservice.h"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/mqtt/simplearrayinterfaceservice.h"
#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/mqtt/nopropertiesinterfaceservice.h"
#include "tb_simple/implementation/nooperationsinterface.h"
#include "tb_simple/generated/mqtt/nooperationsinterfaceservice.h"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/mqtt/nosignalsinterfaceservice.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/mqtt/structinterfaceservice.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/mqtt/structarrayinterfaceservice.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/mqtt/namesservice.h"
#include "counter/implementation/counter.h"
#include "counter/generated/mqtt/counterservice.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/utilities/logger.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <random>

using namespace Test;

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
    auto logConsoleFunc = getLogging();
    std::mt19937 randomNumberGenerator (std::random_device{}());
    std::uniform_int_distribution<> distribution (0, 100000);

    auto randomId = distribution(randomNumberGenerator);
    // MQTT clients need to have unique identifiers
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("testServer"+std::to_string(randomId));

    // set up modules
    std::shared_ptr<Testbed2::IManyParamInterface> testTestbed2ManyParamInterface = std::make_shared<Testbed2::ManyParamInterface>();
    Testbed2::MQTT::ManyParamInterfaceService testTestbed2ManyParamInterfaceService(testTestbed2ManyParamInterface, mqttservice);
    std::shared_ptr<Testbed2::INestedStruct1Interface> testTestbed2NestedStruct1Interface = std::make_shared<Testbed2::NestedStruct1Interface>();
    Testbed2::MQTT::NestedStruct1InterfaceService testTestbed2NestedStruct1InterfaceService(testTestbed2NestedStruct1Interface, mqttservice);
    std::shared_ptr<Testbed2::INestedStruct2Interface> testTestbed2NestedStruct2Interface = std::make_shared<Testbed2::NestedStruct2Interface>();
    Testbed2::MQTT::NestedStruct2InterfaceService testTestbed2NestedStruct2InterfaceService(testTestbed2NestedStruct2Interface, mqttservice);
    std::shared_ptr<Testbed2::INestedStruct3Interface> testTestbed2NestedStruct3Interface = std::make_shared<Testbed2::NestedStruct3Interface>();
    Testbed2::MQTT::NestedStruct3InterfaceService testTestbed2NestedStruct3InterfaceService(testTestbed2NestedStruct3Interface, mqttservice);
    std::shared_ptr<TbEnum::IEnumInterface> testTbEnumEnumInterface = std::make_shared<TbEnum::EnumInterface>();
    TbEnum::MQTT::EnumInterfaceService testTbEnumEnumInterfaceService(testTbEnumEnumInterface, mqttservice);
    std::shared_ptr<TbSame1::ISameStruct1Interface> testTbSame1SameStruct1Interface = std::make_shared<TbSame1::SameStruct1Interface>();
    TbSame1::MQTT::SameStruct1InterfaceService testTbSame1SameStruct1InterfaceService(testTbSame1SameStruct1Interface, mqttservice);
    std::shared_ptr<TbSame1::ISameStruct2Interface> testTbSame1SameStruct2Interface = std::make_shared<TbSame1::SameStruct2Interface>();
    TbSame1::MQTT::SameStruct2InterfaceService testTbSame1SameStruct2InterfaceService(testTbSame1SameStruct2Interface, mqttservice);
    std::shared_ptr<TbSame1::ISameEnum1Interface> testTbSame1SameEnum1Interface = std::make_shared<TbSame1::SameEnum1Interface>();
    TbSame1::MQTT::SameEnum1InterfaceService testTbSame1SameEnum1InterfaceService(testTbSame1SameEnum1Interface, mqttservice);
    std::shared_ptr<TbSame1::ISameEnum2Interface> testTbSame1SameEnum2Interface = std::make_shared<TbSame1::SameEnum2Interface>();
    TbSame1::MQTT::SameEnum2InterfaceService testTbSame1SameEnum2InterfaceService(testTbSame1SameEnum2Interface, mqttservice);
    std::shared_ptr<TbSame2::ISameStruct1Interface> testTbSame2SameStruct1Interface = std::make_shared<TbSame2::SameStruct1Interface>();
    TbSame2::MQTT::SameStruct1InterfaceService testTbSame2SameStruct1InterfaceService(testTbSame2SameStruct1Interface, mqttservice);
    std::shared_ptr<TbSame2::ISameStruct2Interface> testTbSame2SameStruct2Interface = std::make_shared<TbSame2::SameStruct2Interface>();
    TbSame2::MQTT::SameStruct2InterfaceService testTbSame2SameStruct2InterfaceService(testTbSame2SameStruct2Interface, mqttservice);
    std::shared_ptr<TbSame2::ISameEnum1Interface> testTbSame2SameEnum1Interface = std::make_shared<TbSame2::SameEnum1Interface>();
    TbSame2::MQTT::SameEnum1InterfaceService testTbSame2SameEnum1InterfaceService(testTbSame2SameEnum1Interface, mqttservice);
    std::shared_ptr<TbSame2::ISameEnum2Interface> testTbSame2SameEnum2Interface = std::make_shared<TbSame2::SameEnum2Interface>();
    TbSame2::MQTT::SameEnum2InterfaceService testTbSame2SameEnum2InterfaceService(testTbSame2SameEnum2Interface, mqttservice);
    std::shared_ptr<TbSimple::IVoidInterface> testTbSimpleVoidInterface = std::make_shared<TbSimple::VoidInterface>();
    TbSimple::MQTT::VoidInterfaceService testTbSimpleVoidInterfaceService(testTbSimpleVoidInterface, mqttservice);
    std::shared_ptr<TbSimple::ISimpleInterface> testTbSimpleSimpleInterface = std::make_shared<TbSimple::SimpleInterface>();
    TbSimple::MQTT::SimpleInterfaceService testTbSimpleSimpleInterfaceService(testTbSimpleSimpleInterface, mqttservice);
    std::shared_ptr<TbSimple::ISimpleArrayInterface> testTbSimpleSimpleArrayInterface = std::make_shared<TbSimple::SimpleArrayInterface>();
    TbSimple::MQTT::SimpleArrayInterfaceService testTbSimpleSimpleArrayInterfaceService(testTbSimpleSimpleArrayInterface, mqttservice);
    std::shared_ptr<TbSimple::INoPropertiesInterface> testTbSimpleNoPropertiesInterface = std::make_shared<TbSimple::NoPropertiesInterface>();
    TbSimple::MQTT::NoPropertiesInterfaceService testTbSimpleNoPropertiesInterfaceService(testTbSimpleNoPropertiesInterface, mqttservice);
    std::shared_ptr<TbSimple::INoOperationsInterface> testTbSimpleNoOperationsInterface = std::make_shared<TbSimple::NoOperationsInterface>();
    TbSimple::MQTT::NoOperationsInterfaceService testTbSimpleNoOperationsInterfaceService(testTbSimpleNoOperationsInterface, mqttservice);
    std::shared_ptr<TbSimple::INoSignalsInterface> testTbSimpleNoSignalsInterface = std::make_shared<TbSimple::NoSignalsInterface>();
    TbSimple::MQTT::NoSignalsInterfaceService testTbSimpleNoSignalsInterfaceService(testTbSimpleNoSignalsInterface, mqttservice);
    std::shared_ptr<Testbed1::IStructInterface> testTestbed1StructInterface = std::make_shared<Testbed1::StructInterface>();
    Testbed1::MQTT::StructInterfaceService testTestbed1StructInterfaceService(testTestbed1StructInterface, mqttservice);
    std::shared_ptr<Testbed1::IStructArrayInterface> testTestbed1StructArrayInterface = std::make_shared<Testbed1::StructArrayInterface>();
    Testbed1::MQTT::StructArrayInterfaceService testTestbed1StructArrayInterfaceService(testTestbed1StructArrayInterface, mqttservice);
    std::shared_ptr<TbNames::INamEs> testTbNamesNamEs = std::make_shared<TbNames::NamEs>();
    TbNames::MQTT::Nam_EsService testTbNamesNamEsService(testTbNamesNamEs, mqttservice);
    std::shared_ptr<Counter::ICounter> testCounterCounter = std::make_shared<Counter::Counter>();
    Counter::MQTT::CounterService testCounterCounterService(testCounterCounter, mqttservice);

    // start mqtt connection
    mqttservice->connectToHost("");

    bool keepRunning = true;
    std::string cmd;
    do {
        std::cout << "Enter command:" << std::endl;
        getline (std::cin, cmd);

        if(cmd == "quit"){
            mqttservice->disconnect();
            keepRunning = false;
        } else {
        }
    } while(keepRunning);

    return 0;
}
