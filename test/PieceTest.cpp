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
    REQUIRE(pieceCanPromote(BlackPawn, Cell::C9d, Cell::C9c));
    REQUIRE(pieceCanPromote(BlackPawn, Cell::C9c, Cell::C9b));

    REQUIRE(!pieceCanPromote(BlackPawn, Cell::C1g, Cell::C1f));
    REQUIRE(!pieceCanPromote(BlackPromotedPawn, Cell::C9d, Cell::C9c));

    REQUIRE(pieceCanPromote(WhitePawn, Cell::C5f, Cell::C5g));
    REQUIRE(pieceCanPromote(WhitePawn, Cell::C5g, Cell::C5h));

    REQUIRE(!pieceCanPromote(WhitePawn, Cell::C2c, Cell::C2d));
    REQUIRE(!pieceCanPromote(WhitePromotedPawn, Cell::C5f, Cell::C5g));

    REQUIRE(!pieceCanPromote(BlackKing, Cell::C7d,  Cell::C7c));
    REQUIRE(!pieceCanPromote(BlackGold, Cell::C8c,  Cell::C8b));
}

TEST_CASE("Piece must promote")
{
    REQUIRE(pieceMustPromote(BlackPawn, Cell::C2a));
    REQUIRE(pieceMustPromote(BlackLance, Cell::C9a));
    REQUIRE(pieceMustPromote(BlackKnight, Cell::C3b));

    REQUIRE(!pieceMustPromote(BlackSilver, Cell::C2a));
    REQUIRE(!pieceMustPromote(BlackPromotedPawn, Cell::C2a));
    REQUIRE(!pieceMustPromote(BlackPromotedLance, Cell::C2a));
    REQUIRE(!pieceMustPromote(BlackPromotedKnight, Cell::C3b));

    REQUIRE(pieceMustPromote(WhitePawn, Cell::C2i));
    REQUIRE(pieceMustPromote(WhiteLance, Cell::C9i));
    REQUIRE(pieceMustPromote(WhiteKnight, Cell::C3h));

    REQUIRE(!pieceMustPromote(WhiteSilver, Cell::C2i));
    REQUIRE(!pieceMustPromote(WhitePromotedPawn, Cell::C2i));
    REQUIRE(!pieceMustPromote(WhitePromotedLance, Cell::C9i));
    REQUIRE(!pieceMustPromote(WhitePromotedKnight, Cell::C3h));
}
