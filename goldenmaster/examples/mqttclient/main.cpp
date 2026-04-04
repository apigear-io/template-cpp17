
#include "testbed2/generated/mqtt/manyparaminterfaceclient.h"
#include "testbed2/generated/mqtt/nestedstruct1interfaceclient.h"
#include "testbed2/generated/mqtt/nestedstruct2interfaceclient.h"
#include "testbed2/generated/mqtt/nestedstruct3interfaceclient.h"
#include "tb_enum/generated/mqtt/enuminterfaceclient.h"
#include "tb_same1/generated/mqtt/samestruct1interfaceclient.h"
#include "tb_same1/generated/mqtt/samestruct2interfaceclient.h"
#include "tb_same1/generated/mqtt/sameenum1interfaceclient.h"
#include "tb_same1/generated/mqtt/sameenum2interfaceclient.h"
#include "tb_same2/generated/mqtt/samestruct1interfaceclient.h"
#include "tb_same2/generated/mqtt/samestruct2interfaceclient.h"
#include "tb_same2/generated/mqtt/sameenum1interfaceclient.h"
#include "tb_same2/generated/mqtt/sameenum2interfaceclient.h"
#include "tb_simple/generated/mqtt/voidinterfaceclient.h"
#include "tb_simple/generated/mqtt/simpleinterfaceclient.h"
#include "tb_simple/generated/mqtt/simplearrayinterfaceclient.h"
#include "tb_simple/generated/mqtt/nopropertiesinterfaceclient.h"
#include "tb_simple/generated/mqtt/nooperationsinterfaceclient.h"
#include "tb_simple/generated/mqtt/nosignalsinterfaceclient.h"
#include "tb_simple/generated/mqtt/emptyinterfaceclient.h"
#include "testbed1/generated/mqtt/structinterfaceclient.h"
#include "testbed1/generated/mqtt/structarrayinterfaceclient.h"
#include "testbed1/generated/mqtt/structarray2interfaceclient.h"
#include "tb_names/generated/mqtt/namesclient.h"
#include "counter/generated/mqtt/counterclient.h"
#include "tb_struct_array/generated/mqtt/structarrayfieldinterfaceclient.h"
#include "apigear/mqtt/mqttclient.h"
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
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("testClient"+std::to_string(randomId));

    // set up modules
    std::unique_ptr<Testbed2::IManyParamInterface> testTestbed2ManyParamInterface = std::make_unique<Testbed2::MQTT::ManyParamInterfaceClient>(mqttclient);
    std::unique_ptr<Testbed2::INestedStruct1Interface> testTestbed2NestedStruct1Interface = std::make_unique<Testbed2::MQTT::NestedStruct1InterfaceClient>(mqttclient);
    std::unique_ptr<Testbed2::INestedStruct2Interface> testTestbed2NestedStruct2Interface = std::make_unique<Testbed2::MQTT::NestedStruct2InterfaceClient>(mqttclient);
    std::unique_ptr<Testbed2::INestedStruct3Interface> testTestbed2NestedStruct3Interface = std::make_unique<Testbed2::MQTT::NestedStruct3InterfaceClient>(mqttclient);
    std::unique_ptr<TbEnum::IEnumInterface> testTbEnumEnumInterface = std::make_unique<TbEnum::MQTT::EnumInterfaceClient>(mqttclient);
    std::unique_ptr<TbSame1::ISameStruct1Interface> testTbSame1SameStruct1Interface = std::make_unique<TbSame1::MQTT::SameStruct1InterfaceClient>(mqttclient);
    std::unique_ptr<TbSame1::ISameStruct2Interface> testTbSame1SameStruct2Interface = std::make_unique<TbSame1::MQTT::SameStruct2InterfaceClient>(mqttclient);
    std::unique_ptr<TbSame1::ISameEnum1Interface> testTbSame1SameEnum1Interface = std::make_unique<TbSame1::MQTT::SameEnum1InterfaceClient>(mqttclient);
    std::unique_ptr<TbSame1::ISameEnum2Interface> testTbSame1SameEnum2Interface = std::make_unique<TbSame1::MQTT::SameEnum2InterfaceClient>(mqttclient);
    std::unique_ptr<TbSame2::ISameStruct1Interface> testTbSame2SameStruct1Interface = std::make_unique<TbSame2::MQTT::SameStruct1InterfaceClient>(mqttclient);
    std::unique_ptr<TbSame2::ISameStruct2Interface> testTbSame2SameStruct2Interface = std::make_unique<TbSame2::MQTT::SameStruct2InterfaceClient>(mqttclient);
    std::unique_ptr<TbSame2::ISameEnum1Interface> testTbSame2SameEnum1Interface = std::make_unique<TbSame2::MQTT::SameEnum1InterfaceClient>(mqttclient);
    std::unique_ptr<TbSame2::ISameEnum2Interface> testTbSame2SameEnum2Interface = std::make_unique<TbSame2::MQTT::SameEnum2InterfaceClient>(mqttclient);
    std::unique_ptr<TbSimple::IVoidInterface> testTbSimpleVoidInterface = std::make_unique<TbSimple::MQTT::VoidInterfaceClient>(mqttclient);
    std::unique_ptr<TbSimple::ISimpleInterface> testTbSimpleSimpleInterface = std::make_unique<TbSimple::MQTT::SimpleInterfaceClient>(mqttclient);
    std::unique_ptr<TbSimple::ISimpleArrayInterface> testTbSimpleSimpleArrayInterface = std::make_unique<TbSimple::MQTT::SimpleArrayInterfaceClient>(mqttclient);
    std::unique_ptr<TbSimple::INoPropertiesInterface> testTbSimpleNoPropertiesInterface = std::make_unique<TbSimple::MQTT::NoPropertiesInterfaceClient>(mqttclient);
    std::unique_ptr<TbSimple::INoOperationsInterface> testTbSimpleNoOperationsInterface = std::make_unique<TbSimple::MQTT::NoOperationsInterfaceClient>(mqttclient);
    std::unique_ptr<TbSimple::INoSignalsInterface> testTbSimpleNoSignalsInterface = std::make_unique<TbSimple::MQTT::NoSignalsInterfaceClient>(mqttclient);
    std::unique_ptr<TbSimple::IEmptyInterface> testTbSimpleEmptyInterface = std::make_unique<TbSimple::MQTT::EmptyInterfaceClient>(mqttclient);
    std::unique_ptr<Testbed1::IStructInterface> testTestbed1StructInterface = std::make_unique<Testbed1::MQTT::StructInterfaceClient>(mqttclient);
    std::unique_ptr<Testbed1::IStructArrayInterface> testTestbed1StructArrayInterface = std::make_unique<Testbed1::MQTT::StructArrayInterfaceClient>(mqttclient);
    std::unique_ptr<Testbed1::IStructArray2Interface> testTestbed1StructArray2Interface = std::make_unique<Testbed1::MQTT::StructArray2InterfaceClient>(mqttclient);
    std::unique_ptr<TbNames::INamEs> testTbNamesNamEs = std::make_unique<TbNames::MQTT::Nam_EsClient>(mqttclient);
    std::unique_ptr<Counter::ICounter> testCounterCounter = std::make_unique<Counter::MQTT::CounterClient>(mqttclient);
    std::unique_ptr<TbStructArray::IStructArrayFieldInterface> testTbStructArrayStructArrayFieldInterface = std::make_unique<TbStructArray::MQTT::StructArrayFieldInterfaceClient>(mqttclient);

    // start mqtt connection
    mqttclient->connectToHost(host);

    Examples::runCommandLoop({}, [&](){
        mqttclient->disconnect();
    });

    return 0;
}
