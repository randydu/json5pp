cmake_minimum_required(VERSION 3.2...3.16)

project(json5pp VERSION 3.4.0 LANGUAGES CXX)

include(GNUInstallDirs)

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# head-only
add_library(json5pp INTERFACE)

target_include_directories(json5pp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
### Install

install(
    TARGETS json5pp
    EXPORT json5ppConfig
)

install(
    DIRECTORY include/json5pp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES VERSION
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/json5pp
)

# Export
install(
    EXPORT json5ppConfig
    DESTINATION lib/json5pp
)

# Test
option(JSON5PP_TEST "Build unit test" ON)

if(JSON5PP_TEST)
    enable_testing()
    add_subdirectory(tests)
endif()