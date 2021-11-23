/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef GAMELOGMODEL_H
#define GAMELOGMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "../shogi/shogi.h"

class GameLogModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ModelRoles {
        Count = Qt::UserRole,
        Internal,
        USI,
    };

    explicit GameLogModel(shogi::Board& board, QObject* parent=nullptr);

    int rowCount(const QModelIndex& parent=QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;

public slots:
    void onDataChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    shogi::Board& m_board;
};

#endif // GAMELOGMODEL_H
