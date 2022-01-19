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
{
    //qDebug() << QString::fromStdString(m_board.SFEN());   FIXME
}


int BoardModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 9*9;
}


QVariant BoardModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)
    if (index.row() < 0 || index.row() >= 9*9)
        return QVariant();
    auto c = static_cast<shogi::Cell>(index.row());
    return QString::fromStdString(m_board.pieceStringAt(c));
}

void BoardModel::onDataChanged()
{
    beginResetModel();
    endResetModel();
}
