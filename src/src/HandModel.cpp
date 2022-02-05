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

    std::array<unsigned short, 7> hand;
    if (m_color == shogi::Black) hand = m_board.blackHand();
    else hand = m_board.whiteHand();

    if (role == PieceCount) {
        return QVariant(hand[indexRow]);
    }

    if (role == PieceType) {
        switch(indexRow) {
        case 0: return QVariant(shogi::Pawn); break;
        case 1: return QVariant(shogi::Lance); break;
        case 2: return QVariant(shogi::Knight); break;
        case 3: return QVariant(shogi::Silver); break;
        case 4: return QVariant(shogi::Gold); break;
        case 5: return QVariant(shogi::Bishop); break;
        case 6: return QVariant(shogi::Rook); break;
        default: return QVariant();
        }
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
