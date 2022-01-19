/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef SHOGI_H
#define SHOGI_H

#include <iostream>
#include "Board.h"
#include "Cell.h"
#include "Piece.h"
#include "Move.h"

namespace shogi {

std::ostream& operator<<(std::ostream& os, const Board& board);
std::ostream& operator<<(std::ostream& os, const Move& move);

} // namespace shogi

#endif // SHOGI_H
