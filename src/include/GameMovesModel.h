/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef GAMEMOVESMODEL_H
#define GAMEMOVESMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "shogi.h"

class GameMovesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        Move = Qt::UserRole,
    };

    explicit GameMovesModel(shogi::Board& board, QObject* parent=nullptr);

    int rowCount(const QModelIndex& parent=QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;

    void moveFormat(shogi::MoveFormat format);

public slots:
    void onDataChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    shogi::Board& m_board;
    shogi::MoveFormat m_format;
};

#endif // GAMEMOVESMODEL_H
