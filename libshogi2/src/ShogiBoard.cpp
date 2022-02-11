/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "ShogiBoard.h"

//namespace shogi {
//    const std::string sfen_even = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";
//}

using namespace shogi;

namespace shogi {

bool ShogiBoard::moveCanPromote(int from, int to) {
    Square square = m_board[from];
    if (square.piece.promoted == true) return false;

    switch (square.piece.color) {
    case Color::black:
        if (square.piece.type == Type::gold || square.piece.type == Type::king) return false;
        if (from <=18 || to <= 18) return true;
        return false;
    case Color::white:
        if (square.piece.type == Type::gold || square.piece.type == Type::king) return false;
        if (from >=54 || to >= 54) return true;
        return false;
    default:
        return false;
    }
}

bool ShogiBoard::moveMustPromote(int from, int to) {
    Square square = m_board[from];
    if (square.piece.promoted == true) return false;

    switch (square.piece.color) {
    case Color::black:
        if ((square.piece.type == Type::pawn || square.piece.type == Type::lance) && to <= 8) return true;
        if (square.piece.type == Type::knight && to <= 17) return true;
        return false;
    case Color::white:
        if ((square.piece.type == Type::pawn || square.piece.type == Type::lance) && to >= 72) return true;
        if (square.piece.type == Type::knight && to >= 63) return true;
        return false;
    default:
        return false;
    }
}

} // namespace shogi
