{{- $features := .Features -}}
SET DIR=%~dp0..
echo %DIR:~0,-1%
cd %DIR:~0,-1%
@RD /S /Q "%DIR:~0,-1%/build/"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
if not exist build mkdir build
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
cd build
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
{{ if $features.apigear }}
@REM Building and testing apigear module
call :build_and_test_apigear "apigear" "../../apigear"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
{{- end }}
{{- range .System.Modules }}
@REM Building and testing {{snake .Name}} module
call :build_and_test_module "{{snake .Name}}" "../../modules/{{snake .Name}}/conan"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
{{- end }}

@REM Leave build folder
cd ..
{{ if $features.examples }}
call :build_example_app "..\examples\app"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
call :build_example_app "..\examples\appthreadsafe"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
{{- end}}
{{- if $features.examples_olink }}
call :build_example_app "..\examples\olinkserver"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
call :build_example_app "..\examples\olinkclient"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
{{- end}}
{{- if $features.examples_mqtt }}
call :build_example_app "..\examples\mqttserver"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
call :build_example_app "..\examples\mqttclient"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
{{- end}}
{{- if $features.examples_nats }}
call :build_example_app "..\examples\natsserver"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
call :build_example_app "..\examples\natsclient"
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
{{- end}}

exit /b

:build_and_test_apigear
conan remove "%~1/*" -c
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
conan create %~2 --build missing
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
exit /b

:build_and_test_module
conan remove "%~1/*" -c
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
conan create %~2 --build missing
exit /b

:build_example_app
if not exist build\examples\%~1 mkdir build\examples\%~1
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
pushd build\examples\%~1
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
conan install -g=VirtualBuildEnv --build missing --output-folder . ../../../../examples/%~1
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
cmake -B . -S ../../../../examples/%~1 --preset conan-default
if %ERRORLEVEL% GEQ 1 exit /b %ERRORLEVEL%
cmake --build . --preset conan-release
popd
exit /b
