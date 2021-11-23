/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "GameLogModel.h"


GameLogModel::GameLogModel(shogi::Board& board, QObject* parent)
    : QAbstractListModel(parent), m_board(board)
{
}


int GameLogModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_board.moves().size();
}


QVariant GameLogModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)
    if (index.row() < 0 || index.row() >= m_board.moves().size())
        return QVariant();
    auto move = m_board.moves()[index.row()];

    if (role == Count) {
        return index.row()+1;
    }

    if (role == Internal) {
        return QString::fromStdString(move->toString(shogi::MoveFormat::Debug));
    }

    if (role == USI) {
        return QString::fromStdString(move->toString(shogi::MoveFormat::USI));
    }

    return QVariant();
}


void GameLogModel::onDataChanged()
{
    beginResetModel();
    endResetModel();
}


QHash<int, QByteArray> GameLogModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Count] = "count";
    roles[Internal] = "internal";
    roles[USI] = "usi";
    return roles;
}
