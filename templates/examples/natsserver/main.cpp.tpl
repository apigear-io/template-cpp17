{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
#include "{{snake $module.Name}}/implementation/{{ lower ( camel $interface.Name) }}.h"
#include "{{snake $module.Name}}/generated/nats/{{ lower ( camel $interface.Name) }}service.h"
{{- end }}
{{- end }}
#include "apigear/nats/natsservice.h"
#include "apigear/utilities/logger.h"
#include <iostream>

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

using namespace {{ Camel .System.Name }};

int main(){

    auto service = std::make_shared<ApiGear::Nats::Service>();

    // set up modules
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    std::shared_ptr<{{ Camel $module.Name }}::I{{$class}}> test{{ Camel $module.Name }}{{$class}} = std::make_shared<{{ Camel $module.Name }}::{{$class}}>();
    auto test{{ Camel $module.Name }}{{$class}}Service = {{ Camel $module.Name }}::Nats::{{$interface.Name}}Service::create(test{{ Camel $module.Name }}{{$class}}, service);
{{- end }}
{{- end }}

    service->connect("nats://localhost:4222");

    bool keepRunning = true;
    std::string cmd;
    do {
        std::cout << "Enter command:" << std::endl;
        getline (std::cin, cmd);

        if(cmd == "quit"){
            service->disconnect();
            keepRunning = false;
        } else {
        }
    } while(keepRunning);

    return 0;
}
