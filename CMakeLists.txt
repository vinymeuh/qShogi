cmake_minimum_required(VERSION 3.21)

project(qshogi LANGUAGES CXX)

option(LIBSHOGI_TESTING "Build only libshogi for unit tests (default OFF)" OFF)
option(LIBSHOGI_COVERAGE "Enable coverage report for libshogi tests (default OFF)" OFF)

option(LIBSHOGI2_TESTING "Build only libshogi for unit tests (default ON)" ON)
option(LIBSHOGI2_COVERAGE "Enable coverage report for libshogi tests (default OFF)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(libshogi)

add_subdirectory(libshogi2)

#if (NOT LIBSHOGI_TESTING AND NOT LIBSHOGI_COVERAGE)
#    add_subdirectory(src)
#endif()
