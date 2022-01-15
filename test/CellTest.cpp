#include "catch.hpp"
#include "shogi/shogi.h"

using namespace shogi;

TEST_CASE("Cell mapping" )
{
    REQUIRE(Cell::C9a == 0);
    REQUIRE(Cell::C1a == 8);

    REQUIRE(Cell::C9b == 9);
    REQUIRE(Cell::C1b == 17);

    REQUIRE(Cell::C9c == 18);
    REQUIRE(Cell::C1c == 26);

    REQUIRE(Cell::C9d == 27);
    REQUIRE(Cell::C1d == 35);

    REQUIRE(Cell::C9e == 36);
    REQUIRE(Cell::C1e == 44);

    REQUIRE(Cell::C9f == 45);
    REQUIRE(Cell::C1f == 53);

    REQUIRE(Cell::C9g == 54);
    REQUIRE(Cell::C1g == 62);

    REQUIRE(Cell::C9h == 63);
    REQUIRE(Cell::C1h == 71);

    REQUIRE(Cell::C9i == 72);
    REQUIRE(Cell::C1i == 80);
}
