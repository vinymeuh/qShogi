#include "catch.hpp"
#include "shogi/shogi.h"

using namespace shogi;

TEST_CASE("Cell mapping" )
{
    REQUIRE(Cell::a9 == 0);
    REQUIRE(Cell::a1 == 8);

    REQUIRE(Cell::b9 == 9);
    REQUIRE(Cell::b1 == 17);

    REQUIRE(Cell::c9 == 18);
    REQUIRE(Cell::c1 == 26);

    REQUIRE(Cell::d9 == 27);
    REQUIRE(Cell::d1 == 35);

    REQUIRE(Cell::e9 == 36);
    REQUIRE(Cell::e1 == 44);

    REQUIRE(Cell::f9 == 45);
    REQUIRE(Cell::f1 == 53);

    REQUIRE(Cell::g9 == 54);
    REQUIRE(Cell::g1 == 62);

    REQUIRE(Cell::h9 == 63);
    REQUIRE(Cell::h1 == 71);

    REQUIRE(Cell::i9 == 72);
    REQUIRE(Cell::i1 == 80);
}
