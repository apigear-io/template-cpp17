#include <iostream>
#include <string>
{{- $features := .Features}}
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
#include "{{snake $module.Name}}/generated/olink/{{ lower ( camel $interface.Name) }}client.h"
{{- if $features.monitor }}
#include "{{snake $module.Name}}/generated/monitor/{{ lower ( camel $interface.Name) }}.tracedecorator.h"
{{- end}}
{{- end }}
{{- end }}

#include "apigear/olink/olinkconnection.h"
{{- if $features.monitor }}
#include "apigear/tracer/tracer.h"
{{- end}}
#include "apigear/olink/olinklogadapter.h"
#include "olink/clientregistry.h"
#include "apigear/utilities/logger.h"
#include <cstdlib>
#include <sstream>
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
    std::string host = "localhost";
    int port = 8000;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--host" && i + 1 < argc) { host = argv[++i]; }
        else if (arg == "--port" && i + 1 < argc) { port = std::stoi(argv[++i]); }
        else if (arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [--host HOST] [--port PORT]" << std::endl;
            return 0;
        }
    }
    auto uri = "ws://" + host + ":" + std::to_string(port);

{{- if $features.monitor }}
    ApiGear::PocoImpl::Tracer tracer;
    tracer.connect("http://localhost:5555", "testExampleOLinkApp");
{{- end}}
    ApiGear::ObjectLink::ClientRegistry registry;
    auto logConsoleFunc = Examples::initLogging();
    registry.onLog(ApiGear::Utilities::logAdapter(logConsoleFunc));
    ApiGear::PocoImpl::OlinkConnection clientNetworkEndpoint(registry);
    clientNetworkEndpoint.node()->onLog(ApiGear::Utilities::logAdapter(logConsoleFunc));
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    {{- $modulePrefix := lower1 (Camel $module.Name)}}
    {{- $clientClassName := printf "%s%s"  $modulePrefix $class }}
    {{- $tracer_class := printf "%sTraceDecorator" $class }}
    {{- $tracer_className := printf "%sTraced" $clientClassName }}
    auto {{$clientClassName}} = std::make_shared<{{ Camel $module.Name }}::olink::{{$interface.Name}}Client>();
    clientNetworkEndpoint.connectAndLinkObject({{$clientClassName}});
    {{- if $features.monitor }}
    std::unique_ptr<{{Camel $module.Name}}::I{{$class}}> {{$tracer_className}} = {{ Camel $module.Name}}::{{$tracer_class}}::connect(*{{$clientClassName}}, tracer);
    {{- end}}
{{- end }}
{{- end }}

    clientNetworkEndpoint.connectToHost(Poco::URI(uri));

    Examples::runCommandLoop({}, [&](){
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
        {{- $class := Camel $interface.Name }}
        {{- $modulePrefix := lower1 (Camel $module.Name)}}
        {{- $clientClassName := printf "%s%s"  $modulePrefix $class }}
        clientNetworkEndpoint.disconnectAndUnlink({{$clientClassName}}->olinkObjectName());
{{- end }}
{{- end }}
        clientNetworkEndpoint.disconnect();
    });

    return 0;
}
