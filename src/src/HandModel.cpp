/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "HandModel.h"


int HandModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 7;
}


QVariant HandModel::data(const QModelIndex& index, int role) const
{
    int indexRow = index.row();
    if (indexRow < 0 || indexRow >= rowCount())
        return QVariant();

    shogi::Type piece_type;
    switch(indexRow) {
    case 0: piece_type = shogi::Type::pawn; break;
    case 1: piece_type = shogi::Type::lance; break;
    case 2: piece_type = shogi::Type::knight; break;
    case 3: piece_type = shogi::Type::silver; break;
    case 4: piece_type = shogi::Type::gold; break;
    case 5: piece_type = shogi::Type::bishop; break;
    case 6: piece_type = shogi::Type::rook; break;
    }

    if (role == PieceCount) {
        return QVariant(m_board.hand(m_color, piece_type));
    }

    if (role == PieceType) {
        return QVariant(static_cast<int>(piece_type));
    }

    return QVariant();
}


void HandModel::onDataChanged()
{
    beginResetModel();
    endResetModel();
}


QHash<int, QByteArray> HandModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PieceCount] = "piececount";
    roles[PieceType] = "piecetype";
    return roles;
}
