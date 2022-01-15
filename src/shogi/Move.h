/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef MOVE_H
#define MOVE_H

#include <optional>
#include <string>
#include "Cell.h"
#include "Piece.h"

namespace shogi {

/*
 * Move is an abstact class implemented by Shift and Drop.
 * Main goal of these classes is to store each movement played and be able to represent them in different format.
 * Note that there is no movements validation at this level, it is the solely responsibility of the Board class.
 */
enum class MoveFormat { Debug, USI, Hodges, Hosking };


class Move
{
public:
    virtual std::string toString(MoveFormat format=MoveFormat::USI) const = 0;
    virtual ~Move() {};
private:
    friend std::ostream& operator<<(std::ostream& os, const Move& move);
};


class Shift : public Move
{
    friend class Board;
public:
    Shift(Piece piece, Cell from, Cell to, bool promotable=false, bool promoted=false)
        : m_piece{piece}, m_captured{}, m_from{from}, m_to{to}, m_promotable{promotable}, m_promoted{promoted} {};

    std::string toString(MoveFormat format=MoveFormat::USI) const override;
private:
    Piece m_piece;
    std::optional<Piece> m_captured;
    Cell m_from;
    Cell m_to;
    bool m_promotable;
    bool m_promoted;
};


class Drop : public Move
{
    friend class Board;
public:
    Drop(Piece piece, Cell to) : m_piece{piece}, m_to{to} {};

    std::string toString(MoveFormat format=MoveFormat::USI) const override;
private:
    Piece m_piece;
    Cell m_to;
};

} // namespace shogi

#endif // MOVE_H
