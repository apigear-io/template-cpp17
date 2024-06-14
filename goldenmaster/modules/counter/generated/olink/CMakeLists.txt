set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
find_package(custom_types REQUIRED COMPONENTS core)
find_package(extern_types REQUIRED COMPONENTS core)
set (SOURCES_OLINK
    counterservice.cpp
    counterclient.cpp
)
add_library(counter-olink SHARED ${SOURCES_OLINK})
add_library(counter::counter-olink ALIAS counter-olink)
target_include_directories(counter-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(counter-olink
    PRIVATE
    counter::counter-core
    custom_types::custom_types-core
    extern_types::extern_types-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(counter-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(counter-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS counter-olink
        EXPORT CounterOLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/counter/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT CounterOLinkTargets
  NAMESPACE counter::
)

install(EXPORT CounterOLinkTargets
  FILE CounterOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE counter::
)
