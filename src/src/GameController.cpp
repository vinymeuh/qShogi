/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "GameController.h"

#include <QQuickItem>
#include <QQuickView>
#include <QQmlComponent>


GameController::GameController(QQmlApplicationEngine* engine, QObject* parent)
    : m_engine{engine}, QObject{parent}, m_board_model(m_board), m_gamemoves_model(m_board),
      m_northhand_model{HandModel(m_board, shogi::Color::white)},
      m_southhand_model{HandModel(m_board, shogi::Color::black)},
      m_edit_mode{false}
{   
    m_board.setSFEN(shogi::sfen::shogi_even);

    qmlRegisterSingletonInstance("qShogi", 1, 0, "BoardModel", &m_board_model);
    qmlRegisterSingletonInstance("qShogi", 1, 0, "GameLogModel", &m_gamemoves_model);
    qmlRegisterSingletonInstance("qShogi", 1, 0, "NorthHandModel", &m_northhand_model);
    qmlRegisterSingletonInstance("qShogi", 1, 0, "SouthHandModel", &m_southhand_model);

    // GameController signals to C++ models slots
    QObject::connect(this, SIGNAL(redraw()), &m_board_model, SLOT(onDataChanged()));
    QObject::connect(this, SIGNAL(redraw()), &m_gamemoves_model, SLOT(onDataChanged()));
    QObject::connect(this, SIGNAL(redraw()), &m_northhand_model, SLOT(onDataChanged()));
    QObject::connect(this, SIGNAL(redraw()), &m_southhand_model, SLOT(onDataChanged()));
}


void GameController::newGame(int sfenChoice, QString sfenStr)
{
    std::string previous_sfen = m_board.SFEN();

    switch(sfenChoice) {
    case -2:
        m_board.setSFEN(previous_sfen);
        break;
    case -1:
        try {
            m_board.setSFEN(sfenStr.toStdString());
        }
        catch (const std::invalid_argument& e) {
            qDebug() << e.what();   // TODO: display error message
            m_board.setSFEN(previous_sfen);
        }
        break;
    case 0: m_board.setSFEN(shogi::sfen::shogi_even); break;
    case 1: m_board.setSFEN(shogi::sfen::shogi_handicap_lance); break;
    case 2: m_board.setSFEN(shogi::sfen::shogi_handicap_bishop); break;
    case 3: m_board.setSFEN(shogi::sfen::shogi_handicap_rook); break;
    case 4: m_board.setSFEN(shogi::sfen::shogi_handicap_rook_lance); break;
    case 5: m_board.setSFEN(shogi::sfen::shogi_handicap_2pieces); break;
    case 6: m_board.setSFEN(shogi::sfen::shogi_handicap_4pieces); break;
    case 7: m_board.setSFEN(shogi::sfen::shogi_handicap_6pieces); break;
    case 8: m_board.setSFEN(shogi::sfen::shogi_handicap_8pieces); break;
    case 9: m_board.setSFEN(shogi::sfen::shogi_handicap_10pieces); break;
    }

    emit redraw();
}


QString GameController::pieceImageFilePath(int index) const
{
    if (index < 0 || index >= m_board.squares()) {
        return "";
    }

    auto piece = m_board[index].piece;
    switch(piece.color) {
    case shogi::Color::black:
        return pieceImageFilePath(piece.type, piece.promoted, Orientation::South);
    case shogi::Color::white:
        return pieceImageFilePath(piece.type, piece.promoted, Orientation::North);
    default:
        return "";
    }
}


QString GameController::pieceImageFilePath(shogi::Type piece_type, bool promoted, Orientation orientation) const
{
    QString piece_type_str;
    if (promoted == false) {
        switch (piece_type) {
        case shogi::Type::pawn: piece_type_str = "pawn"; break;
        case shogi::Type::lance: piece_type_str = "lance"; break;
        case shogi::Type::knight: piece_type_str = "knight"; break;
        case shogi::Type::silver: piece_type_str = "silver"; break;
        case shogi::Type::gold: piece_type_str = "gold"; break;
        case shogi::Type::bishop: piece_type_str = "bishop"; break;
        case shogi::Type::rook: piece_type_str = "rook"; break;
        case shogi::Type::king: piece_type_str = "king"; break;
        }
    }
    else {
        switch (piece_type) {
        case shogi::Type::pawn: piece_type_str = "pawnP"; break;
        case shogi::Type::lance: piece_type_str = "lanceP"; break;
        case shogi::Type::knight: piece_type_str = "knightP"; break;
        case shogi::Type::silver: piece_type_str = "silverP"; break;
        case shogi::Type::bishop: piece_type_str = "bishopP"; break;
        case shogi::Type::rook: piece_type_str = "rookP"; break;
        }
    }

    QString orientation_str;
    if (orientation == South) orientation_str = "south";
    else orientation_str = "north";

    return "/assets/pieces/kanji_light/" + orientation_str + "/" + piece_type_str +".svg";
}


QString GameController::cellAtIndex(int index) const
{
    if (index < 0 || index >= m_board.squares()) {
        return "";
    }
    return QString::fromStdString( m_board[index].piece.toString() );
}


QString GameController::cellColorAtIndex(int index) const
{
    if (index < 0 || index >= m_board.squares()) {
        return "";
    }

    switch(m_board[index].piece.color) {
    case shogi::Color::black: return "black";
    case shogi::Color::white: return "white";
    default: return "";
    }
}


void GameController::move(int from, int to)
{
    bool can_promote = m_board.moveCanPromote(from, to);
    bool must_promote = m_board.moveMustPromote(from, to);

    if (can_promote == true && must_promote == false) {
        openPromotionDialog(from, to);
    }
    else {
        m_board.move(from, to, must_promote);
    }
}


void GameController::moveAfterPromotionDecision(int from, int to, bool promotion)
{
    m_board.move(from, to, promotion);
    emit redraw();  // display bug without it
}


void GameController::drop(shogi::Color color, shogi::Type piece_type, int to)
{
    m_board.drop(color, piece_type, to);
}


shogi::Color GameController::northHandColor() const
{
    return m_northhand_model.color();
}


shogi::Color GameController::southHandColor() const
{
    return m_southhand_model.color();
}


bool GameController::isNorthHandTurn() const
{
    return m_board.sideToMove() == m_northhand_model.color();
}


bool GameController::isSouthHandTurn() const
{
    return m_board.sideToMove() == m_southhand_model.color();
}


QString GameController::turn() const
{
    switch (m_board.sideToMove()) {
    case shogi::Color::black: return "black";
    case shogi::Color::white: return "white";
    default: return "";
    }
}


void GameController::toggleEditMode()
{
    if (m_edit_mode) {
        m_edit_mode = false;
    }
    else {
        m_edit_mode = true;
    }
    emit editModeChanged();

    // start new game from current position
    std::string sfen = m_board.SFEN();
    m_board.setSFEN(sfen);
    emit redraw();
}


void GameController::switchSideToMove()
{
    //m_board.switchSideToMove();
    emit redraw();
}


void GameController::setMoveFormat(shogi::Notation format)
{
    m_gamemoves_model.moveFormat(format);
    emit redraw();
}


void GameController::openPromotionDialog(int from, int to)
{
    QQuickWindow* rootItem = qobject_cast<QQuickWindow*>(m_engine->rootObjects().value(0));
    qDebug() << "GameController::openPromotionDialog: " << rootItem;
    QQmlComponent component(m_engine, QUrl("qrc:/qml/PromoteDialog.qml"));
    if (component.isError()) qDebug() << "component has errors:" << component.errorString();
    else
    {
        QQuickItem* childItem = qobject_cast<QQuickItem*>(component.create());
        if (childItem)
        {
            childItem->setProperty("from", from);
            childItem->setProperty("to", to);
            childItem->setParentItem(rootItem->contentItem());
        }
        else qDebug() << "childItem is null :(";
    }
}
