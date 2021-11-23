cmake_minimum_required(VERSION 3.21)

project(qshogi LANGUAGES CXX)

option(SHOGI_BUILD_UNIT_TESTS "Build unit tests for shogi library (default OFF)" OFF)
option(SHOGI_CODE_COVERAGE "Enable coverage reporting for shogi library (default OFF)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (SHOGI_CODE_COVERAGE)
    message("Code coverage is enabled")
    include(CMake/CodeCoverage.cmake)
    append_coverage_compiler_flags()
endif()

add_subdirectory(src)

if (SHOGI_BUILD_UNIT_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
