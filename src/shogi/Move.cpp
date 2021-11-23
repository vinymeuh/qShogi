/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "shogi.h"

#include <algorithm>

namespace shogi {

std::string Shift::toString(MoveFormat format) const
{
    std::string s;

    switch(format) {
    case MoveFormat::Debug:
        if (m_promotion) {
            s = "Piece=" + pieceSymbol(m_piece) +
                    ", From=" + CellToString(m_from) +
                    ", To=" + CellToString(m_to) +
                    ", Promoted=true";
        } else {
            s = "Piece=" + pieceSymbol(m_piece) +
                    ", From=" + CellToString(m_from) +
                    ", To=" + CellToString(m_to) +
                    ", Promoted=false";
        }
        break;
    case MoveFormat::USI:
        if (m_promotion) {
            s = std::string{CellToString(m_from)} + std::string{CellToString(m_to)} + "+";
        } else {
            s = std::string{CellToString(m_from)} + std::string{CellToString(m_to)};
        }
        break;
    }
    return s;
}


std::string Drop::toString(MoveFormat format) const
{
    std::string s;
    switch(format) {
    case MoveFormat::Debug:
        s = "Piece=" + pieceSymbol(m_piece) + ", dropped To=" + CellToString(m_to);
        break;
    case MoveFormat::USI:
        std::string p = pieceSymbol(m_piece);
        std::transform(p.begin(), p.end(), p.begin(),
                       [](unsigned char p){ return std::toupper(p); });
        s = p + "*" + std::string{CellToString(m_to)};
        break;
    }
    return s;
}


std::ostream& operator<<(std::ostream& os, const Move& move)
{
    os << move.toString(MoveFormat::Debug);
    return os;
}

} // namespace shogi
