set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(custom_types REQUIRED COMPONENTS api)
find_package(extern_types REQUIRED COMPONENTS api)
add_library(counter-api INTERFACE)
add_library(counter::counter-api ALIAS counter-api)
target_include_directories(counter-api
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(counter-api INTERFACE custom_types::custom_types-api extern_types::extern_types-api)

# install binary files
install(TARGETS counter-api
        EXPORT CounterApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/counter/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT CounterApiTargets
  NAMESPACE counter::
)

install(EXPORT CounterApiTargets
  FILE CounterApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE counter::
)
