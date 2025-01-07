set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
    enuminterfaceservice.cpp
    enuminterfaceclient.cpp
)
add_library(tb_enum-olink SHARED ${SOURCES_OLINK})
add_library(tb_enum::tb_enum-olink ALIAS tb_enum-olink)
target_include_directories(tb_enum-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_enum-olink
    PRIVATE
    tb_enum::tb_enum-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_enum-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_enum-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_enum-olink
        EXPORT Tb_enumOLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_enum/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_enumOLinkTargets
  NAMESPACE tb_enum::
)

install(EXPORT Tb_enumOLinkTargets
  FILE Tb_enumOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_enum::
)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
