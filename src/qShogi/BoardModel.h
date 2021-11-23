/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlApplicationEngine>
#include "../shogi/shogi.h"

class BoardModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit BoardModel(shogi::Board& board, QObject* parent=nullptr);

    int rowCount(const QModelIndex& parent=QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;

public slots:
    void onDataChanged();

private:
    shogi::Board& m_board;
};

#endif // BOARDMODEL_H
