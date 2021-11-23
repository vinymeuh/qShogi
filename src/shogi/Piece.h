/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "Cell.h"

namespace shogi {

enum Color {Black, White};

enum PieceType {
    Pawn, Lance, Knight, Silver, Gold, Bishop, Rook, King,
    PromotedPawn, PromotedLance, PromotedKnight, PromotedSilver, PromotedBishop, PromotedRook,
};

enum Piece {
    BlackPawn, BlackLance, BlackKnight, BlackSilver, BlackGold, BlackBishop, BlackRook, BlackKing,
    BlackPromotedPawn, BlackPromotedLance, BlackPromotedKnight, BlackPromotedSilver, BlackPromotedBishop, BlackPromotedRook,
    WhitePawn, WhiteLance, WhiteKnight, WhiteSilver, WhiteGold, WhiteBishop, WhiteRook, WhiteKing,
    WhitePromotedPawn, WhitePromotedLance, WhitePromotedKnight, WhitePromotedSilver, WhitePromotedBishop, WhitePromotedRook,
};

inline Color pieceColor(Piece p)
{
    if (p >= BlackPawn && p <= BlackPromotedRook) return Black;
    return White;
};

constexpr const PieceType pieceType(Piece p) noexcept
{
    switch(p) {
    case BlackPawn:
    case WhitePawn:
        return Pawn;
    case BlackLance:
    case WhiteLance:
        return Lance;
    case BlackKnight:
    case WhiteKnight:
        return Knight;
    case BlackSilver:
    case WhiteSilver:
        return Silver;
    case BlackGold:
    case WhiteGold:
        return Gold;
    case BlackBishop:
    case WhiteBishop:
        return Bishop;
    case BlackRook:
    case WhiteRook:
        return Rook;
    case BlackKing:
    case WhiteKing:
        return King;
    case BlackPromotedPawn:
    case WhitePromotedPawn:
        return PromotedPawn;
    case BlackPromotedLance:
    case WhitePromotedLance:
        return PromotedLance;
    case BlackPromotedKnight:
    case WhitePromotedKnight:
        return PromotedKnight;
    case BlackPromotedSilver:
    case WhitePromotedSilver:
        return PromotedSilver;
    case BlackPromotedBishop:
    case WhitePromotedBishop:
        return PromotedBishop;
    case BlackPromotedRook:
    case WhitePromotedRook:
        return PromotedRook;
    }
}

constexpr const Piece piece(PieceType pt, Color color) noexcept
{
    if (color == Black) {
        switch(pt) {
        case Pawn:   return BlackPawn;
        case Lance:  return BlackLance;
        case Knight: return BlackKnight;
        case Silver: return BlackSilver;
        case Gold:   return BlackGold;
        case Bishop: return BlackBishop;
        case Rook:   return BlackRook;
        case King:   return BlackKing;
        case PromotedPawn:   return BlackPromotedPawn;
        case PromotedLance:  return BlackPromotedLance;
        case PromotedKnight: return BlackPromotedKnight;
        case PromotedSilver: return BlackPromotedSilver;
        case PromotedBishop: return BlackPromotedBishop;
        case PromotedRook:   return BlackPromotedRook;
        }
    }

    switch(pt) {
    case Pawn:   return WhitePawn;
    case Lance:  return WhiteLance;
    case Knight: return WhiteKnight;
    case Silver: return WhiteSilver;
    case Gold:   return WhiteGold;
    case Bishop: return WhiteBishop;
    case Rook:   return WhiteRook;
    case King:   return WhiteKing;
    case PromotedPawn:   return WhitePromotedPawn;
    case PromotedLance:  return WhitePromotedLance;
    case PromotedKnight: return WhitePromotedKnight;
    case PromotedSilver: return WhitePromotedSilver;
    case PromotedBishop: return WhitePromotedBishop;
    case PromotedRook:   return WhitePromotedRook;
    }
}


inline bool pieceIsPromoted(Piece p)
{
    if ((p>=BlackPromotedPawn && p<=BlackPromotedRook) || (p>=WhitePromotedPawn && p<=WhitePromotedRook)) return true;
    return false;
}

// Returns true for promotable piece moving from or to promotion area
bool pieceCanPromote(Piece p, Cell from, Cell to);

// Returns true for a pawn, a lance or a knight moving to a mandatory promote position
bool pieceMustPromote(Piece p, Cell to);

std::string pieceSymbol(Piece p);
Piece pieceFromSymbol(std::string s);

} // namespace shogi
#endif // PIECE_H
