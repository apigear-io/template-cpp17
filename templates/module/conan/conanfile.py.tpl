{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $isApiHeaderOnly := and (eq (len .Module.Enums) 0) (eq (len .Module.Structs) 0) -}}
{{- $module_id := snake .Module.Name -}}
{{- $features := .Features -}}
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.build import check_max_cppstd, check_min_cppstd, cross_building
from conan.tools.files import load, copy
from conan.tools.build import can_run
from pathlib import os

class {{$module_id}}Conan(ConanFile):
    name = "{{$module_id}}"
    version = "{{.Module.Version}}"
    package_type = "library"
    license = "GPL v3"
    author = "ApiGear UG"
    #url = "<Package recipe repository url here, for issues about the package>"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "build_testing": [True, False],
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "build_testing": True,
        "shared": True,
        "fPIC": False,
        {{- if and $features.monitor ( len .Module.Interfaces ) }}
        "apigear/*:enable_monitor": True,
        {{- end}}
        {{- if and $features.olink ( len .Module.Interfaces ) }}
        "apigear/*:enable_olink": True,
        {{- end}}
        {{- if and $features.mqtt ( len .Module.Interfaces ) }}
        "apigear/*:enable_mqtt": True,
        {{- end}}
    }

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("nlohmann_json/3.11.3", transitive_headers=True)
{{- range .Module.Imports }}
        self.requires("{{snake .Name}}/{{ ($.System.LookupModule .Name).Version }}", transitive_headers=True)
{{- end }}
        {{ if and $features.apigear ( len .Module.Interfaces ) }}
        self.requires("apigear/3.6.0", transitive_headers=True)
        {{- end}}

    def build_requirements(self):
        {{- if or $features.stubs $features.core }}
        self.test_requires("catch2/2.13.7")
        {{- end }}

    def validate(self):
        check_min_cppstd(self, "14")

    def layout(self):
        cmake_layout(self)
        self.folders.root = ".."
        self.folders.source = "{{$module_id}}"

    def export_sources(self):
        # move one level up from the recipe folder
        source_folder = os.path.join(self.recipe_folder, "..")
        # wrap sources into modules name
        dst_folder = os.path.join(self.export_sources_folder, "{{$module_id}}")
        copy(self, "*", source_folder, dst_folder)

    def source(self):
        cmake_file = load(self, "CMakeLists.txt")

    def generate(self):
        tc = CMakeToolchain(self)
        if not cross_building(self):
            tc.cache_variables['BUILD_TESTING'] = self.options.build_testing
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)

        # workaround wrong layout setup if not using "conan create"
        if self.folders.base_source.endswith("{{$module_id}}"):
            print("Building outside of the conan cache")
            # we are building outside of the conan cache
            cmake.configure(build_script_folder="..")
        else:
            cmake.configure()

        cmake.build()

        # we skip tests on windows since the conanrun env does not include locally built libraries
        if can_run(self) and self.settings.os != "Windows":
            cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # generates a Find{{$module_id}}.cmake file in addition to the {{$module_id}}-config.cmake
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.components["{{$module_id}}-api"].includedirs.append(os.path.join(self.package_folder, "include"))
        {{- if (eq $isApiHeaderOnly false) }}
        self.cpp_info.components["{{$module_id}}-api"].libs = ["{{$module_id}}-api"]
        {{- end}}
        {{- range .Module.Imports }}
        self.cpp_info.components["{{$module_id}}-api"].requires = ["{{snake .Name}}::{{snake .Name}}-api"]
        {{- end }}
        {{- if $features.core }}
        self.cpp_info.components["{{$module_id}}-core"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-core"].libs = ["{{$module_id}}-core"]
        {{- if or (eq $isApiHeaderOnly false) (len .Module.Imports )}}
        self.cpp_info.components["{{$module_id}}-core"].requires = ["{{$module_id}}-api", "nlohmann_json::nlohmann_json"]
        {{- else }}
        self.cpp_info.components["{{$module_id}}-core"].requires = ["nlohmann_json::nlohmann_json"]
        {{- end }}
        {{- end}}
        {{- if and $features.stubs ( len .Module.Interfaces ) }}
        self.cpp_info.components["{{$module_id}}-implementation"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-implementation"].libs = ["{{$module_id}}-implementation"]
        self.cpp_info.components["{{$module_id}}-implementation"].requires = ["{{$module_id}}-core", "nlohmann_json::nlohmann_json"]
        {{- end}}
        {{- if and .Features.monitor ( len .Module.Interfaces ) }}
        self.cpp_info.components["{{$module_id}}-monitor"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-monitor"].libs = ["{{$module_id}}-monitor"]
        self.cpp_info.components["{{$module_id}}-monitor"].requires = ["{{$module_id}}-core", "nlohmann_json::nlohmann_json", "apigear::poco-tracer"]
        {{- end}}
        {{- if and $features.olink ( len .Module.Interfaces ) }}
        self.cpp_info.components["{{$module_id}}-olink"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-olink"].libs = ["{{$module_id}}-olink"]
        self.cpp_info.components["{{$module_id}}-olink"].requires = ["{{$module_id}}-core", "nlohmann_json::nlohmann_json", "apigear::poco-olink"]
        {{- end}}
        {{- if and $features.mqtt ( len .Module.Interfaces ) }}
        self.cpp_info.components["{{$module_id}}-mqtt"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["{{$module_id}}-mqtt"].libs = ["{{$module_id}}-mqtt"]
        self.cpp_info.components["{{$module_id}}-mqtt"].requires = ["{{$module_id}}-core", "nlohmann_json::nlohmann_json", "apigear::paho-mqtt"]
        {{- end}}
