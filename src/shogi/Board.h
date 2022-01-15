/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <bitset>
#include <memory>
#include <string>
#include <vector>
#include "Cell.h"
#include "Piece.h"
#include "Move.h"

namespace shogi {

/*
 * Board is an assembly of pieces positions represented by bitboards, hands and a moves log.
 * Board state is initialized from a SFEN string.
 */
using bitboard = std::bitset<81>;

const std::string sfen_even = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";
const std::string sfen_handicap_lance = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/1NSGKGSNL w - 1";
const std::string sfen_handicap_bishop = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/7R1/LNSGKGSNL w - 1";
const std::string sfen_handicap_rook = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B7/LNSGKGSNL w - 1";
const std::string sfen_handicap_rook_lance = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B7/1NSGKGSNL w - 1";
const std::string sfen_handicap_2pieces = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/9/LNSGKGSNL w - 1";
const std::string sfen_handicap_4pieces = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/9/1NSGKGSN1 w - 1";
const std::string sfen_handicap_6pieces = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/9/2SGKGS2 w - 1";
const std::string sfen_handicap_8pieces = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/9/3GKG3 w - 1";
const std::string sfen_handicap_10pieces = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/9/4K4 w - 1";


class Board
{
public:
    enum Hand {
        Pawn = 0, Lance, Knight, Silver, Gold, Bishop, Rook
    };

    Board() {};

    void set_start_position(const std::string sfen=sfen_even);
    void clear();

    // Returns current state of the board as a SFEN string.
    std::string const sfen();

    // Returns Hand for the black player or the white player.
    const std::array<unsigned short, 7> blackHand() const { return m_BlackHand; }
    const std::array<unsigned short, 7> whiteHand() const { return m_WhiteHand; }

    // Returns the color of the current side to move.
    Color sideToMove() const { return m_sidetomove; }

    // Returns the current move count as defined in SFEN specification.
    // Note that this one is NEVER equals to moves().size(), don't use it to iterate on moves() returned vector.
    unsigned int moveCount() const { return m_movecount; }

    // Returns moves log.
    std::vector<std::shared_ptr<Move>> moves() const { return m_moves; }

    // Returns piece occuping cell at given position or nothing.
    std::optional<Piece> cell(const Cell index) const;
    std::optional<Piece> cell(const unsigned int rank, const unsigned int file) const { return cell(static_cast<Cell>(rank*9+file)); }

    std::string pieceStringAt(const Cell index) const;
    std::string pieceStringAt(const unsigned int rank, const unsigned int file) const { return pieceStringAt(static_cast<Cell>(rank*9+file)); }

    // Updates board with a move WITHOUT move validation.
    void shiftPiece(Cell from, Cell to, bool promoted=false);
    void dropPiece(Piece piece, Cell to);

    inline bool canPromote(Cell from, Cell to)
    {
        if (auto p = cell(from); p.has_value()) return pieceCanPromote(*p, from, to);
        else return false;
    }

    inline bool mustPromote(Cell from, Cell to)
    {
        if (auto p = cell(from); p.has_value()) return pieceMustPromote(*p, to);
        else return false;
    }

    // Settings
    void editModeOn();
    void editModeOff();
    void switchSideToMove();

private:
    // black piece positions
    bitboard m_BlackPawns;
    bitboard m_BlackLances;
    bitboard m_BlackKnights;
    bitboard m_BlackSilvers;
    bitboard m_BlackGolds;
    bitboard m_BlackBishops;
    bitboard m_BlackRooks;
    bitboard m_BlackKing;

    bitboard m_BlackPromotedPawns;
    bitboard m_BlackPromotedLances;
    bitboard m_BlackPromotedKnights;
    bitboard m_BlackPromotedSilvers;
    bitboard m_BlackPromotedBishops;
    bitboard m_BlackPromotedRooks;

    // white pieces positions
    bitboard m_WhitePawns;
    bitboard m_WhiteLances;
    bitboard m_WhiteKnights;
    bitboard m_WhiteSilvers;
    bitboard m_WhiteGolds;
    bitboard m_WhiteBishops;
    bitboard m_WhiteRooks;
    bitboard m_WhiteKing;

    bitboard m_WhitePromotedPawns;
    bitboard m_WhitePromotedLances;
    bitboard m_WhitePromotedKnights;
    bitboard m_WhitePromotedSilvers;
    bitboard m_WhitePromotedBishops;
    bitboard m_WhitePromotedRooks;

    // global pieces positions
    bitboard m_AllBlackPieces;
    bitboard m_AllWhitePieces;
    bitboard m_AllPieces;

    Color m_sidetomove;
    unsigned int m_movecount;

    // hands
    std::array<unsigned short, 7>  m_BlackHand;
    std::array<unsigned short, 7>  m_WhiteHand;

    // game log
    std::string m_starting_sfen;
    std::vector<std::shared_ptr<Move>> m_moves;

    // settings
    bool m_edit_mode = false;

    // sfen parsing used to initialize the board
    void set_start_position_board_state(const std::string str);
    void set_start_pieces_in_hands(const std::string str);
};

} // namespace shogi

#endif // BOARD_H
