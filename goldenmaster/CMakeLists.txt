cmake_minimum_required(VERSION 3.24)
project(test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# on Windows it is helpful to have all binary files next to each other
# it is intentionally not set as part of BUILD_TESTING to have a consistent behavior
# this can be removed once there is a better option than modifying the PATH env for unit testing
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_TESTING "Enable this option to build the test targets" OFF)
option(TEST_FETCH_DEPS "Fetch and build dependencies, if not pre-installed" OFF)

# enable testing
if(BUILD_TESTING)
include(CTest)
enable_testing()
endif(BUILD_TESTING)

if(TEST_FETCH_DEPS)
include(FetchContent)

if(BUILD_TESTING)
find_package(Catch2 QUIET)
if (NOT Catch2_Found)
  message(STATUS "Catch2 NOT FOUND, fetching the git repository")
  FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v2.13.8
      GIT_SHALLOW    TRUE
      OVERRIDE_FIND_PACKAGE)
  FetchContent_MakeAvailable(Catch2)
endif()

find_package(trompeloeil QUIET)
if(NOT trompeloeil_Found)
  message(STATUS "trompeloeil NOT FOUND, fetching the git repository")
  FetchContent_Declare(
      trompeloeil
      GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
      GIT_TAG        v46
      OVERRIDE_FIND_PACKAGE
      )
  FetchContent_MakeAvailable(trompeloeil)
endif()
endif() # BUILD_TESTING

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
  # pull nlohmann json as dependency
  message(STATUS "nlohmann_json NOT FOUND, fetching the release package")
  include(FetchContent)
  set(JSON_Install ON)
  FetchContent_Declare(nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  OVERRIDE_FIND_PACKAGE)
  FetchContent_MakeAvailable(nlohmann_json)
endif()

find_package(olink_core QUIET)
if(NOT olink_core_FOUND)
  # pull olink_core as dependency
  message(STATUS "olink_core NOT FOUND, fetching the git repository")
  FetchContent_Declare(olink_core
      GIT_REPOSITORY https://github.com/apigear-io/objectlink-core-cpp.git
      GIT_TAG v0.2.10
      GIT_SHALLOW TRUE
      EXCLUDE_FROM_ALL FALSE
      OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(olink_core)
endif()
endif() # TEST_FETCH_DEPS

# checks are workaround until generator support feature check properly
find_package(apigear QUIET)
if(NOT apigear_FOUND)
  # pull apigear as dependency
  message(STATUS "apigear NOT FOUND, building from source folder")
  include(FetchContent)
  set(APIGEAR_BUILD_WITH_MONITOR ON CACHE INTERNAL "Enable support for monitoring")
  set(APIGEAR_BUILD_WITH_OLINK ON CACHE INTERNAL "Enable support for OLink")
  set(APIGEAR_BUILD_WITH_MQTT ON CACHE INTERNAL "Enable support for MQTT")
  FetchContent_Declare(apigear
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/apigear"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(apigear)
endif()
find_package(testbed2 QUIET)
if(NOT testbed2_FOUND)
  # pull testbed2 as dependency
  message(STATUS "testbed2 NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(testbed2
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/testbed2"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(testbed2)
endif()
find_package(tb_enum QUIET)
if(NOT tb_enum_FOUND)
  # pull tb_enum as dependency
  message(STATUS "tb_enum NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(tb_enum
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/tb_enum"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(tb_enum)
endif()
find_package(tb_same1 QUIET)
if(NOT tb_same1_FOUND)
  # pull tb_same1 as dependency
  message(STATUS "tb_same1 NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(tb_same1
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/tb_same1"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(tb_same1)
endif()
find_package(tb_same2 QUIET)
if(NOT tb_same2_FOUND)
  # pull tb_same2 as dependency
  message(STATUS "tb_same2 NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(tb_same2
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/tb_same2"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(tb_same2)
endif()
find_package(tb_simple QUIET)
if(NOT tb_simple_FOUND)
  # pull tb_simple as dependency
  message(STATUS "tb_simple NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(tb_simple
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/tb_simple"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(tb_simple)
endif()
find_package(testbed1 QUIET)
if(NOT testbed1_FOUND)
  # pull testbed1 as dependency
  message(STATUS "testbed1 NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(testbed1
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/testbed1"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(testbed1)
endif()
find_package(tb_names QUIET)
if(NOT tb_names_FOUND)
  # pull tb_names as dependency
  message(STATUS "tb_names NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(tb_names
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/tb_names"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(tb_names)
endif()
find_package(custom_types QUIET)
if(NOT custom_types_FOUND)
  # pull custom_types as dependency
  message(STATUS "custom_types NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(custom_types
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/custom_types"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(custom_types)
endif()
find_package(extern_types QUIET)
if(NOT extern_types_FOUND)
  # pull extern_types as dependency
  message(STATUS "extern_types NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(extern_types
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/extern_types"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(extern_types)
endif()
find_package(counter QUIET)
if(NOT counter_FOUND)
  # pull counter as dependency
  message(STATUS "counter NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(counter
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/counter"
    OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(counter)
endif()
add_subdirectory(examples/app)
add_subdirectory(examples/appthreadsafe)
add_subdirectory(examples/olinkserver)
add_subdirectory(examples/olinkclient)
add_subdirectory(examples/mqttserver)
add_subdirectory(examples/mqttclient)
