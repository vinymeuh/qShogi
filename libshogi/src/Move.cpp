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
        s = "Piece=" + pieceSymbol(m_piece) +
                ", From=" + HodgesNotation(m_from) +
                ", To=" + HodgesNotation(m_to);
        if (m_promoted) s += ", Promoted";
        if (m_captured.has_value()) {
            s += ", Capture=" + pieceSymbol(m_captured.value());
        }
        break;
    case MoveFormat::USI:
        s = HodgesNotation(m_from) + HodgesNotation(m_to);
        if (m_promoted) s += "+";
        break;
    case MoveFormat::Hodges:
        s = pieceTypeSymbol(pieceType(m_piece)) + HodgesNotation(m_from); // TODO: origin only when needed to resolve ambiguity
        if (m_captured.has_value()) s += "x" + HodgesNotation(m_to);
        else  s += "-" + HodgesNotation(m_to);
        if (m_promotable) {
            if (m_promoted) s += "+";
            else s += "=";
        }
        break;
    case MoveFormat::Hosking:
        s = pieceTypeSymbol(pieceType(m_piece)) + HoskingNotation(m_from); // TODO: origin only when needed to resolve ambiguity
        if (m_captured.has_value()) s += "x" + HoskingNotation(m_to);
        else  s += "-" + HoskingNotation(m_to);
        if (m_promotable) {
            if (m_promoted) s += "+";
            else s += "=";
        }
        break;
    }

    return s;
}


std::string Drop::toString(MoveFormat format) const
{
    std::string s;
    std::string ps = pieceSymbol(m_piece);

    switch(format) {
    case MoveFormat::Debug:
        s = "Piece=" + ps + ", Dropped, To=" + HodgesNotation(m_to);
        break;
    case MoveFormat::USI:
        std::transform(ps.begin(), ps.end(), ps.begin(),
                       [](unsigned char ps){ return std::toupper(ps); });
        s = ps + "*" + HodgesNotation(m_to);
        break;
    case MoveFormat::Hodges:
        s = pieceTypeSymbol(pieceType(m_piece)) + "*" + HodgesNotation(m_to);
        break;
    case MoveFormat::Hosking:
        s = pieceTypeSymbol(pieceType(m_piece)) + "*" + HoskingNotation(m_to);
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
