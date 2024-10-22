set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-tracer)
set (SOURCES_MONITOR
    samestruct1interface.tracedecorator.cpp
    samestruct1interface.tracer.cpp
    samestruct2interface.tracedecorator.cpp
    samestruct2interface.tracer.cpp
    sameenum1interface.tracedecorator.cpp
    sameenum1interface.tracer.cpp
    sameenum2interface.tracedecorator.cpp
    sameenum2interface.tracer.cpp
)
add_library(tb_same2-monitor SHARED ${SOURCES_MONITOR})
add_library(tb_same2::tb_same2-monitor ALIAS tb_same2-monitor)
target_include_directories(tb_same2-monitor
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_same2-monitor PRIVATE
    tb_same2::tb_same2-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same2-monitor PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same2-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_same2-monitor
        EXPORT Tb_same2MonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_same2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_same2MonitorTargets
  NAMESPACE tb_same2::
)

install(EXPORT Tb_same2MonitorTargets
  FILE Tb_same2MonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same2::
)
