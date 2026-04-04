
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
#include "tb_simple/generated/nats/emptyinterfaceclient.h"
#include "testbed1/generated/nats/structinterfaceclient.h"
#include "testbed1/generated/nats/structarrayinterfaceclient.h"
#include "testbed1/generated/nats/structarray2interfaceclient.h"
#include "tb_names/generated/nats/namesclient.h"
#include "counter/generated/nats/counterclient.h"
#include "tb_struct_array/generated/nats/structarrayfieldinterfaceclient.h"
#include "apigear/utilities/logger.h"
#include "apigear/nats/natsclient.h"
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
    auto testTbSimpleEmptyInterface = TbSimple::Nats::EmptyInterfaceClient::create(client);
    auto testTestbed1StructInterface = Testbed1::Nats::StructInterfaceClient::create(client);
    auto testTestbed1StructArrayInterface = Testbed1::Nats::StructArrayInterfaceClient::create(client);
    auto testTestbed1StructArray2Interface = Testbed1::Nats::StructArray2InterfaceClient::create(client);
    auto testTbNamesNamEs = TbNames::Nats::Nam_EsClient::create(client);
    auto testCounterCounter = Counter::Nats::CounterClient::create(client);
    auto testTbStructArrayStructArrayFieldInterface = TbStructArray::Nats::StructArrayFieldInterfaceClient::create(client);


    
    // Try out properties: subscribe for changes
    testTestbed2ManyParamInterface->_getPublisher().subscribeToProp1Changed([](auto value){ std::cout << " Prop1 " << std::endl; });

    // or ask for change, when object is ready
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
    client->connect(url);

    Examples::runCommandLoop({}, [&](){
        client->disconnect();
    });

    return 0;
}
