set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-tracer)
set (SOURCES_MONITOR
    manyparaminterface.tracedecorator.cpp
    manyparaminterface.tracer.cpp
    nestedstruct1interface.tracedecorator.cpp
    nestedstruct1interface.tracer.cpp
    nestedstruct2interface.tracedecorator.cpp
    nestedstruct2interface.tracer.cpp
    nestedstruct3interface.tracedecorator.cpp
    nestedstruct3interface.tracer.cpp
)
add_library(testbed2-monitor SHARED ${SOURCES_MONITOR})
add_library(testbed2::testbed2-monitor ALIAS testbed2-monitor)
target_include_directories(testbed2-monitor
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed2-monitor PRIVATE
    testbed2::testbed2-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed2-monitor PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed2-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed2-monitor
        EXPORT Testbed2MonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed2MonitorTargets
  NAMESPACE testbed2::
)

install(EXPORT Testbed2MonitorTargets
  FILE Testbed2MonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed2::
)
