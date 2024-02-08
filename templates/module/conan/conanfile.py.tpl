{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $isApiHeaderOnly := and (eq (len .Module.Enums) 0) (eq (len .Module.Structs) 0) -}}
{{- $module_id := snake .Module.Name -}}
{{- $features := .Features -}}
from conans import ConanFile, CMake, tools
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy
from pathlib import os

class {{$module_id}}Conan(ConanFile):
    name = "{{$module_id}}"
    version = "{{.Module.Version}}"
    license = "GPL v3"
    author = "ApiGear UG"
    #url = "<Package recipe repository url here, for issues about the package>"
    settings = "os", "compiler", "build_type", "arch"
    requires = "catch2/2.13.7", "nlohmann_json/3.9.1"{{ if $features.apigear }}, "apigear/3.5.2"{{- end}}
    generators = "cmake_find_package"
    options = {"build_testing": [True, False]}
    default_options = {
        "build_testing": True,
        {{- if $features.monitor }}
        "apigear:enable_monitor": True,
        {{- end}}
        {{- if $features.olink }}
        "apigear:enable_olink": True,
        {{- end}}
        {{- if $features.mqtt }}
        "apigear:enable_mqtt": True,
        {{- end}}
    }

    def layout(self):
        self.folders.root = ".."
        self.folders.source = "{{$module_id}}"
        # cmake_layout(self)

    def export_sources(self):
        # move one level up from the recipe folder
        source_folder = os.path.join(self.recipe_folder, "..")
        # wrap sources into modules name
        dst_folder = os.path.join(self.export_sources_folder, "{{$module_id}}")
        copy(self, "*", source_folder, dst_folder)

    def build(self):
        cmake = CMake(self)
        if not tools.cross_building(self):
            cmake.definitions['BUILD_TESTING'] = self.options.build_testing

        # workaround wrong layout setup if not using "conan create"
        if self.folders.source_folder != self.export_sources_folder:
            # we are building outside of the conan cache
            cmake.configure("..")
        else:
            cmake.configure()

        cmake.build()
        if not tools.cross_building(self):
            build_type = self.settings.get_safe("build_type", default="Release")
            # workaround - we need to add the api.dll and the core.dll to the windows PATH to be found for the test
            local_libs = { "PATH" : []}
            local_libs["PATH"].append(os.path.sep.join([self.build_folder, "generated", "api", build_type]))
            {{ if $features.core -}} local_libs["PATH"].append(os.path.sep.join([self.build_folder, "generated", "core", build_type])) {{- end}}
            with tools.environment_append(local_libs):
                cmake.test()

    def package(self):
        packages = ["api"
        {{- if $features.core }}, "core"{{ end -}}
        {{- if $features.monitor }}, "monitor"{{ end -}}
        {{- if $features.olink }}, "olink"{{ end -}}
        ]
        self.copy("**/*.h", dst="include/{{$module_id}}/generated", src="{{$module_id}}/generated")
        {{ if $features.stubs -}} self.copy("*.h", dst="include/{{$module_id}}/implementation", src="{{$module_id}}/implementation") {{- end}}
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.env_info.path.append(os.path.join(self.package_folder, "bin"))
        self.cpp_info.components["{{$module_id}}-api"].includedirs.append(os.path.join(self.package_folder, "include"))
        {{- if (eq $isApiHeaderOnly false) }}
        self.cpp_info.components["{{$module_id}}-api"].libs = ["{{$module_id}}-api"]
        {{- end}}
        {{- if $features.core }}
        self.cpp_info.components["{{$module_id}}-core"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-core"].libs = ["{{$module_id}}-core"]
        {{- if (eq $isApiHeaderOnly false) }}
        self.cpp_info.components["{{$module_id}}-core"].requires = ["{{$module_id}}-api", "catch2::catch2", "nlohmann_json::nlohmann_json"]
        {{- else }}
        self.cpp_info.components["{{$module_id}}-core"].requires = ["catch2::catch2", "nlohmann_json::nlohmann_json"]
        {{- end }}
        {{- end}}
        {{- if $features.stubs }}
        self.cpp_info.components["{{$module_id}}-implementation"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-implementation"].libs = ["{{$module_id}}-implementation"]
        self.cpp_info.components["{{$module_id}}-implementation"].requires = ["{{$module_id}}-core", "catch2::catch2", "nlohmann_json::nlohmann_json"]
        {{- end}}
        {{- if .Features.monitor }}
        self.cpp_info.components["{{$module_id}}-monitor"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-monitor"].libs = ["{{$module_id}}-monitor"]
        self.cpp_info.components["{{$module_id}}-monitor"].requires = ["{{$module_id}}-core", "nlohmann_json::nlohmann_json", "apigear::poco-tracer"]
        {{- end}}
        {{- if $features.olink }}
        self.cpp_info.components["{{$module_id}}-olink"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-olink"].libs = ["{{$module_id}}-olink"]
        self.cpp_info.components["{{$module_id}}-olink"].requires = ["{{$module_id}}-core", "nlohmann_json::nlohmann_json", "apigear::poco-olink"]
        {{- end}}
        {{- if $features.mqtt }}
        self.cpp_info.components["{{$module_id}}-mqtt"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-mqtt"].libs = ["{{$module_id}}-mqtt"]
        self.cpp_info.components["{{$module_id}}-mqtt"].requires = ["{{$module_id}}-core", "nlohmann_json::nlohmann_json", "apigear::paho-mqtt"]
        {{- end}}