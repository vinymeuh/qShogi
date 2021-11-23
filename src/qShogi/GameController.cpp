/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "GameController.h"

#include <QQuickItem>
#include <QQuickView>
#include <QQmlComponent>


GameController::GameController(QQmlApplicationEngine* engine, QObject* parent)
    : m_engine{engine}, QObject{parent}, m_board_model(m_board), m_gamelog_model(m_board),
      m_northhand_model{NorthHandModel(m_board, shogi::White)},
      m_southhand_model{SouthHandModel(m_board, shogi::Black)}
{   
    m_board.set_start_position();

    qmlRegisterSingletonInstance("qShogi", 1, 0, "BoardModel", &m_board_model);
    qmlRegisterSingletonInstance("qShogi", 1, 0, "GameLogModel", &m_gamelog_model);
    qmlRegisterSingletonInstance("qShogi", 1, 0, "NorthHandModel", &m_northhand_model);
    qmlRegisterSingletonInstance("qShogi", 1, 0, "SouthHandModel", &m_southhand_model);

    // GameController signals to C++ models slots
    QObject::connect(this, SIGNAL(nextMove()), &m_board_model, SLOT(onDataChanged()));
    QObject::connect(this, SIGNAL(nextMove()), &m_gamelog_model, SLOT(onDataChanged()));
    QObject::connect(this, SIGNAL(nextMove()), &m_northhand_model, SLOT(onDataChanged()));
    QObject::connect(this, SIGNAL(nextMove()), &m_southhand_model, SLOT(onDataChanged()));
}


void GameController::newGame(int sfenChoice, QString sfenStr)
{
    std::string previous_sfen = m_board.sfen();

    switch(sfenChoice) {
    case -2:
        m_board.set_start_position(previous_sfen);
        break;
    case -1:
        try {
            m_board.set_start_position(sfenStr.toStdString());
        }
        catch (const std::invalid_argument& e) {
            qDebug() << e.what();   // TODO: display error message
            m_board.set_start_position(previous_sfen);
        }
        break;
    case 0: m_board.set_start_position(shogi::sfen_even); break;
    case 1: m_board.set_start_position(shogi::sfen_handicap_lance); break;
    case 2: m_board.set_start_position(shogi::sfen_handicap_bishop); break;
    case 3: m_board.set_start_position(shogi::sfen_handicap_rook); break;
    case 4: m_board.set_start_position(shogi::sfen_handicap_rook_lance); break;
    case 5: m_board.set_start_position(shogi::sfen_handicap_2pieces); break;
    case 6: m_board.set_start_position(shogi::sfen_handicap_4pieces); break;
    case 7: m_board.set_start_position(shogi::sfen_handicap_6pieces); break;
    case 8: m_board.set_start_position(shogi::sfen_handicap_8pieces); break;
    case 9: m_board.set_start_position(shogi::sfen_handicap_10pieces); break;
    }

    emit nextMove();
}


QString GameController::pieceImageFilePath(int index) const
{
    if (index < 0 || index >= 9*9)
        return "";
    auto cell = static_cast<shogi::Cell>(index);
    auto piece = m_board.cell(cell);
    if (piece.has_value()) {
        Orientation orientation;
        if (pieceColor(*piece) == shogi::Black) orientation = South;
        else orientation = North;
        return pieceImageFilePath(pieceType(*piece), orientation);
    }
    return "";
}


QString GameController::pieceImageFilePath(shogi::PieceType piece_type, Orientation orientation) const
{
    QString piece_type_str;
    switch (piece_type) {
    case shogi::Pawn: piece_type_str = "pawn"; break;
    case shogi::Lance: piece_type_str = "lance"; break;
    case shogi::Knight: piece_type_str = "knight"; break;
    case shogi::Silver: piece_type_str = "silver"; break;
    case shogi::Gold: piece_type_str = "gold"; break;
    case shogi::Bishop: piece_type_str = "bishop"; break;
    case shogi::Rook: piece_type_str = "rook"; break;
    case shogi::King: piece_type_str = "king"; break;
    case shogi::PromotedPawn: piece_type_str = "pawnP"; break;
    case shogi::PromotedLance: piece_type_str = "lanceP"; break;
    case shogi::PromotedKnight: piece_type_str = "knightP"; break;
    case shogi::PromotedSilver: piece_type_str = "silverP"; break;
    case shogi::PromotedBishop: piece_type_str = "bishopP"; break;
    case shogi::PromotedRook: piece_type_str = "rookP"; break;
    }

    QString orientation_str;
    if (orientation == South) orientation_str = "south";
    else orientation_str = "north";

    return "/pieces/kanji_light/" + orientation_str + "/" + piece_type_str +".svg";
}


QString GameController::cellAtIndex(int index) const
{
    if (index < 0 || index >= 9*9)
        return "";
    auto c = static_cast<shogi::Cell>(index);
    return QString::fromStdString(m_board.pieceStringAt(c));
}


QString GameController::cellColorAtIndex(int index) const
{
    if (index < 0 || index >= 9*9)
        return "";
    auto cell = static_cast<shogi::Cell>(index);
    auto piece = m_board.cell(cell);
    if (piece.has_value()) {
        if (pieceColor(*piece) == shogi::Black) {
            return "black";
        }
        else {
            return "white";
        }
    }
    return "";
}


void GameController::move(int from, int to)
{
    auto cfrom = static_cast<shogi::Cell>(from);
    auto cto = static_cast<shogi::Cell>(to);

    bool can_promote = m_board.canPromote(cfrom, cto);
    bool must_promote = m_board.mustPromote(cfrom, cto);

    if (can_promote == true && must_promote == false) {
        openPromotionDialog(from, to);
    }
    else {
        m_board.shiftPiece(cfrom, cto, must_promote);
        //qDebug() << QString::fromStdString(m_board.SFEN()); FIXME
        emit nextMove();
    }

    return;
}


void GameController::moveAfterPromotionDecision(int from, int to, bool promotion)
{
    auto cfrom = static_cast<shogi::Cell>(from);
    auto cto = static_cast<shogi::Cell>(to);
    m_board.shiftPiece(cfrom, cto, promotion);
    emit nextMove();
}


void GameController::drop(shogi::PieceType piece_type, shogi::Color color, int to)
{
    shogi::Piece piece = shogi::piece(piece_type, color);
    auto cto = static_cast<shogi::Cell>(to);
    m_board.dropPiece(piece, cto);
    emit nextMove();
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
    case shogi::Black: return "black";
    case shogi::White: return "white";
    default: return "";
    }
}


void GameController::onNewGame(const QString &sfen) {
    qDebug() << "Called the C++ slot with message:" << sfen;
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
