if (LIBSHOGI_COVERAGE)
    message("Code coverage is enabled")
    include(../CMake/CodeCoverage.cmake)
    append_coverage_compiler_flags()
endif()

set(HEADER_FILES
    include/shogi.h
    include/Board.h
    include/Square.h
    include/Move.h
    include/ShogiBoard.h
    include/MiniShogiBoard.h
)

set(SOURCE_FILES
    src/Board.cpp
    src/Square.cpp
    src/Move.cpp
    src/ShogiBoard.cpp
    src/MiniShogiBoard.cpp
)

include_directories(include)

add_library(shogi OBJECT
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

if (LIBSHOGI_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
