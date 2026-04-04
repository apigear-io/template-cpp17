
#include "testbed2/implementation/manyparaminterface.h"
#include "testbed2/generated/nats/manyparaminterfaceservice.h"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "testbed2/generated/nats/nestedstruct1interfaceservice.h"
#include "testbed2/implementation/nestedstruct2interface.h"
#include "testbed2/generated/nats/nestedstruct2interfaceservice.h"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/nats/nestedstruct3interfaceservice.h"
#include "tb_enum/implementation/enuminterface.h"
#include "tb_enum/generated/nats/enuminterfaceservice.h"
#include "tb_same1/implementation/samestruct1interface.h"
#include "tb_same1/generated/nats/samestruct1interfaceservice.h"
#include "tb_same1/implementation/samestruct2interface.h"
#include "tb_same1/generated/nats/samestruct2interfaceservice.h"
#include "tb_same1/implementation/sameenum1interface.h"
#include "tb_same1/generated/nats/sameenum1interfaceservice.h"
#include "tb_same1/implementation/sameenum2interface.h"
#include "tb_same1/generated/nats/sameenum2interfaceservice.h"
#include "tb_same2/implementation/samestruct1interface.h"
#include "tb_same2/generated/nats/samestruct1interfaceservice.h"
#include "tb_same2/implementation/samestruct2interface.h"
#include "tb_same2/generated/nats/samestruct2interfaceservice.h"
#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/nats/sameenum1interfaceservice.h"
#include "tb_same2/implementation/sameenum2interface.h"
#include "tb_same2/generated/nats/sameenum2interfaceservice.h"
#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/nats/voidinterfaceservice.h"
#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/nats/simpleinterfaceservice.h"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/nats/simplearrayinterfaceservice.h"
#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/nats/nopropertiesinterfaceservice.h"
#include "tb_simple/implementation/nooperationsinterface.h"
#include "tb_simple/generated/nats/nooperationsinterfaceservice.h"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "tb_simple/generated/nats/nosignalsinterfaceservice.h"
#include "tb_simple/implementation/emptyinterface.h"
#include "tb_simple/generated/nats/emptyinterfaceservice.h"
#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/nats/structinterfaceservice.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/nats/structarrayinterfaceservice.h"
#include "testbed1/implementation/structarray2interface.h"
#include "testbed1/generated/nats/structarray2interfaceservice.h"
#include "tb_names/implementation/names.h"
#include "tb_names/generated/nats/namesservice.h"
#include "counter/implementation/counter.h"
#include "counter/generated/nats/counterservice.h"
#include "tb_struct_array/implementation/structarrayfieldinterface.h"
#include "tb_struct_array/generated/nats/structarrayfieldinterfaceservice.h"
#include "apigear/nats/natsservice.h"
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

using namespace Test;

int main(int argc, char* argv[]){

    // Parse command line arguments
    std::string url = "nats://localhost:4222";
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--url" && i + 1 < argc) { url = argv[++i]; }
        else if (arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [--url URL]" << std::endl;
            return 0;
        }
    }

    Examples::initLogging();
    auto service = std::make_shared<ApiGear::Nats::Service>();

    // set up modules
    std::shared_ptr<Testbed2::IManyParamInterface> testTestbed2ManyParamInterface = std::make_shared<Testbed2::ManyParamInterface>();
    auto testTestbed2ManyParamInterfaceService = Testbed2::Nats::ManyParamInterfaceService::create(testTestbed2ManyParamInterface, service);
    std::shared_ptr<Testbed2::INestedStruct1Interface> testTestbed2NestedStruct1Interface = std::make_shared<Testbed2::NestedStruct1Interface>();
    auto testTestbed2NestedStruct1InterfaceService = Testbed2::Nats::NestedStruct1InterfaceService::create(testTestbed2NestedStruct1Interface, service);
    std::shared_ptr<Testbed2::INestedStruct2Interface> testTestbed2NestedStruct2Interface = std::make_shared<Testbed2::NestedStruct2Interface>();
    auto testTestbed2NestedStruct2InterfaceService = Testbed2::Nats::NestedStruct2InterfaceService::create(testTestbed2NestedStruct2Interface, service);
    std::shared_ptr<Testbed2::INestedStruct3Interface> testTestbed2NestedStruct3Interface = std::make_shared<Testbed2::NestedStruct3Interface>();
    auto testTestbed2NestedStruct3InterfaceService = Testbed2::Nats::NestedStruct3InterfaceService::create(testTestbed2NestedStruct3Interface, service);
    std::shared_ptr<TbEnum::IEnumInterface> testTbEnumEnumInterface = std::make_shared<TbEnum::EnumInterface>();
    auto testTbEnumEnumInterfaceService = TbEnum::Nats::EnumInterfaceService::create(testTbEnumEnumInterface, service);
    std::shared_ptr<TbSame1::ISameStruct1Interface> testTbSame1SameStruct1Interface = std::make_shared<TbSame1::SameStruct1Interface>();
    auto testTbSame1SameStruct1InterfaceService = TbSame1::Nats::SameStruct1InterfaceService::create(testTbSame1SameStruct1Interface, service);
    std::shared_ptr<TbSame1::ISameStruct2Interface> testTbSame1SameStruct2Interface = std::make_shared<TbSame1::SameStruct2Interface>();
    auto testTbSame1SameStruct2InterfaceService = TbSame1::Nats::SameStruct2InterfaceService::create(testTbSame1SameStruct2Interface, service);
    std::shared_ptr<TbSame1::ISameEnum1Interface> testTbSame1SameEnum1Interface = std::make_shared<TbSame1::SameEnum1Interface>();
    auto testTbSame1SameEnum1InterfaceService = TbSame1::Nats::SameEnum1InterfaceService::create(testTbSame1SameEnum1Interface, service);
    std::shared_ptr<TbSame1::ISameEnum2Interface> testTbSame1SameEnum2Interface = std::make_shared<TbSame1::SameEnum2Interface>();
    auto testTbSame1SameEnum2InterfaceService = TbSame1::Nats::SameEnum2InterfaceService::create(testTbSame1SameEnum2Interface, service);
    std::shared_ptr<TbSame2::ISameStruct1Interface> testTbSame2SameStruct1Interface = std::make_shared<TbSame2::SameStruct1Interface>();
    auto testTbSame2SameStruct1InterfaceService = TbSame2::Nats::SameStruct1InterfaceService::create(testTbSame2SameStruct1Interface, service);
    std::shared_ptr<TbSame2::ISameStruct2Interface> testTbSame2SameStruct2Interface = std::make_shared<TbSame2::SameStruct2Interface>();
    auto testTbSame2SameStruct2InterfaceService = TbSame2::Nats::SameStruct2InterfaceService::create(testTbSame2SameStruct2Interface, service);
    std::shared_ptr<TbSame2::ISameEnum1Interface> testTbSame2SameEnum1Interface = std::make_shared<TbSame2::SameEnum1Interface>();
    auto testTbSame2SameEnum1InterfaceService = TbSame2::Nats::SameEnum1InterfaceService::create(testTbSame2SameEnum1Interface, service);
    std::shared_ptr<TbSame2::ISameEnum2Interface> testTbSame2SameEnum2Interface = std::make_shared<TbSame2::SameEnum2Interface>();
    auto testTbSame2SameEnum2InterfaceService = TbSame2::Nats::SameEnum2InterfaceService::create(testTbSame2SameEnum2Interface, service);
    std::shared_ptr<TbSimple::IVoidInterface> testTbSimpleVoidInterface = std::make_shared<TbSimple::VoidInterface>();
    auto testTbSimpleVoidInterfaceService = TbSimple::Nats::VoidInterfaceService::create(testTbSimpleVoidInterface, service);
    std::shared_ptr<TbSimple::ISimpleInterface> testTbSimpleSimpleInterface = std::make_shared<TbSimple::SimpleInterface>();
    auto testTbSimpleSimpleInterfaceService = TbSimple::Nats::SimpleInterfaceService::create(testTbSimpleSimpleInterface, service);
    std::shared_ptr<TbSimple::ISimpleArrayInterface> testTbSimpleSimpleArrayInterface = std::make_shared<TbSimple::SimpleArrayInterface>();
    auto testTbSimpleSimpleArrayInterfaceService = TbSimple::Nats::SimpleArrayInterfaceService::create(testTbSimpleSimpleArrayInterface, service);
    std::shared_ptr<TbSimple::INoPropertiesInterface> testTbSimpleNoPropertiesInterface = std::make_shared<TbSimple::NoPropertiesInterface>();
    auto testTbSimpleNoPropertiesInterfaceService = TbSimple::Nats::NoPropertiesInterfaceService::create(testTbSimpleNoPropertiesInterface, service);
    std::shared_ptr<TbSimple::INoOperationsInterface> testTbSimpleNoOperationsInterface = std::make_shared<TbSimple::NoOperationsInterface>();
    auto testTbSimpleNoOperationsInterfaceService = TbSimple::Nats::NoOperationsInterfaceService::create(testTbSimpleNoOperationsInterface, service);
    std::shared_ptr<TbSimple::INoSignalsInterface> testTbSimpleNoSignalsInterface = std::make_shared<TbSimple::NoSignalsInterface>();
    auto testTbSimpleNoSignalsInterfaceService = TbSimple::Nats::NoSignalsInterfaceService::create(testTbSimpleNoSignalsInterface, service);
    std::shared_ptr<TbSimple::IEmptyInterface> testTbSimpleEmptyInterface = std::make_shared<TbSimple::EmptyInterface>();
    auto testTbSimpleEmptyInterfaceService = TbSimple::Nats::EmptyInterfaceService::create(testTbSimpleEmptyInterface, service);
    std::shared_ptr<Testbed1::IStructInterface> testTestbed1StructInterface = std::make_shared<Testbed1::StructInterface>();
    auto testTestbed1StructInterfaceService = Testbed1::Nats::StructInterfaceService::create(testTestbed1StructInterface, service);
    std::shared_ptr<Testbed1::IStructArrayInterface> testTestbed1StructArrayInterface = std::make_shared<Testbed1::StructArrayInterface>();
    auto testTestbed1StructArrayInterfaceService = Testbed1::Nats::StructArrayInterfaceService::create(testTestbed1StructArrayInterface, service);
    std::shared_ptr<Testbed1::IStructArray2Interface> testTestbed1StructArray2Interface = std::make_shared<Testbed1::StructArray2Interface>();
    auto testTestbed1StructArray2InterfaceService = Testbed1::Nats::StructArray2InterfaceService::create(testTestbed1StructArray2Interface, service);
    std::shared_ptr<TbNames::INamEs> testTbNamesNamEs = std::make_shared<TbNames::NamEs>();
    auto testTbNamesNamEsService = TbNames::Nats::Nam_EsService::create(testTbNamesNamEs, service);
    std::shared_ptr<Counter::ICounter> testCounterCounter = std::make_shared<Counter::Counter>();
    auto testCounterCounterService = Counter::Nats::CounterService::create(testCounterCounter, service);
    std::shared_ptr<TbStructArray::IStructArrayFieldInterface> testTbStructArrayStructArrayFieldInterface = std::make_shared<TbStructArray::StructArrayFieldInterface>();
    auto testTbStructArrayStructArrayFieldInterfaceService = TbStructArray::Nats::StructArrayFieldInterfaceService::create(testTbStructArrayStructArrayFieldInterface, service);

    service->connect(url);

    Examples::runCommandLoop({}, [&](){
        service->disconnect();
    });

    return 0;
}
