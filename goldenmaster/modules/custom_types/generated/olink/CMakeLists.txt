set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
)
add_library(custom_types-olink SHARED ${SOURCES_OLINK})
add_library(custom_types::custom_types-olink ALIAS custom_types-olink)
target_include_directories(custom_types-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(custom_types-olink
    PRIVATE
    custom_types::custom_types-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(custom_types-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(custom_types-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS custom_types-olink
        EXPORT Custom_typesOLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/custom_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Custom_typesOLinkTargets
  NAMESPACE custom_types::
)

install(EXPORT Custom_typesOLinkTargets
  FILE Custom_typesOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE custom_types::
)
