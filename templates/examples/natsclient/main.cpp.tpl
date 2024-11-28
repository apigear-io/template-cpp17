{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
#include "{{snake $module.Name}}/generated/nats/{{ lower ( camel $interface.Name) }}client.h"
{{- end }}
{{- end }}
#include "apigear/utilities/logger.h"
#include <iostream>
#include "apigear/nats/natsclient.h"

using namespace {{ Camel .System.Name }};

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

    // or ask for change, when objest is ready
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
