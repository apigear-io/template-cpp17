set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
    structarrayfieldinterfaceservice.cpp
    structarrayfieldinterfaceclient.cpp
)
add_library(tb_struct_array-olink SHARED ${SOURCES_OLINK})
add_library(tb_struct_array::tb_struct_array-olink ALIAS tb_struct_array-olink)
target_include_directories(tb_struct_array-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_struct_array-olink
    PRIVATE
    tb_struct_array::tb_struct_array-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_struct_array-olink PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_struct_array-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_struct_array-olink
        EXPORT Tb_struct_arrayOLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_struct_array/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_struct_arrayOLinkTargets
  NAMESPACE tb_struct_array::
)

install(EXPORT Tb_struct_arrayOLinkTargets
  FILE Tb_struct_arrayOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_struct_array::
)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
