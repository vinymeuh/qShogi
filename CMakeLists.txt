cmake_minimum_required(VERSION 3.21)

project(qshogi LANGUAGES CXX)

option(QSHOGI_LIBSHOGI_TESTING "Build only unit tests for shogi library (default OFF)" OFF)
option(QSHOGI_LIBSHOGI_COVERAGE "Enable coverage reporting for shogi library (default OFF)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (QSHOGI_LIBSHOGI_TESTING AND QSHOGI_LIBSHOGI_COVERAGE)
    message("Code coverage is enabled")
    include(CMake/CodeCoverage.cmake)
    append_coverage_compiler_flags()
endif()

add_subdirectory(src/shogi)

if (NOT QSHOGI_LIBSHOGI_TESTING)
    add_subdirectory(src/qShogi)
endif()

if (QSHOGI_LIBSHOGI_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
