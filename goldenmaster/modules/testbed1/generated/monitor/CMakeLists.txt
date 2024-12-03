set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-tracer)
set (SOURCES_MONITOR
    structinterface.tracedecorator.cpp
    structinterface.tracer.cpp
    structarrayinterface.tracedecorator.cpp
    structarrayinterface.tracer.cpp
)
add_library(testbed1-monitor SHARED ${SOURCES_MONITOR})
add_library(testbed1::testbed1-monitor ALIAS testbed1-monitor)
target_include_directories(testbed1-monitor
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed1-monitor PRIVATE
    testbed1::testbed1-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed1-monitor PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed1-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed1-monitor
        EXPORT Testbed1MonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed1/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed1MonitorTargets
  NAMESPACE testbed1::
)

install(EXPORT Testbed1MonitorTargets
  FILE Testbed1MonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed1::
)
