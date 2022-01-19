if (LIBSHOGI_COVERAGE)
    message("Code coverage is enabled")
    include(../CMake/CodeCoverage.cmake)
    append_coverage_compiler_flags()
endif()

set(HEADER_FILES
    include/shogi.h
    include/Board.h
    include/Cell.h
    include/Move.h
    include/Piece.h
)

set(SOURCE_FILES
    src/Board.cpp
    src/Move.cpp
    src/Piece.cpp
)

include_directories(include)

add_library(shogi STATIC
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

if (LIBSHOGI_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
