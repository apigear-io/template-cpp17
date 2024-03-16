[requires]
{{- range .System.Modules }}
{{- $module := . }}
{{snake $module.Name}}/{{$module.Version}}
{{- end }}
apigear/3.6.0

[generators]
CMakeDeps
CMakeToolchain
VirtualRunEnv
