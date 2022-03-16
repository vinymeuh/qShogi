/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "BoardModel.h"

#include <QQuickItem>
#include <QQuickView>
#include <QQmlComponent>


BoardModel::BoardModel(shogi::Board& board, QObject* parent)
    : QAbstractListModel(parent), m_board(board)
{}


int BoardModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_board.squares();
}


QVariant BoardModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)
    if (index.row() < 0 || index.row() >= m_board.squares())
        return QVariant();

    return QString::fromStdString(
                m_board[index.row()].piece.toString()
            );
}

void BoardModel::onDataChanged()
{
    beginResetModel();
    endResetModel();
}
