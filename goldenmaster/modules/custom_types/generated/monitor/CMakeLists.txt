set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-tracer)
set (SOURCES_MONITOR
)
add_library(custom_types-monitor SHARED ${SOURCES_MONITOR})
add_library(custom_types::custom_types-monitor ALIAS custom_types-monitor)
target_include_directories(custom_types-monitor
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(custom_types-monitor PRIVATE
    custom_types::custom_types-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(custom_types-monitor PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(custom_types-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS custom_types-monitor
        EXPORT Custom_typesMonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/custom_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Custom_typesMonitorTargets
  NAMESPACE custom_types::
)

install(EXPORT Custom_typesMonitorTargets
  FILE Custom_typesMonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE custom_types::
)
