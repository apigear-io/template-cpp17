set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-tracer)
find_package(custom_types REQUIRED COMPONENTS core)
find_package(extern_types REQUIRED COMPONENTS core)
set (SOURCES_MONITOR
    counter.tracedecorator.cpp
    counter.tracer.cpp
)
add_library(counter-monitor SHARED ${SOURCES_MONITOR})
add_library(counter::counter-monitor ALIAS counter-monitor)
target_include_directories(counter-monitor
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(counter-monitor PRIVATE
    counter::counter-core
    custom_types::custom_types-core
    extern_types::extern_types-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(counter-monitor PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(counter-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS counter-monitor
        EXPORT CounterMonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/counter/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT CounterMonitorTargets
  NAMESPACE counter::
)

install(EXPORT CounterMonitorTargets
  FILE CounterMonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE counter::
)
