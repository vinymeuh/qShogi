#include "catch.hpp"
#include "shogi/shogi.h"

using namespace shogi;

TEST_CASE("Piece symbol")
{
    REQUIRE(pieceSymbol(BlackPawn) == "P");
    REQUIRE(pieceSymbol(WhitePawn) == "p");
}


TEST_CASE("Piece color")
{
    REQUIRE(pieceColor(BlackPawn) == Black);
    REQUIRE(pieceColor(WhitePawn) == White);
}


TEST_CASE("Piece is promoted")
{
    REQUIRE(!pieceIsPromoted(BlackPawn));

    REQUIRE(pieceIsPromoted(BlackPromotedPawn));
}

TEST_CASE("Piece can promote")
{
    REQUIRE(pieceCanPromote(BlackPawn, Cell::d9, Cell::c9));
    REQUIRE(pieceCanPromote(BlackPawn, Cell::c9, Cell::b9));

    REQUIRE(!pieceCanPromote(BlackPawn, Cell::g1, Cell::f1));
    REQUIRE(!pieceCanPromote(BlackPromotedPawn, Cell::d9, Cell::c9));

    REQUIRE(pieceCanPromote(WhitePawn, Cell::f5, Cell::g5));
    REQUIRE(pieceCanPromote(WhitePawn, Cell::g5, Cell::h5));

    REQUIRE(!pieceCanPromote(WhitePawn, Cell::c2, Cell::d2));
    REQUIRE(!pieceCanPromote(WhitePromotedPawn, Cell::f5, Cell::g5));

    REQUIRE(!pieceCanPromote(BlackKing, Cell::d7,  Cell::c7));
    REQUIRE(!pieceCanPromote(BlackGold, Cell::c8,  Cell::b8));
}

TEST_CASE("Piece must promote")
{
    REQUIRE(pieceMustPromote(BlackPawn, Cell::a2));
    REQUIRE(pieceMustPromote(BlackLance, Cell::a9));
    REQUIRE(pieceMustPromote(BlackKnight, Cell::b3));

    REQUIRE(!pieceMustPromote(BlackSilver, Cell::a2));
    REQUIRE(!pieceMustPromote(BlackPromotedPawn, Cell::a2));
    REQUIRE(!pieceMustPromote(BlackPromotedLance, Cell::a2));
    REQUIRE(!pieceMustPromote(BlackPromotedKnight, Cell::b3));

    REQUIRE(pieceMustPromote(WhitePawn, Cell::i2));
    REQUIRE(pieceMustPromote(WhiteLance, Cell::i9));
    REQUIRE(pieceMustPromote(WhiteKnight, Cell::h3));

    REQUIRE(!pieceMustPromote(WhiteSilver, Cell::i2));
    REQUIRE(!pieceMustPromote(WhitePromotedPawn, Cell::i2));
    REQUIRE(!pieceMustPromote(WhitePromotedLance, Cell::i9));
    REQUIRE(!pieceMustPromote(WhitePromotedKnight, Cell::h3));
}
