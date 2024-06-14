set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Eigen3 REQUIRED COMPONENTS Eigen)
add_library(extern_types-api INTERFACE)
add_library(extern_types::extern_types-api ALIAS extern_types-api)
target_include_directories(extern_types-api
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(extern_types-api INTERFACE Eigen3::Eigen)

# install binary files
install(TARGETS extern_types-api
        EXPORT Extern_typesApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/extern_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Extern_typesApiTargets
  NAMESPACE extern_types::
)

install(EXPORT Extern_typesApiTargets
  FILE Extern_typesApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE extern_types::
)
