/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef CELL_H
#define CELL_H

namespace shogi {

/*
 * Cell provides direct mapping between classic shogi's coordinates notation and an index between 0 and 80.
 * It is not an enum class as we want implicit int conversions for bitboards manipulations.
 */
enum Cell {
    a9=0,a8,a7,a6,a5,a4,a3,a2,a1,
    b9  ,b8,b7,b6,b5,b4,b3,b2,b1,
    c9  ,c8,c7,c6,c5,c4,c3,c2,c1,
    d9  ,d8,d7,d6,d5,d4,d3,d2,d1,
    e9  ,e8,e7,e6,e5,e4,e3,e2,e1,
    f9  ,f8,f7,f6,f5,f4,f3,f2,f1,
    g9  ,g8,g7,g6,g5,g4,g3,g2,g1,
    h9  ,h8,h7,h6,h5,h4,h3,h2,h1,
    i9  ,i8,i7,i6,i5,i4,i3,i2,i1,
};

constexpr const char* CellToString(Cell c) noexcept
{
    switch(c) {
    case a1: return "a1";
    case b1: return "b1";
    case c1: return "c1";
    case d1: return "d1";
    case e1: return "e1";
    case f1: return "f1";
    case g1: return "g1";
    case h1: return "h1";
    case i1: return "i1";
    case a2: return "a2";
    case b2: return "b2";
    case c2: return "c2";
    case d2: return "d2";
    case e2: return "e2";
    case f2: return "f2";
    case g2: return "g2";
    case h2: return "h2";
    case i2: return "i2";
    case a3: return "a3";
    case b3: return "b3";
    case c3: return "c3";
    case d3: return "d3";
    case e3: return "e3";
    case f3: return "f3";
    case g3: return "g3";
    case h3: return "h3";
    case i3: return "i3";
    case a4: return "a4";
    case b4: return "b4";
    case c4: return "c4";
    case d4: return "d4";
    case e4: return "e4";
    case f4: return "f4";
    case g4: return "g4";
    case h4: return "h4";
    case i4: return "i4";
    case a5: return "a5";
    case b5: return "b5";
    case c5: return "c5";
    case d5: return "d5";
    case e5: return "e5";
    case f5: return "f5";
    case g5: return "g5";
    case h5: return "h5";
    case i5: return "i5";
    case a6: return "a6";
    case b6: return "b6";
    case c6: return "c6";
    case d6: return "d6";
    case e6: return "e6";
    case f6: return "f6";
    case g6: return "g6";
    case h6: return "h6";
    case i6: return "i6";
    case a7: return "a7";
    case b7: return "b7";
    case c7: return "c7";
    case d7: return "d7";
    case e7: return "e7";
    case f7: return "f7";
    case g7: return "g7";
    case h7: return "h7";
    case i7: return "i7";
    case a8: return "a8";
    case b8: return "b8";
    case c8: return "c8";
    case d8: return "d8";
    case e8: return "e8";
    case f8: return "f8";
    case g8: return "g8";
    case h8: return "h8";
    case i8: return "i8";
    case a9: return "a9";
    case b9: return "b9";
    case c9: return "c9";
    case d9: return "d9";
    case e9: return "e9";
    case f9: return "f9";
    case g9: return "g9";
    case h9: return "h9";
    case i9: return "i9";
    }
    return "?";
}

}   // namespace shogi

#endif // CELL_H
