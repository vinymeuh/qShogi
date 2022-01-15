/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "../shogi/shogi.h"
#include "BoardModel.h"
#include "GameMovesModel.h"
#include "NorthHandModel.h"
#include "SouthHandModel.h"


class GameController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString turn READ turn NOTIFY nextMove)
    Q_PROPERTY(bool editMode READ editMode NOTIFY editModeChanged)

public:
    enum Orientation { North, South };
    Q_ENUM(Orientation)

    explicit GameController(QQmlApplicationEngine* engine, QObject* parent=nullptr);

    Q_INVOKABLE void newGame(int sfenChoice, QString sfenStr="");

    // piece representation
    Q_INVOKABLE QString pieceImageFilePath(int index) const;
    Q_INVOKABLE QString pieceImageFilePath(shogi::PieceType piece_type, GameController::Orientation orientation) const;

    // piece retrieval
    Q_INVOKABLE QString cellAtIndex(int index) const;
    Q_INVOKABLE QString cellColorAtIndex(int index) const;

    // piece moves
    Q_INVOKABLE void move(int from, int to);
    Q_INVOKABLE void moveAfterPromotionDecision(int from, int to, bool promotion=false);
    Q_INVOKABLE void drop(shogi::PieceType piece_type, shogi::Color color, int to);

    // hands
    Q_INVOKABLE shogi::Color northHandColor() const;
    Q_INVOKABLE shogi::Color southHandColor() const;
    Q_INVOKABLE bool isNorthHandTurn() const;
    Q_INVOKABLE bool isSouthHandTurn() const;

    // turn to play
    QString turn() const;

    // edit mode
    bool editMode() const { return m_edit_mode; };
    Q_INVOKABLE void toggleEditMode();
    Q_INVOKABLE void switchSideToMove();

    // game record
    Q_INVOKABLE void setMoveFormat(shogi::MoveFormat format);

private:
    void openPromotionDialog(int from, int to);

signals:
    void nextMove();
    void editModeChanged();

private:
    shogi::Board m_board;
    BoardModel m_board_model;
    GameMovesModel m_gamemoves_model;
    NorthHandModel m_northhand_model;
    SouthHandModel m_southhand_model;
    QQmlApplicationEngine* m_engine;

    // settings
    bool m_edit_mode;
};

#endif // GAMECONTROLLER_H
