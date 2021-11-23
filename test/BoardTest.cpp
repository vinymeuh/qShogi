#include "catch.hpp"
#include "shogi/shogi.h"

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

    b2.shiftPiece(Cell::g1, Cell::f1);
    REQUIRE(!b2.cell(Cell::g1).has_value());
    REQUIRE(b2.cell(Cell::f1) == BlackPawn);
    REQUIRE(b2.moves()[0]->toString() == "g1f1");

    b2.shiftPiece(Cell::c1, Cell::d1);
    REQUIRE(!b2.cell(Cell::c1).has_value());
    REQUIRE(b2.cell(Cell::d1) == WhitePawn);
    REQUIRE(b2.moves()[1]->toString() == "c1d1");

    b2.shiftPiece(Cell::f1, Cell::e1);
    REQUIRE(b2.cell(Cell::e1) == BlackPawn);
    REQUIRE(b2.moves()[2]->toString() == "f1e1");

    b2.shiftPiece(Cell::d1, Cell::e1);   // capture
    REQUIRE(b2.cell(Cell::e1) == WhitePawn);
    REQUIRE(b2.whiteHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[3]->toString() == "d1e1");

    b2.shiftPiece(Cell::i1, Cell::e1);   // capture
    REQUIRE(b2.cell(Cell::e1) == BlackLance);
    REQUIRE(b2.blackHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[4]->toString() == "i1e1");

    b2.dropPiece(WhitePawn, Cell::c1); // drop
    REQUIRE(b2.cell(Cell::c1) == WhitePawn);
    REQUIRE(b2.whiteHand()[Board::Hand::Pawn] == 0);
    REQUIRE(b2.moves()[5]->toString() == "P*c1");

    b2.shiftPiece(Cell::e1, Cell::c1, true); // capture + promotion
    REQUIRE(b2.cell(Cell::c1) == BlackPromotedLance);
    REQUIRE(b2.blackHand()[Board::Hand::Pawn] == 2);
    REQUIRE(b2.moves()[6]->toString() == "e1c1+");

    b2.shiftPiece(Cell::a1, Cell::c1);   // capture
    REQUIRE(b2.cell(Cell::c1) == WhiteLance);
    REQUIRE(b2.whiteHand()[Board::Hand::Lance] == 1);
    REQUIRE(b2.moves()[7]->toString() == "a1c1");

    b2.dropPiece(BlackPawn, Cell::g1); // drop
    REQUIRE(b2.cell(Cell::g1) == BlackPawn);
    REQUIRE(b2.blackHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[8]->toString() == "P*g1");

    b2.shiftPiece(Cell::c1, Cell::g1, true); // capture + promotion
    REQUIRE(b2.cell(Cell::g1) == WhitePromotedLance);
    REQUIRE(b2.whiteHand()[Board::Hand::Pawn] == 1);
    REQUIRE(b2.moves()[9]->toString() == "c1g1+");

    REQUIRE(b2.moveCount() == 11);  // 10 moves played, next one is 11
}
