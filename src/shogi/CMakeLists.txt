set(HEADER_FILES
    shogi.h
    Board.h
    Cell.h
    Move.h
    Piece.h
)

set(SOURCE_FILES
    Board.cpp
    Move.cpp
    Piece.cpp
)

add_library(shogi STATIC
    ${HEADER_FILES}
    ${SOURCE_FILES}
)
