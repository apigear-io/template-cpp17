set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
)
add_library(extern_types-olink SHARED ${SOURCES_OLINK})
add_library(extern_types::extern_types-olink ALIAS extern_types-olink)
target_include_directories(extern_types-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(extern_types-olink
    PRIVATE
    extern_types::extern_types-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(extern_types-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(extern_types-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS extern_types-olink
        EXPORT Extern_typesOLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/extern_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Extern_typesOLinkTargets
  NAMESPACE extern_types::
)

install(EXPORT Extern_typesOLinkTargets
  FILE Extern_typesOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE extern_types::
)
