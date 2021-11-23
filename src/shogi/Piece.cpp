/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "shogi.h"

namespace shogi {

bool pieceCanPromote(Piece p, Cell from, Cell to)
{
    if (pieceIsPromoted(p) || p == BlackGold || p == BlackKing || p == WhiteGold || p == WhiteKing) return false;

    if (pieceColor(p) == Black && (from <= Cell::c1 || to <= Cell::c1)) return true;
    else if (pieceColor(p) == White && (from >= Cell::g9 || to >= Cell::g9)) return true;
    else return false;
}

bool pieceMustPromote(Piece p, Cell to)
{
    if ((p == BlackPawn || p == BlackLance) && to <= Cell::a1) return true;
    if (p == BlackKnight && to <= Cell::b1) return true;

    if ((p == WhitePawn || p == WhiteLance) && to >= Cell::i9) return true;
    if (p == WhiteKnight && to >= Cell::g9) return true;

    return false;
}


std::string pieceSymbol(Piece p)
{
    switch(p) {
    case BlackPawn:           return "P";
    case BlackLance:          return "L";
    case BlackKnight:         return "N";
    case BlackSilver:         return "S";
    case BlackGold:           return "G";
    case BlackBishop:         return "B";
    case BlackRook:           return "R";
    case BlackKing:           return "K";
    case BlackPromotedPawn:   return "+P";
    case BlackPromotedLance:  return "+L";
    case BlackPromotedKnight: return "+N";
    case BlackPromotedSilver: return "+S";
    case BlackPromotedBishop: return "+B";
    case BlackPromotedRook:   return "+R";
    case WhitePawn:           return "p";
    case WhiteLance:          return "l";
    case WhiteKnight:         return "n";
    case WhiteSilver:         return "s";
    case WhiteGold:           return "g";
    case WhiteBishop:         return "b";
    case WhiteRook:           return "r";
    case WhiteKing:           return "k";
    case WhitePromotedPawn:   return "+p";
    case WhitePromotedLance:  return "+l";
    case WhitePromotedKnight: return "+n";
    case WhitePromotedSilver: return "+s";
    case WhitePromotedBishop: return "+b";
    case WhitePromotedRook:   return "+r";
    default: return "?";
    }
}

Piece pieceFromSymbol(std::string s)
{
    if (s == "P") return BlackPawn;
    if (s == "L") return BlackLance;
    if (s == "N") return BlackKnight;
    if (s == "S") return BlackSilver;
    if (s == "G") return BlackGold;
    if (s == "B") return BlackBishop;
    if (s == "R") return BlackRook;
    if (s == "K") return BlackKing;
    if (s == "+P") return BlackPromotedPawn;
    if (s == "+L") return BlackPromotedLance;
    if (s == "+N") return BlackPromotedKnight;
    if (s == "+S") return BlackPromotedSilver;
    if (s == "+B") return BlackPromotedBishop;
    if (s == "+R") return BlackPromotedRook;
    if (s == "p") return WhitePawn;
    if (s == "l") return WhiteLance;
    if (s == "n") return WhiteKnight;
    if (s == "s") return WhiteSilver;
    if (s == "g") return WhiteGold;
    if (s == "b") return WhiteBishop;
    if (s == "r") return WhiteRook;
    if (s == "k") return WhiteKing;
    if (s == "+p") return WhitePromotedPawn;
    if (s == "+l") return WhitePromotedLance;
    if (s == "+n") return WhitePromotedKnight;
    if (s == "+s") return WhitePromotedSilver;
    if (s == "+b") return WhitePromotedBishop;
    if (s == "+r") return WhitePromotedRook;

    return BlackKing; // FIXME - exception ?
}


} // namespace shogi
