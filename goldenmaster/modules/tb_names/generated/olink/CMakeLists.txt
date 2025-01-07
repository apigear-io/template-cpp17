set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
    namesservice.cpp
    namesclient.cpp
)
add_library(tb_names-olink SHARED ${SOURCES_OLINK})
add_library(tb_names::tb_names-olink ALIAS tb_names-olink)
target_include_directories(tb_names-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_names-olink
    PRIVATE
    tb_names::tb_names-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_names-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_names-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_names-olink
        EXPORT Tb_namesOLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_names/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_namesOLinkTargets
  NAMESPACE tb_names::
)

install(EXPORT Tb_namesOLinkTargets
  FILE Tb_namesOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_names::
)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
