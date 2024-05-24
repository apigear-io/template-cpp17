from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.build import check_max_cppstd, check_min_cppstd, cross_building
from conan.tools.files import load, copy
from conan.tools.build import can_run
from pathlib import os

class tb_namesConan(ConanFile):
    name = "tb_names"
    version = "1.0.0"
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
        "apigear/*:enable_monitor": True,
        "apigear/*:enable_olink": True,
        "apigear/*:enable_mqtt": True,
    }

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("nlohmann_json/3.11.3", transitive_headers=True)
        
        self.requires("apigear/3.6.0", transitive_headers=True)

    def build_requirements(self):
        self.test_requires("catch2/2.13.7")

    def validate(self):
        check_min_cppstd(self, "14")

    def layout(self):
        cmake_layout(self)
        self.folders.root = ".."
        self.folders.source = "tb_names"

    def export_sources(self):
        # move one level up from the recipe folder
        source_folder = os.path.join(self.recipe_folder, "..")
        # wrap sources into modules name
        dst_folder = os.path.join(self.export_sources_folder, "tb_names")
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
        if self.folders.base_source.endswith("tb_names"):
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
        # generates a Findtb_names.cmake file in addition to the tb_names-config.cmake
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.components["tb_names-api"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["tb_names-core"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["tb_names-core"].libs = ["tb_names-core"]
        self.cpp_info.components["tb_names-core"].requires = ["nlohmann_json::nlohmann_json"]
        self.cpp_info.components["tb_names-implementation"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["tb_names-implementation"].libs = ["tb_names-implementation"]
        self.cpp_info.components["tb_names-implementation"].requires = ["tb_names-core", "nlohmann_json::nlohmann_json"]
        self.cpp_info.components["tb_names-monitor"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["tb_names-monitor"].libs = ["tb_names-monitor"]
        self.cpp_info.components["tb_names-monitor"].requires = ["tb_names-core", "nlohmann_json::nlohmann_json", "apigear::poco-tracer"]
        self.cpp_info.components["tb_names-olink"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["tb_names-olink"].libs = ["tb_names-olink"]
        self.cpp_info.components["tb_names-olink"].requires = ["tb_names-core", "nlohmann_json::nlohmann_json", "apigear::poco-olink"]
        self.cpp_info.components["tb_names-mqtt"].includedirs.append(os.path.join(self.package_folder, "include"))
        self.cpp_info.components["tb_names-mqtt"].libs = ["tb_names-mqtt"]
        self.cpp_info.components["tb_names-mqtt"].requires = ["tb_names-core", "nlohmann_json::nlohmann_json", "apigear::paho-mqtt"]
