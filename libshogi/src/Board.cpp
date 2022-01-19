/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "shogi.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace shogi {

void Board::set_start_position(const std::string sfen)
{
    clear();

    // sfen consists of 3 to 4 fields white space separated
    std::vector<std::string> fields;
    std::stringstream ss(sfen);
    std::string token;
    while (ss >> token) {
        fields.push_back(token);
    }
    if (auto s = fields.size(); s < 3 || s > 4) {
        throw std::invalid_argument("invalid sfen: must have 3 (optionally 4) fields space separated");
    }

    // fields[0] = Board state
    set_start_position_board_state(fields[0]);

    // fields[1] = Side to move
    if (fields[1] == "b") {
        m_sidetomove = Black;
    }
    else if (fields[1] == "w") {
        m_sidetomove = White;
    }
    else {
        throw std::invalid_argument("invalid sfen: side to move filed must be 'b' or 'w'");
    }

    // fields[2] = Pieces in hand
    if (fields[2] != "-") set_start_pieces_in_hands(fields[2]);

    // fields[3] = Move count (optional)
    if (fields.size() == 3) {
        m_movecount = 1;
    } else {
        m_movecount = std::stoul(fields[3]);
    }

    m_starting_sfen = sfen;
};


void Board::clear()
{
    m_BlackPawns = 0;
    m_BlackLances = 0;
    m_BlackKnights = 0;
    m_BlackSilvers = 0;
    m_BlackGolds = 0;
    m_BlackBishops = 0;
    m_BlackRooks = 0;
    m_BlackKing = 0;
    m_BlackPromotedPawns = 0;
    m_BlackPromotedLances = 0;
    m_BlackPromotedKnights = 0;
    m_BlackPromotedSilvers = 0;
    m_BlackPromotedBishops = 0;
    m_BlackPromotedRooks = 0;

    m_WhitePawns = 0;
    m_WhiteLances = 0;
    m_WhiteKnights = 0;
    m_WhiteSilvers = 0;
    m_WhiteGolds = 0;
    m_WhiteBishops = 0;
    m_WhiteRooks = 0;
    m_WhiteKing = 0;
    m_WhitePromotedPawns = 0;
    m_WhitePromotedLances = 0;
    m_WhitePromotedKnights = 0;
    m_WhitePromotedSilvers = 0;
    m_WhitePromotedBishops = 0;
    m_WhitePromotedRooks = 0;

    m_AllPieces = 0;
    m_AllBlackPieces = 0;
    m_AllWhitePieces = 0;

    m_sidetomove = Black;
    m_movecount = 1;

    m_BlackHand = {0, 0, 0, 0, 0, 0, 0};
    m_WhiteHand = {0, 0, 0, 0, 0, 0, 0};

    m_starting_sfen = "";
    m_moves.clear();  // FIXME: crash
};


std::string const Board::sfen()
{
    std::string sfen = "";

    // board state
    std::string cell;
    int ecc = 0; // empty cell counter
    for (int i=0; i<81; ++i) {
        if (i%9 == 0 && i != 0) {   // new line
            if (ecc >0) {
                sfen += std::to_string(ecc);
                ecc = 0;
            }
            sfen += "/";
        }

        cell = pieceStringAt(static_cast<Cell>(i));
        if (cell == "") {
            ++ecc;
            continue;
        }
        if (ecc > 0) {  // a piece after at least one empty cell
            sfen += std::to_string(ecc);
            ecc = 0;
        }
        sfen += cell;
    }

    // side to move
    if (m_sidetomove == Black) sfen += " b ";
    else sfen += " w ";

    // hands
    unsigned short count;
    bool no_capture = true;
    for (int i=Board::Rook; i>=Board::Pawn; --i) {
        count = m_BlackHand[i];
        if (count == 0) continue;
        no_capture = false;
        if (count > 1) sfen += std::to_string(count);
        switch(i) {
        case Board::Rook: sfen += "R"; break;
        case Board::Bishop: sfen += "B"; break;
        case Board::Gold: sfen += "G"; break;
        case Board::Silver: sfen += "S"; break;
        case Board::Knight: sfen += "N"; break;
        case Board::Lance: sfen += "L"; break;
        case Board::Pawn: sfen += "P"; break;
        }
    }
    for (int i=Board::Rook; i>=Board::Pawn; --i) {
        count = m_WhiteHand[i];
        if (count == 0) continue;
        no_capture = false;
        if (count > 1) sfen += std::to_string(count);
        switch(i) {
        case Board::Rook: sfen += "r"; break;
        case Board::Bishop: sfen += "b"; break;
        case Board::Gold: sfen += "g"; break;
        case Board::Silver: sfen += "s"; break;
        case Board::Knight: sfen += "n"; break;
        case Board::Lance: sfen += "l"; break;
        case Board::Pawn: sfen += "p"; break;
        }
    }
    if (no_capture) sfen += "-";

    // move count
    sfen += " " + std::to_string(m_movecount);

    return sfen;
};


std::optional<Piece> Board::cell(const Cell index) const
{
    if (m_AllBlackPieces[index] == 1) {
        if (m_BlackPawns[index] == 1)                return BlackPawn;
        else if (m_BlackLances[index] == 1)          return BlackLance;
        else if (m_BlackKnights[index] == 1)         return BlackKnight;
        else if (m_BlackSilvers[index] == 1)         return BlackSilver;
        else if (m_BlackGolds[index] == 1)           return BlackGold;
        else if (m_BlackBishops[index] == 1)         return BlackBishop;
        else if (m_BlackRooks[index] == 1)           return BlackRook;
        else if (m_BlackKing[index] == 1)            return BlackKing;
        else if (m_BlackPromotedPawns[index] == 1)   return BlackPromotedPawn;
        else if (m_BlackPromotedLances[index] == 1)  return BlackPromotedLance;
        else if (m_BlackPromotedKnights[index] == 1) return BlackPromotedKnight;
        else if (m_BlackPromotedSilvers[index] == 1) return BlackPromotedSilver;
        else if (m_BlackPromotedBishops[index] == 1) return BlackPromotedBishop;
        else if (m_BlackPromotedRooks[index] == 1)   return BlackPromotedRook;
    }
    if (m_AllWhitePieces[index] == 1) {
        if (m_WhitePawns[index] == 1)                return WhitePawn;
        else if (m_WhiteLances[index] == 1)          return WhiteLance;
        else if (m_WhiteKnights[index] == 1)         return WhiteKnight;
        else if (m_WhiteSilvers[index] == 1)         return WhiteSilver;
        else if (m_WhiteGolds[index] == 1)           return WhiteGold;
        else if (m_WhiteBishops[index] == 1)         return WhiteBishop;
        else if (m_WhiteRooks[index] == 1)           return WhiteRook;
        else if (m_WhiteKing[index] == 1)            return WhiteKing;
        else if (m_WhitePromotedPawns[index] == 1)   return WhitePromotedPawn;
        else if (m_WhitePromotedLances[index] == 1)  return WhitePromotedLance;
        else if (m_WhitePromotedKnights[index] == 1) return WhitePromotedKnight;
        else if (m_WhitePromotedSilvers[index] == 1) return WhitePromotedSilver;
        else if (m_WhitePromotedBishops[index] == 1) return WhitePromotedBishop;
        else if (m_WhitePromotedRooks[index] == 1)   return WhitePromotedRook;
    }
    return {};
}


std::string Board::pieceStringAt(const Cell index) const
{
    if (auto piece = cell(index)) {
        return pieceSymbol(*piece);
    }
    return "";
}


void Board::shiftPiece(Cell from, Cell to, bool promoted)
{
    auto piece = cell(from);
    assert(piece.has_value());
    auto piece_to = cell(to);
    assert(!piece_to.has_value() || pieceColor(*piece) != pieceColor(*piece_to));

    bool promotable = canPromote(from, to);
    auto move = std::make_shared<Shift>(*piece, from, to, promotable, promoted);

    // capture
    if (piece_to.has_value()) {
        move->m_captured = *piece_to; // update move with captured piece
        switch (*piece_to) {
        case BlackPawn:
            m_AllBlackPieces[to] = 0;
            m_BlackPawns[to] = 0;
            m_WhiteHand[Hand::Pawn]++;
            break;
        case BlackLance:
            m_AllBlackPieces[to] = 0;
            m_BlackLances[to] = 0;
            m_WhiteHand[Hand::Lance]++;
            break;
        case BlackKnight:
            m_AllBlackPieces[to] = 0;
            m_BlackKnights[to] = 0;
            m_WhiteHand[Hand::Knight]++;
            break;
        case BlackSilver:
            m_AllBlackPieces[to] = 0;
            m_BlackSilvers[to] = 0;
            m_WhiteHand[Hand::Silver]++;
            break;
        case BlackGold:
            m_AllBlackPieces[to] = 0;
            m_BlackGolds[to] = 0;
            m_WhiteHand[Hand::Gold]++;
            break;
        case BlackBishop:
            m_AllBlackPieces[to] = 0;
            m_BlackBishops[to] = 0;
            m_WhiteHand[Hand::Bishop]++;
            break;
        case BlackRook:
            m_AllBlackPieces[to] = 0;
            m_BlackRooks[to] = 0;
            m_WhiteHand[Hand::Rook]++;
            break;
        case BlackKing:
            m_AllBlackPieces[to] = 0;
            m_BlackKing[to] = 0;
            break;
        case BlackPromotedPawn:
            m_AllBlackPieces[to] = 0;
            m_BlackPromotedPawns[to] = 0;
            m_WhiteHand[Hand::Pawn]++;
            break;
        case BlackPromotedLance:
            m_AllBlackPieces[to] = 0;
            m_BlackPromotedLances[to] = 0;
            m_WhiteHand[Hand::Lance]++;
            break;
        case BlackPromotedKnight:
            m_AllBlackPieces[to] = 0;
            m_BlackPromotedKnights[to] = 0;
            m_WhiteHand[Hand::Knight]++;
            break;
        case BlackPromotedSilver:
            m_AllBlackPieces[to] = 0;
            m_BlackPromotedSilvers[to] = 0;
            m_WhiteHand[Hand::Silver]++;
            break;
        case BlackPromotedBishop:
            m_AllBlackPieces[to] = 0;
            m_BlackPromotedBishops[to] = 0;
            m_WhiteHand[Hand::Bishop]++;
            break;
        case BlackPromotedRook:
            m_AllBlackPieces[to] = 0;
            m_BlackPromotedRooks[to] = 0;
            m_WhiteHand[Hand::Rook]++;
        case WhitePawn:
            m_AllWhitePieces[to] = 0;
            m_WhitePawns[to] = 0;
            m_BlackHand[Hand::Pawn]++;
            break;
        case WhiteLance:
            m_AllWhitePieces[to] = 0;
            m_WhiteLances[to] = 0;
            m_BlackHand[Hand::Lance]++;
            break;
        case WhiteKnight:
            m_AllWhitePieces[to] = 0;
            m_WhiteKnights[to] = 0;
            m_BlackHand[Hand::Knight]++;
            break;
        case WhiteSilver:
            m_AllWhitePieces[to] = 0;
            m_WhiteSilvers[to] = 0;
            m_BlackHand[Hand::Silver]++;
            break;
        case WhiteGold:
            m_AllWhitePieces[to] = 0;
            m_WhiteGolds[to] = 0;
            m_BlackHand[Hand::Gold]++;
            break;
        case WhiteBishop:
            m_AllWhitePieces[to] = 0;
            m_WhiteBishops[to] = 0;
            m_BlackHand[Hand::Bishop]++;
            break;
        case WhiteRook:
            m_AllWhitePieces[to] = 0;
            m_WhiteRooks[to] = 0;
            m_BlackHand[Hand::Rook]++;
            break;
        case WhiteKing:
            m_AllWhitePieces[to] = 0;
            m_WhiteKing[to] = 0;
            break;
        case WhitePromotedPawn:
            m_AllWhitePieces[to] = 0;
            m_WhitePromotedPawns[to] = 0;
            m_BlackHand[Hand::Pawn]++;
            break;
        case WhitePromotedLance:
            m_AllWhitePieces[to] = 0;
            m_WhitePromotedLances[to] = 0;
            m_BlackHand[Hand::Lance]++;
            break;
        case WhitePromotedKnight:
            m_AllWhitePieces[to] = 0;
            m_WhitePromotedKnights[to] = 0;
            m_BlackHand[Hand::Knight]++;
            break;
        case WhitePromotedSilver:
            m_AllWhitePieces[to] = 0;
            m_WhitePromotedSilvers[to] = 0;
            m_BlackHand[Hand::Silver]++;
            break;
        case WhitePromotedBishop:
            m_AllWhitePieces[to] = 0;
            m_WhitePromotedBishops[to] = 0;
            m_BlackHand[Hand::Bishop]++;
            break;
        case WhitePromotedRook:
            m_AllWhitePieces[to] = 0;
            m_WhitePromotedRooks[to] = 0;
            m_BlackHand[Hand::Rook]++;
        default:
            ; // unreachable
        }
    }

    // move
    switch (*piece) {
    case BlackPawn:
        m_AllBlackPieces[from] = 0;
        m_BlackPawns[from] = 0;
        m_AllBlackPieces[to] = 1;
        if (!promoted) m_BlackPawns[to] = 1;
        else m_BlackPromotedPawns[to] = 1;
        break;
    case BlackLance:
        m_AllBlackPieces[from] = 0;
        m_BlackLances[from] = 0;
        m_AllBlackPieces[to] = 1;
        if (!promoted) m_BlackLances[to] = 1;
        else m_BlackPromotedLances[to] = 1;
        break;
    case BlackKnight:
        m_AllBlackPieces[from] = 0;
        m_BlackKnights[from] = 0;
        m_AllBlackPieces[to] = 1;
        if (!promoted) m_BlackKnights[to] = 1;
        else m_BlackPromotedKnights[to] = 1;
        break;
    case BlackSilver:
        m_AllBlackPieces[from] = 0;
        m_BlackSilvers[from] = 0;
        m_AllBlackPieces[to] = 1;
        if (!promoted) m_BlackSilvers[to] = 1;
        else m_BlackPromotedSilvers[to] = 1;
        break;
    case BlackGold:
        m_AllBlackPieces[from] = 0;
        m_BlackGolds[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackGolds[to] = 1;
        break;
    case BlackKing:
        m_AllBlackPieces[from] = 0;
        m_BlackKing[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackKing[to] = 1;
        break;
    case BlackBishop:
        m_AllBlackPieces[from] = 0;
        m_BlackBishops[from] = 0;
        m_AllBlackPieces[to] = 1;
        if (!promoted) m_BlackBishops[to] = 1;
        else m_BlackPromotedBishops[to] = 1;
        break;
    case BlackRook:
        m_AllBlackPieces[from] = 0;
        m_BlackRooks[from] = 0;
        m_AllBlackPieces[to] = 1;
        if (!promoted) m_BlackRooks[to] = 1;
        else m_BlackPromotedRooks[to] = 1;
        break;
    case BlackPromotedPawn:
        m_AllBlackPieces[from] = 0;
        m_BlackPromotedPawns[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackPromotedPawns[to] = 1;
        break;
    case BlackPromotedLance:
        m_AllBlackPieces[from] = 0;
        m_BlackPromotedLances[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackPromotedLances[to] = 1;
    case BlackPromotedKnight:
        m_AllBlackPieces[from] = 0;
        m_BlackPromotedKnights[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackPromotedKnights[to] = 1;
    case BlackPromotedSilver:
        m_AllBlackPieces[from] = 0;
        m_BlackPromotedSilvers[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackPromotedSilvers[to] = 1;
    case BlackPromotedBishop:
        m_AllBlackPieces[from] = 0;
        m_BlackPromotedBishops[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackPromotedBishops[to] = 1;
    case BlackPromotedRook:
        m_AllBlackPieces[from] = 0;
        m_BlackPromotedRooks[from] = 0;
        m_AllBlackPieces[to] = 1;
        m_BlackPromotedRooks[to] = 1;
    case WhitePawn:
        m_AllWhitePieces[from] = 0;
        m_WhitePawns[from] = 0;
        m_AllWhitePieces[to] = 1;
        if (!promoted) m_WhitePawns[to] = 1;
        else m_WhitePromotedPawns[to] = 1;
        break;
    case WhiteLance:
        m_AllWhitePieces[from] = 0;
        m_WhiteLances[from] = 0;
        m_AllWhitePieces[to] = 1;
        if (!promoted) m_WhiteLances[to] = 1;
        else m_WhitePromotedLances[to] = 1;
        break;
    case WhiteKnight:
        m_AllWhitePieces[from] = 0;
        m_WhiteKnights[from] = 0;
        m_AllWhitePieces[to] = 1;
        if (!promoted) m_WhiteKnights[to] = 1;
        else m_WhitePromotedKnights[to] = 1;
        break;
    case WhiteSilver:
        m_AllWhitePieces[from] = 0;
        m_WhiteSilvers[from] = 0;
        m_AllWhitePieces[to] = 1;
        if (!promoted) m_WhiteSilvers[to] = 1;
        else m_WhitePromotedSilvers[to] = 1;
        break;
    case WhiteGold:
        m_AllWhitePieces[from] = 0;
        m_WhiteGolds[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhiteGolds[to] = 1;
        break;
    case WhiteKing:
        m_AllWhitePieces[from] = 0;
        m_WhiteKing[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhiteKing[to] = 1;
        break;
    case WhiteBishop:
        m_AllWhitePieces[from] = 0;
        m_WhiteBishops[from] = 0;
        m_AllWhitePieces[to] = 1;
        if (!promoted) m_WhiteBishops[to] = 1;
        else m_WhitePromotedBishops[to] = 1;
        break;
    case WhiteRook:
        m_AllWhitePieces[from] = 0;
        m_WhiteRooks[from] = 0;
        m_AllWhitePieces[to] = 1;
        if (!promoted) m_WhiteRooks[to] = 1;
        else m_WhitePromotedRooks[to] = 1;
        break;
    case WhitePromotedPawn:
        m_AllWhitePieces[from] = 0;
        m_WhitePromotedPawns[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhitePromotedPawns[to] = 1;
        break;
    case WhitePromotedLance:
        m_AllWhitePieces[from] = 0;
        m_WhitePromotedLances[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhitePromotedLances[to] = 1;
    case WhitePromotedKnight:
        m_AllWhitePieces[from] = 0;
        m_WhitePromotedKnights[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhitePromotedKnights[to] = 1;
    case WhitePromotedSilver:
        m_AllWhitePieces[from] = 0;
        m_WhitePromotedSilvers[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhitePromotedSilvers[to] = 1;
    case WhitePromotedBishop:
        m_AllWhitePieces[from] = 0;
        m_WhitePromotedBishops[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhitePromotedBishops[to] = 1;
    case WhitePromotedRook:
        m_AllWhitePieces[from] = 0;
        m_WhitePromotedRooks[from] = 0;
        m_AllWhitePieces[to] = 1;
        m_WhitePromotedRooks[to] = 1;
    default:
        ; // unreachable
    }

    m_AllPieces[from] = 0;
    m_AllPieces[to] = 1;

    if (!m_edit_mode) {
        // log the move
        m_moves.push_back(move);

        // prepare for next move
        if (m_sidetomove == Black) m_sidetomove = White;
        else m_sidetomove = Black;
        m_movecount++;
    }
}


void Board::dropPiece(Piece piece, Cell to)
{
    assert(piece == BlackPawn || piece == BlackLance || piece == BlackKnight || piece == BlackSilver || piece == BlackGold || piece == BlackBishop || piece == BlackRook ||
           piece == WhitePawn || piece == WhiteLance || piece == WhiteKnight || piece == WhiteSilver || piece == WhiteGold || piece == WhiteBishop || piece == WhiteRook );
    assert(!cell(to).has_value());

    m_AllPieces[to] = 1;
    switch (piece) {
    case BlackPawn:
        m_AllBlackPieces[to] = 1;
        m_BlackPawns[to] = 1;
        assert(m_BlackHand[Hand::Pawn] > 0);
        m_BlackHand[Hand::Pawn]--;
        break;
    case BlackLance:
        m_AllBlackPieces[to] = 1;
        m_BlackLances[to] = 1;
        assert(m_BlackHand[Hand::Lance] > 0);
        m_BlackHand[Hand::Lance]--;
        break;
    case BlackKnight:
        m_AllBlackPieces[to] = 1;
        m_BlackKnights[to] = 1;
        assert(m_BlackHand[Hand::Knight] > 0);
        m_BlackHand[Hand::Knight]--;
        break;
    case BlackSilver:
        m_AllBlackPieces[to] = 1;
        m_BlackSilvers[to] = 1;
        assert(m_BlackHand[Hand::Silver] > 0);
        m_BlackHand[Hand::Silver]--;
        break;
    case BlackGold:
        m_AllBlackPieces[to] = 1;
        m_BlackGolds[to] = 1;
        assert(m_BlackHand[Hand::Gold] > 0);
        m_BlackHand[Hand::Gold]--;
        break;
    case BlackBishop:
        m_AllBlackPieces[to] = 1;
        m_BlackBishops[to] = 1;
        assert(m_BlackHand[Hand::Bishop] > 0);
        m_BlackHand[Hand::Bishop]--;
        break;
    case BlackRook:
        m_AllBlackPieces[to] = 1;
        m_BlackRooks[to] = 1;
        assert(m_BlackHand[Hand::Rook] > 0);
        m_BlackHand[Hand::Rook]--;
        break;
    case WhitePawn:
        m_AllWhitePieces[to] = 1;
        m_WhitePawns[to] = 1;
        assert(m_WhiteHand[Hand::Pawn] > 0);
        m_WhiteHand[Hand::Pawn]--;
        break;
    case WhiteLance:
        m_AllWhitePieces[to] = 1;
        m_WhiteLances[to] = 1;
        assert(m_WhiteHand[Hand::Lance] > 0);
        m_WhiteHand[Hand::Lance]--;
        break;
    case WhiteKnight:
        m_AllWhitePieces[to] = 1;
        m_WhiteKnights[to] = 1;
        assert(m_WhiteHand[Hand::Knight] > 0);
        m_WhiteHand[Hand::Knight]--;
        break;
    case WhiteSilver:
        m_AllWhitePieces[to] = 1;
        m_WhiteSilvers[to] = 1;
        assert(m_WhiteHand[Hand::Silver] > 0);
        m_WhiteHand[Hand::Silver]--;
        break;
    case WhiteGold:
        m_AllWhitePieces[to] = 1;
        m_WhiteGolds[to] = 1;
        assert(m_WhiteHand[Hand::Gold] > 0);
        m_WhiteHand[Hand::Gold]--;
        break;
    case WhiteBishop:
        m_AllWhitePieces[to] = 1;
        m_WhiteBishops[to] = 1;
        assert(m_WhiteHand[Hand::Bishop] > 0);
        m_WhiteHand[Hand::Bishop]--;
        break;
    case WhiteRook:
        m_AllWhitePieces[to] = 1;
        m_WhiteRooks[to] = 1;
        assert(m_WhiteHand[Hand::Rook] > 0);
        m_WhiteHand[Hand::Rook]--;
        break;
    default:
        ; // unreachable
    }

    if (!m_edit_mode) {
        // log the move
        auto drop = std::make_shared<Drop>(piece, to);
        m_moves.push_back(drop);

        // prepare for next move
        if (m_sidetomove == Black) m_sidetomove = White;
        else m_sidetomove = Black;
        m_movecount++;
    }
}


void Board::set_start_position_board_state(const std::string str)
{
    std::stringstream board_state(str);
    std::vector<std::string> ranks;

    std::string token;
    while (std::getline(board_state, token, '/')) {
        ranks.push_back(token);
    }
    if (ranks.size() != 9) {
        throw std::invalid_argument("invalid sfen: missing at least one rank in board state");
    }

    unsigned int file;
    unsigned int index;
    bool promoted = false;
    for (unsigned int rank=0; rank<9; ++rank) {
        file = 0;   // TODO: check file <9
        for (const char& cell : ranks[rank]) {
            if (isdigit(cell)) {
                file += int(cell) - '0';
            }
            else {
                index = rank*9+file;
                file++;

                m_AllPieces[index] = 1;
                switch(cell) {
                case '+':
                    promoted = true;
                    file--;    // we must stay on same cell for next character defining the piece type
                    break;
                case 'P':
                    m_AllBlackPieces[index] = 1;
                    if (promoted) {
                        m_BlackPromotedPawns[index] = 1;
                        promoted = false;
                    }
                    else m_BlackPawns[index] = 1;
                    break;
                case 'L':
                    m_AllBlackPieces[index] = 1;
                    if (promoted) {
                        m_BlackPromotedLances[index] = 1;
                        promoted = false;
                    }
                    else m_BlackLances[index] = 1;
                    break;
                case 'N':
                    m_AllBlackPieces[index] = 1;
                    if (promoted) {
                        m_BlackPromotedKnights[index] = 1;
                        promoted = false;
                    }
                    else m_BlackKnights[index] = 1;
                    break;
                case 'S':
                    m_AllBlackPieces[index] = 1;
                    if (promoted) {
                        m_BlackPromotedSilvers[index] = 1;
                        promoted = false;
                    }
                    else m_BlackSilvers[index] = 1;
                    break;
                case 'G':
                    m_AllBlackPieces[index] = 1;
                    m_BlackGolds[index] = 1;
                    break;
                case 'B':
                    m_AllBlackPieces[index] = 1;
                    if (promoted) {
                        m_BlackPromotedBishops[index] = 1;
                        promoted = false;
                    }
                    else m_BlackBishops[index] = 1;
                    break;
                case 'R':
                    m_AllBlackPieces[index] = 1;
                    m_AllBlackPieces[index] = 1;
                    if (promoted) {
                        m_BlackPromotedRooks[index] = 1;
                        promoted = false;
                    }
                    else m_BlackRooks[index] = 1;
                    break;
                case 'K':
                    m_AllBlackPieces[index] = 1;
                    m_BlackKing[index] = 1;
                    break;
                case 'p':
                    m_AllWhitePieces[index] = 1;
                    if (promoted) {
                        m_WhitePromotedPawns[index] = 1;
                        promoted = false;
                    }
                    else m_WhitePawns[index] = 1;
                    break;
                case 'l':
                    m_AllWhitePieces[index] = 1;
                    if (promoted) {
                        m_WhitePromotedLances[index] = 1;
                        promoted = false;
                    }
                    else m_WhiteLances[index] = 1;
                    break;
                case 'n':
                    m_AllWhitePieces[index] = 1;
                    if (promoted) {
                        m_WhitePromotedKnights[index] = 1;
                        promoted = false;
                    }
                    else m_WhiteKnights[index] = 1;
                    break;
                case 's':
                    m_AllWhitePieces[index] = 1;
                    if (promoted) {
                        m_WhitePromotedSilvers[index] = 1;
                        promoted = false;
                    }
                    else m_WhiteSilvers[index] = 1;
                    break;
                case 'g':
                    m_AllWhitePieces[index] = 1;
                    m_WhiteGolds[index] = 1;
                    break;
                case 'b':
                    m_AllWhitePieces[index] = 1;
                    if (promoted) {
                        m_WhitePromotedBishops[index] = 1;
                        promoted = false;
                    }
                    else m_WhiteBishops[index] = 1;
                    break;
                case 'r':
                    m_AllWhitePieces[index] = 1;
                    if (promoted) {
                        m_WhitePromotedRooks[index] = 1;
                        promoted = false;
                    }
                    else m_WhiteRooks[index] = 1;
                    break;
                case 'k':
                    m_AllWhitePieces[index] = 1;
                    m_WhiteKing[index] = 1;
                    break;
                default:
                    throw std::invalid_argument("invalid sfen: incorrect letter found in board state field");
                }
            }
        }
    }
}


void Board::set_start_pieces_in_hands(const std::string str)
{
    char tokenUpper;
    unsigned short piece_count = 1;
    for (const char& token : str) {
        if (isdigit(token)) {
            piece_count = int(token) - '0';
            continue;
        }

        tokenUpper = toupper(token);
        if (token == tokenUpper) {
            switch(tokenUpper) {
            case 'P':
                m_BlackHand[Hand::Pawn] = piece_count;
                break;
            case 'L':
                m_BlackHand[Hand::Lance] = piece_count;
                break;
            case 'N':
                m_BlackHand[Hand::Knight] = piece_count;
                break;
            case 'S':
                m_BlackHand[Hand::Silver] = piece_count;
                break;
            case 'G':
                m_BlackHand[Hand::Gold] = piece_count;
                break;
            case 'B':
                m_BlackHand[Hand::Bishop] = piece_count;
                break;
            case 'R':
                m_BlackHand[Hand::Rook] = piece_count;
                break;
            default:
                throw std::invalid_argument("invalid sfen: incorrect letter found in black hand");
            }
        }
        else {
            switch(tokenUpper) {
            case 'P':
                m_WhiteHand[Hand::Pawn] = piece_count;
                break;
            case 'L':
                m_WhiteHand[Hand::Lance] = piece_count;
                break;
            case 'N':
                m_WhiteHand[Hand::Knight] = piece_count;
                break;
            case 'S':
                m_WhiteHand[Hand::Silver] = piece_count;
                break;
            case 'G':
                m_WhiteHand[Hand::Gold] = piece_count;
                break;
            case 'B':
                m_WhiteHand[Hand::Bishop] = piece_count;
                break;
            case 'R':
                m_WhiteHand[Hand::Rook] = piece_count;
                break;
            default:
                throw std::invalid_argument("invalid sfen: incorrect letter found in white hand");
            }
        }
        piece_count = 1;
    }
}


void Board::editModeOn()
{
    m_edit_mode = true;
    m_movecount = 1;
    m_moves.clear();
};


void Board::editModeOff() { m_edit_mode = false; };


void Board::switchSideToMove()
{
    if (m_edit_mode) {
        if (m_sidetomove == Black) m_sidetomove = White;
        else m_sidetomove = Black;
    }
}


std::ostream& operator<<(std::ostream& os, const Board& board)
{
    char buf[4];
    std::optional<shogi::Piece> piece;
    std::string piece_str;

    os << " 9  8  7  6  5  4  3  2  1" << std::endl;
    os << "---------------------------" << std::endl;
    for (unsigned int rank=0; rank<=8; ++rank) {
        for (unsigned int file=0; file<=8; ++file) {
            piece = board.cell(rank, file);
            if (piece.has_value()) {
                piece_str = shogi::pieceSymbol(*piece);
                sprintf(buf, "%2s ", piece_str.c_str());
                os << std::string(buf);
            }
            else {
                os << " . ";
            }
        }
        os << "|" << static_cast<char>('a'+rank) << std::endl;
    }
    os << "---------------------------" << std::endl;

    os << "Black Hand: ";
    if (auto n = board.blackHand()[Board::Hand::Pawn]; n > 0)   os << n << "xP ";
    if (auto n = board.blackHand()[Board::Hand::Lance]; n > 0)  os << n << "xL ";
    if (auto n = board.blackHand()[Board::Hand::Knight]; n > 0) os << n << "xN ";
    if (auto n = board.blackHand()[Board::Hand::Silver]; n > 0) os << n << "xP ";
    if (auto n = board.blackHand()[Board::Hand::Gold]; n > 0)   os << n << "xS ";
    if (auto n = board.blackHand()[Board::Hand::Bishop]; n > 0) os << n << "xB ";
    if (auto n = board.blackHand()[Board::Hand::Rook]; n > 0)   os << n << "xR";
    os << std::endl;

    os << "White Hand: ";
    if (auto n = board.whiteHand()[Board::Hand::Pawn]; n > 0)   os << n << "xP ";
    if (auto n = board.whiteHand()[Board::Hand::Lance]; n > 0)  os << n << "xL ";
    if (auto n = board.whiteHand()[Board::Hand::Knight]; n > 0) os << n << "xN ";
    if (auto n = board.whiteHand()[Board::Hand::Silver]; n > 0) os << n << "xP ";
    if (auto n = board.whiteHand()[Board::Hand::Gold]; n > 0)   os << n << "xS ";
    if (auto n = board.whiteHand()[Board::Hand::Bishop]; n > 0) os << n << "xB ";
    if (auto n = board.whiteHand()[Board::Hand::Rook]; n > 0)   os << n << "xR";
    os << std::endl;

    return os;
}


} // namespace shogi
