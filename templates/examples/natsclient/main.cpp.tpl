{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
#include "{{snake $module.Name}}/generated/nats/{{ lower ( camel $interface.Name) }}client.h"
{{- end }}
{{- end }}
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

using namespace {{ Camel .System.Name }};

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
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    auto test{{Camel $module.Name}}{{$class}} = {{Camel $module.Name}}::Nats::{{$interface.Name}}Client::create(client);
{{- end }}
{{- end }}


    {{ $propertyExampleReady := 0 -}}
    {{ $signalExampleReady := 0 -}}
    {{ $operationExampleReady := 0 -}}
    {{- range.System.Modules -}}
    {{- $module := . -}}
    {{- range $module.Interfaces -}}
    {{- $interface := . -}}

{{- if (and (eq $propertyExampleReady  0)  (len $interface.Properties) )}}
    {{- $property := (index $interface.Properties 0) }}
    {{- $namespacePrefix := printf "%s::" (Camel $module.Name )}}
    // Try out properties: subscribe for changes
    test{{Camel $module.Name}}{{ Camel $interface.Name}}->_getPublisher().subscribeTo{{Camel $property.Name}}Changed([](auto value){ std::cout << " {{Camel $property.Name}} " << std::endl; });

    // or ask for change, when object is ready
    auto idSubProp = test{{Camel $module.Name}}{{ Camel $interface.Name}}->_subscribeForIsReady(
        [test{{Camel $module.Name}}{{ Camel $interface.Name}}](bool connected)
        {
            if (!connected)
            {
                return;
            }
            auto local_{{$property.Name}} = {{cppDefault $namespacePrefix $property}};//TODO change this value to non default!
            std::cout << " is ready!" << std::endl;
            test{{Camel $module.Name}}{{ Camel $interface.Name}}->set{{Camel $property.Name}}(local_{{$property.Name}});
        });
    {{ $propertyExampleReady = 1}}
{{- end }}
{{- if (and (eq $signalExampleReady  0)  (len $interface.Signals))}}
    // Check the signals with subscribing for its change. Emit the signal from server side.
    {{- $namespacePrefix := printf "%s::"  (Camel .Module.Name )}}
    {{- $signal := (index $interface.Signals 0 ) }}
    test{{Camel $module.Name}}{{ Camel $interface.Name}}->_getPublisher().subscribeTo{{Camel $signal.Name}}([]({{cppParams $namespacePrefix $signal.Params }}){ std::cout << " {{Camel $signal.Name}} " << std::endl; });
    {{ $signalExampleReady = 1}}
{{- end }}

{{- if ( and (eq $operationExampleReady  0) (len $interface.Operations))}}
    {{- $operation := (index $interface.Operations 0) }}
    // Play around executing your operations
    {{- $namespacePrefix := printf "%s::"  (Camel .Module.Name )}}
    auto idSubOperation = test{{Camel $module.Name}}{{ Camel $interface.Name}}->_subscribeForIsReady(
        [test{{Camel $module.Name}}{{ Camel $interface.Name}}](bool connected)
        {
            if (!connected)
            {
                return;
            }
            {{ if (not $operation.Return.IsVoid) }}auto method_result = {{ end }} test{{Camel $module.Name}}{{ Camel $interface.Name}}->{{lower1 $operation.Name}}(
                {{- range $i, $e := $operation.Params }}
                    {{- if $i }}, {{ end }}{{cppDefault $namespacePrefix $e}}
                {{- end }}   {{- /* end range operation param*/ -}} );
        });
    {{ $operationExampleReady = 1}}
{{- end }}
{{- if (and (and $operationExampleReady  $signalExampleReady)  $propertyExampleReady)}}
    {{- break}}
{{- end }}
{{- end}}{{/* end range over interfaces*/}}
{{- if (and (and $operationExampleReady  $signalExampleReady)  $propertyExampleReady)}}
    {{- break}}
{{- end }}
{{- end}}{{/* end range over modules*/}}

    //connect
    client->connect(url);

    Examples::runCommandLoop({}, [&](){
        client->disconnect();
    });

    return 0;
}
