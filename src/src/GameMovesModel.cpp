/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "GameMovesModel.h"


GameMovesModel::GameMovesModel(shogi::Board& board, QObject* parent)
    : QAbstractListModel(parent), m_board(board), m_format(shogi::Notation::USI)
{
}


int GameMovesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_board.moves();
}


QVariant GameMovesModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_board.moves())
        return QVariant();

    if (role == Move) {
        return QString("%1   %2")
                .arg(index.row()+1, 4)
                .arg(QString::fromStdString(m_board.moveNumber(index.row(), m_format)));
    }

    return QVariant();
}


void GameMovesModel::moveFormat(shogi::Notation format)
{
    m_format = format;
    onDataChanged();
}


void GameMovesModel::onDataChanged()
{
    beginResetModel();
    endResetModel();
}


QHash<int, QByteArray> GameMovesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Move] = "move";
    return roles;
}
