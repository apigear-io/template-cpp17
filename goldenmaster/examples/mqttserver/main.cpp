
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
#include "tb_simple/implementation/emptyinterface.h"
#include "tb_simple/generated/mqtt/emptyinterfaceservice.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/mqtt/structinterfaceservice.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/mqtt/structarrayinterfaceservice.h"
#include "testbed1/implementation/structarray2interface.h"
#include "testbed1/generated/mqtt/structarray2interfaceservice.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/mqtt/namesservice.h"
#include "counter/implementation/counter.h"
#include "counter/generated/mqtt/counterservice.h"
#include "tb_struct_array/implementation/structarrayfieldinterface.h"
#include "tb_struct_array/generated/mqtt/structarrayfieldinterfaceservice.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/utilities/logger.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <functional>
#include <map>

namespace Examples {

using CommandHandler = std::function<void(const std::string& args)>;
using CommandMap = std::map<std::string, CommandHandler>;

inline ApiGear::Utilities::WriteLogFunc initLogging()
{
    ApiGear::Utilities::LogLevel logLevel = ApiGear::Utilities::LogLevel::Warning;
    if (const char* envLogLevel = std::getenv("LOG_LEVEL"))
    {
        int parsed = -1;
        std::istringstream iss(envLogLevel);
        if (!(iss >> parsed) || parsed < 0) {
            std::cerr << "Warning: invalid LOG_LEVEL=\"" << envLogLevel
                      << "\", using default (Warning)" << std::endl;
        } else if (parsed > static_cast<int>(ApiGear::Utilities::LogLevel::Error)) {
            ApiGear::Utilities::setLog(nullptr);
            return nullptr;
        } else {
            logLevel = static_cast<ApiGear::Utilities::LogLevel>(parsed);
        }
    }
    auto logFunc = ApiGear::Utilities::getConsoleLogFunc(logLevel);
    ApiGear::Utilities::setLog(logFunc);
    return logFunc;
}

inline void runCommandLoop(CommandMap commands, std::function<void()> onQuit)
{
    commands["help"] = [&](const std::string&) {
        std::cout << "Available commands:";
        for (const auto& [name, _] : commands) { std::cout << " " << name; }
        std::cout << " quit exit" << std::endl;
    };
    std::string line;
    std::cout << "Type \"help\" for available commands." << std::endl;
    while (std::getline(std::cin, line)) {
        auto start = line.find_first_not_of(" \t\r\n");
        auto end = line.find_last_not_of(" \t\r\n");
        if (start != std::string::npos) {
            line = line.substr(start, end - start + 1);
        } else {
            line.clear();
        }
        for (auto& c : line) { c = static_cast<char>(std::tolower(static_cast<unsigned char>(c))); }
        if (line == "quit" || line == "exit") {
            if (onQuit) { onQuit(); }
            return;
        }
        auto spacePos = line.find(' ');
        std::string cmd = (spacePos == std::string::npos) ? line : line.substr(0, spacePos);
        std::string args = (spacePos == std::string::npos) ? "" : line.substr(spacePos + 1);
        auto it = commands.find(cmd);
        if (it != commands.end()) {
            it->second(args);
        } else if (!cmd.empty()) {
            std::cout << "Unknown command: \"" << cmd
                      << "\". Type \"help\" for available commands." << std::endl;
        }
    }
    if (onQuit) { onQuit(); }
}

} // namespace Examples
#include <random>

using namespace Test;

int main(int argc, char* argv[]){

    // Parse command line arguments
    std::string host = "localhost";
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--host" && i + 1 < argc) { host = argv[++i]; }
        else if (arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [--host HOST]" << std::endl;
            return 0;
        }
    }

    auto logConsoleFunc = Examples::initLogging();
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
    std::shared_ptr<TbSimple::IEmptyInterface> testTbSimpleEmptyInterface = std::make_shared<TbSimple::EmptyInterface>();
    TbSimple::MQTT::EmptyInterfaceService testTbSimpleEmptyInterfaceService(testTbSimpleEmptyInterface, mqttservice);
    std::shared_ptr<Testbed1::IStructInterface> testTestbed1StructInterface = std::make_shared<Testbed1::StructInterface>();
    Testbed1::MQTT::StructInterfaceService testTestbed1StructInterfaceService(testTestbed1StructInterface, mqttservice);
    std::shared_ptr<Testbed1::IStructArrayInterface> testTestbed1StructArrayInterface = std::make_shared<Testbed1::StructArrayInterface>();
    Testbed1::MQTT::StructArrayInterfaceService testTestbed1StructArrayInterfaceService(testTestbed1StructArrayInterface, mqttservice);
    std::shared_ptr<Testbed1::IStructArray2Interface> testTestbed1StructArray2Interface = std::make_shared<Testbed1::StructArray2Interface>();
    Testbed1::MQTT::StructArray2InterfaceService testTestbed1StructArray2InterfaceService(testTestbed1StructArray2Interface, mqttservice);
    std::shared_ptr<TbNames::INamEs> testTbNamesNamEs = std::make_shared<TbNames::NamEs>();
    TbNames::MQTT::Nam_EsService testTbNamesNamEsService(testTbNamesNamEs, mqttservice);
    std::shared_ptr<Counter::ICounter> testCounterCounter = std::make_shared<Counter::Counter>();
    Counter::MQTT::CounterService testCounterCounterService(testCounterCounter, mqttservice);
    std::shared_ptr<TbStructArray::IStructArrayFieldInterface> testTbStructArrayStructArrayFieldInterface = std::make_shared<TbStructArray::StructArrayFieldInterface>();
    TbStructArray::MQTT::StructArrayFieldInterfaceService testTbStructArrayStructArrayFieldInterfaceService(testTbStructArrayStructArrayFieldInterface, mqttservice);

    // start mqtt connection
    mqttservice->connectToHost(host);

    Examples::runCommandLoop({}, [&](){
        mqttservice->disconnect();
    });

    return 0;
}
