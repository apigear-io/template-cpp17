set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-tracer)
set (SOURCES_MONITOR
)
add_library(extern_types-monitor SHARED ${SOURCES_MONITOR})
add_library(extern_types::extern_types-monitor ALIAS extern_types-monitor)
target_include_directories(extern_types-monitor
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(extern_types-monitor PRIVATE
    extern_types::extern_types-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(extern_types-monitor PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(extern_types-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS extern_types-monitor
        EXPORT Extern_typesMonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/extern_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Extern_typesMonitorTargets
  NAMESPACE extern_types::
)

install(EXPORT Extern_typesMonitorTargets
  FILE Extern_typesMonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE extern_types::
)
