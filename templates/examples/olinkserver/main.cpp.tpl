{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
#include "{{snake $module.Name}}/implementation/{{ lower ( camel $interface.Name) }}.h"
#include "{{snake $module.Name}}/generated/olink/{{ lower ( camel $interface.Name) }}service.h"
#include "{{snake $module.Name}}/generated/core/{{ lower ( camel $interface.Name) }}.threadsafedecorator.h"
{{- end }}
{{- end }}

#include "apigear/olink/olinklogadapter.h"
#include "olink/remoteregistry.h"
#include "apigear/olink/olinkhost.h"
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

using namespace {{ Camel .System.Name }};

int main(int argc, char* argv[]){

    // Parse command line arguments
    int port = 8000;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--port" && i + 1 < argc) { port = std::stoi(argv[++i]); }
        else if (arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [--port PORT]" << std::endl;
            return 0;
        }
    }

    ApiGear::ObjectLink::RemoteRegistry registry;
    auto logConsoleFunc = Examples::initLogging();
    registry.onLog(ApiGear::Utilities::logAdapter(logConsoleFunc));

    ApiGear::PocoImpl::OLinkHost testserver(registry, ApiGear::Utilities::logAdapter(logConsoleFunc));

{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    {{- $modulePrefix := lower1 (Camel $module.Name)}}
    {{- $instanceName := printf "%s%s"  $modulePrefix $class }}
    {{- $instanceNameTS := printf "%sThreadSafeDecorator" $class }}
    {{- $serviceInstanceName := printf "%sOlink%sService" $modulePrefix $class }}
    auto {{$instanceName}} = std::make_shared<{{ Camel $module.Name }}::{{$class}}>();
    auto {{$instanceName}}ThreadSafe = std::make_shared<{{ Camel $module.Name }}::{{$instanceNameTS}}>({{$instanceName}});
    auto {{$serviceInstanceName}} = std::make_shared<{{ Camel $module.Name }}::olink::{{$interface.Name}}Service>({{$instanceName}}ThreadSafe, registry);
    registry.addSource({{$serviceInstanceName}});
{{- end }}
{{- end }}

    // Start your server after all the services are added.
    // This ensures that any new client that connects, will find the source it needs.
    testserver.listen(port);

    Examples::runCommandLoop({}, [&](){
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
        {{- $class := Camel $interface.Name }}
        {{- $modulePrefix := lower1 (Camel $module.Name)}}
        {{- $serviceInstanceName := printf "%sOlink%sService" $modulePrefix $class }}
        registry.removeSource({{$serviceInstanceName}}->olinkObjectName());
{{- end }}
{{- end }}
        testserver.close();
    });

    return 0;
}
