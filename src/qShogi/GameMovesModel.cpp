/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "GameMovesModel.h"


GameMovesModel::GameMovesModel(shogi::Board& board, QObject* parent)
    : QAbstractListModel(parent), m_board(board), m_format(shogi::MoveFormat::USI)
{
}


int GameMovesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_board.moves().size();
}


QVariant GameMovesModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_board.moves().size())
        return QVariant();
    auto move = m_board.moves()[index.row()];

    if (role == Move) {
        switch(m_format) {
        case shogi::MoveFormat::Debug:
            return QString("%1   %2")
                    .arg(index.row()+1, 4)
                    .arg(QString::fromStdString(move->toString(shogi::MoveFormat::Debug)));
        case shogi::MoveFormat::USI:
            return QString("%1   %2")
                    .arg(index.row()+1, 4)
                    .arg(QString::fromStdString(move->toString(shogi::MoveFormat::USI)));
        case shogi::MoveFormat::Hodges:
            return QString("%1   %2")
                    .arg(index.row()+1, 4)
                    .arg(QString::fromStdString(move->toString(shogi::MoveFormat::Hodges)));
        case shogi::MoveFormat::Hosking:
            return QString("%1   %2")
                    .arg(index.row()+1, 4)
                    .arg(QString::fromStdString(move->toString(shogi::MoveFormat::Hosking)));
        }
    }

    return QVariant();
}


void GameMovesModel::moveFormat(shogi::MoveFormat format)
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
