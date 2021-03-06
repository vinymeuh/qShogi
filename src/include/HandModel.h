/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef HANDMODEL_H
#define HANDMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "shogi.h"

class HandModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ModelRoles {
        PieceCount = Qt::UserRole,
        PieceType,
    };

    HandModel(const shogi::Board& board, shogi::Color color, QObject* parent=nullptr)
        : QAbstractListModel(parent), m_board{board}, m_color{color} {};

    int rowCount(const QModelIndex& parent=QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;

    shogi::Color color() const { return m_color; }

public slots:
    void onDataChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    const shogi::Board& m_board;
    shogi::Color m_color;
};

#endif // HANDMODEL_H
