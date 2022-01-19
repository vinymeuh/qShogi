#include "catch.hpp"

#include "shogi.h"

using namespace shogi;

TEST_CASE("Board start position initialization")
{
    Board board;

    SECTION("initialization from default sfen string") {
        REQUIRE_NOTHROW(board.set_start_position());
        REQUIRE(board.sfen() == sfen_even);
    }

    SECTION("initialization using valid sfen_even string") {
        REQUIRE_NOTHROW(board.set_start_position(sfen_even));
        REQUIRE(board.sfen() == sfen_even);
    }

    SECTION("initialization using valid sfen string without movecount") {
        REQUIRE_NOTHROW(board.set_start_position("lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b -"));
        REQUIRE(board.sfen() == sfen_even);
    }

    SECTION("Board from the 3rd game of the 19th Ryu-O match between Sato and Watanabe") {
        REQUIRE_NOTHROW(board.set_start_position("8l/1l+R2P3/p2pBG1pp/kps1p4/Nn1P2G2/P1P1P2PP/1PS6/1KSG3+r1/LN2+p3L w Sbgn3p 124"));
        REQUIRE(board.sfen() == "8l/1l+R2P3/p2pBG1pp/kps1p4/Nn1P2G2/P1P1P2PP/1PS6/1KSG3+r1/LN2+p3L w Sbgn3p 124");
    }

    SECTION("initialization using invalid sfen string") {
        REQUIRE_THROWS_AS(board.set_start_position("dummy"), std::invalid_argument);
        REQUIRE_THROWS_AS(board.set_start_position("lnsgkgsnl/1r5b1/ppppppppp/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1"), std::invalid_argument);
        REQUIRE_THROWS_AS(board.set_start_position("lnsgkgsnl/1r5b1/pppppxppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1"), std::invalid_argument);
        REQUIRE_THROWS_AS(board.set_start_position("lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL x - 1"), std::invalid_argument);
        REQUIRE_THROWS_AS(board.set_start_position("lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b x 1"), std::invalid_argument);
        REQUIRE_THROWS_AS(board.set_start_position("lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - x"), std::invalid_argument);
    }
}

TEST_CASE("Basic moves with Cell")
{
    Board b2;
    b2.set_start_position();
    REQUIRE(b2.sideToMove() == shogi::Black);
    REQUIRE(b2.moveCount() == 1);

    b2.shiftPiece(Cell::C1g, Cell::C1f);
    REQUIRE(!b2.cell(Cell::C1g).has_value());
    REQUIRE(b2.cell(Cell::C1f) == BlackPawn);
    REQUIRE(b2.moves()[0]->toString() == "1g1f");

    b2.shiftPiece(Cell::C1c, Cell::C1d);
    REQUIRE(!b2.cell(Cell::C1c).has_value());
    REQUIRE(b2.cell(Cell::C1d) == WhitePawn);
    REQUIRE(b2.moves()[1]->toString() == "1c1d");

    b2.shiftPiece(Cell::C1f, Cell::C1e);
    REQUIRE(b2.cell(Cell::C1e) == BlackPawn);
    REQUIRE(b2.moves()[2]->toString() == "1f1e");

    b2.shiftPiece(Cell::C1d, Cell::C1e);   // capture
    REQUIRE(b2.cell(Cell::C1e) == WhitePawn);
    REQUIRE(b2.whiteHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[3]->toString() == "1d1e");

    b2.shiftPiece(Cell::C1i, Cell::C1e);   // capture
    REQUIRE(b2.cell(Cell::C1e) == BlackLance);
    REQUIRE(b2.blackHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[4]->toString() == "1i1e");

    b2.dropPiece(WhitePawn, Cell::C1c); // drop
    REQUIRE(b2.cell(Cell::C1c) == WhitePawn);
    REQUIRE(b2.whiteHand()[Board::Hand::Pawn] == 0);
    REQUIRE(b2.moves()[5]->toString() == "P*1c");

    b2.shiftPiece(Cell::C1e, Cell::C1c, true); // capture + promotion
    REQUIRE(b2.cell(Cell::C1c) == BlackPromotedLance);
    REQUIRE(b2.blackHand()[Board::Hand::Pawn] == 2);
    REQUIRE(b2.moves()[6]->toString() == "1e1c+");

    b2.shiftPiece(Cell::C1a, Cell::C1c);   // capture
    REQUIRE(b2.cell(Cell::C1c) == WhiteLance);
    REQUIRE(b2.whiteHand()[Board::Hand::Lance] == 1);
    REQUIRE(b2.moves()[7]->toString() == "1a1c");

    b2.dropPiece(BlackPawn, Cell::C1g); // drop
    REQUIRE(b2.cell(Cell::C1g) == BlackPawn);
    REQUIRE(b2.blackHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[8]->toString() == "P*1g");

    b2.shiftPiece(Cell::C1c, Cell::C1g, true); // capture + promotion
    REQUIRE(b2.cell(Cell::C1g) == WhitePromotedLance);
    REQUIRE(b2.whiteHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[9]->toString() == "1c1g+");

    REQUIRE(b2.moveCount() == 11);  // 10 moves played, next one is 11
}
