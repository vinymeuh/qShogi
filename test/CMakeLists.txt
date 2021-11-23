include_directories(../src)

set(HEADER_FILES
    catch.hpp
)

set(SOURCE_FILES
    main.cpp
    BoardTest.cpp
    CellTest.cpp
    PieceTest.cpp
)

add_executable(shogiTesting
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_link_libraries(shogiTesting
    PRIVATE shogi
)

if (SHOGI_CODE_COVERAGE)
    setup_target_for_coverage_gcovr_html(
        NAME shogiCoverage
        EXECUTABLE shogiTesting
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src"
    )
endif()
