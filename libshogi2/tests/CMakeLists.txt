include_directories(../../vendor/catch2)

add_executable(shogi2Test
    main.cpp
    SquareTest.cpp
    BoardTest.cpp
    MoveTest.cpp
    ShogiBoardTest.cpp
    MiniShogiBoardTest.cpp
)

target_link_libraries(shogi2Test PRIVATE shogi2)

if (LIBSHOGI2_COVERAGE)
    setup_target_for_coverage_gcovr_html(
        NAME shogi2TestCoverage
        EXECUTABLE shogi2Test
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/libshogi2"
    )
endif()
