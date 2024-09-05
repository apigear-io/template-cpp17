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

#include <iostream>
#include <sstream>
#include <cstdlib>

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

using namespace {{ Camel .System.Name }};

int main(){
    ApiGear::ObjectLink::RemoteRegistry registry;
    auto logConsoleFunc = getLogging();
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
    testserver.listen(8000);

    bool keepRunning = true;
    std::string cmd;
    do {
        std::cout << "Enter command:" << std::endl;
        getline (std::cin, cmd);

        if(cmd == "quit"){
            testserver.close();
            keepRunning = false;
        }
    } while(keepRunning);

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
    
    return 0;
}
