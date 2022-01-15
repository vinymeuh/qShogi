/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef CELL_H
#define CELL_H

#include <string>
#include <iostream>


namespace shogi {

/*
 * Cell provides direct mapping between Hodges shogi's coordinates notation (1a to 9i) and an index between 0 and 80.
 * It is not an enum class as we want implicit int conversions for bitboards manipulations.
 */
enum Cell {
    C9a=0,C8a,C7a,C6a,C5a,C4a,C3a,C2a,C1a,
    C9b  ,C8b,C7b,C6b,C5b,C4b,C3b,C2b,C1b,
    C9c  ,C8c,C7c,C6c,C5c,C4c,C3c,C2c,C1c,
    C9d  ,C8d,C7d,C6d,C5d,C4d,C3d,C2d,C1d,
    C9e  ,C8e,C7e,C6e,C5e,C4e,C3e,C2e,C1e,
    C9f  ,C8f,C7f,C6f,C5f,C4f,C3f,C2f,C1f,
    C9g  ,C8g,C7g,C6g,C5g,C4g,C3g,C2g,C1g,
    C9h  ,C8h,C7h,C6h,C5h,C4h,C3h,C2h,C1h,
    C9i  ,C8i,C7i,C6i,C5i,C4i,C3i,C2i,C1i,
};


inline std::string HodgesNotation(Cell c) {
    auto file = 9 - c%9;
    char rank = char('a') + (int)c/9;
    return std::to_string(file) + rank;
}


inline std::string HoskingNotation(Cell c) {
    auto file = 9 - c%9;
    auto rank = 1+ (int)c/9;
    return std::to_string(file) + std::to_string(rank);
}


}   // namespace shogi

#endif // CELL_H
