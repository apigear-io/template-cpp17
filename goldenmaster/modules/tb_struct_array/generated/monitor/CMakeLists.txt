set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-tracer)
set (SOURCES_MONITOR
    structarrayfieldinterface.tracedecorator.cpp
    structarrayfieldinterface.tracer.cpp
)
add_library(tb_struct_array-monitor SHARED ${SOURCES_MONITOR})
add_library(tb_struct_array::tb_struct_array-monitor ALIAS tb_struct_array-monitor)
target_include_directories(tb_struct_array-monitor
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_struct_array-monitor PRIVATE
    tb_struct_array::tb_struct_array-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_struct_array-monitor PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_struct_array-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_struct_array-monitor
        EXPORT Tb_struct_arrayMonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_struct_array/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_struct_arrayMonitorTargets
  NAMESPACE tb_struct_array::
)

install(EXPORT Tb_struct_arrayMonitorTargets
  FILE Tb_struct_arrayMonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_struct_array::
)
