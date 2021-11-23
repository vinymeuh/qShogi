/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include "NorthHandModel.h"


int NorthHandModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    std::array<unsigned short, 7> hand;
    if (m_color == shogi::Black) hand = m_board.blackHand();
    else hand = m_board.whiteHand();

    int count{0};
    if (hand[shogi::Board::Hand::Pawn] > 0) ++count;
    if (hand[shogi::Board::Hand::Lance] > 0) ++count;
    if (hand[shogi::Board::Hand::Knight] > 0) ++count;
    if (hand[shogi::Board::Hand::Silver] > 0) ++count;
    if (hand[shogi::Board::Hand::Gold] > 0) ++count;
    if (hand[shogi::Board::Hand::Bishop] > 0) ++count;
    if (hand[shogi::Board::Hand::Rook] > 0) ++count;
    return count;
}


QVariant NorthHandModel::data(const QModelIndex& index, int role) const
{
    int indexRow = index.row();
    if (indexRow < 0 || indexRow >= rowCount())
        return QVariant();

    std::array<unsigned short, 7> hand;
    if (m_color == shogi::Black) hand = m_board.blackHand();
    else hand = m_board.whiteHand();

    shogi::PieceType pt = shogi::Rook;
    int count{0};
    int current{-1};
    if (hand[shogi::Board::Hand::Pawn] > 0) {
        ++current;
        if (indexRow == current) {
            count = hand[shogi::Board::Hand::Pawn];
            pt = shogi::Pawn;
        }
    }
    if (hand[shogi::Board::Hand::Lance]> 0) {
        ++current;
        if (indexRow == current) {
            count = hand[shogi::Board::Hand::Lance];
            pt = shogi::Lance;
        }
    }
    if (hand[shogi::Board::Hand::Knight] > 0) {
        ++current;
        if (indexRow == current) {
            count = hand[shogi::Board::Hand::Knight];
            pt = shogi::Knight;
        }
    }
    if (hand[shogi::Board::Hand::Silver] > 0) {
        ++current;
        if (indexRow == current) {
            count = hand[shogi::Board::Hand::Silver];
            pt = shogi::Silver;
        }
    }
    if (hand[shogi::Board::Hand::Gold] > 0) {
        ++current;
        if (indexRow == current) {
            count = hand[shogi::Board::Hand::Gold];
            pt = shogi::Gold;
        }
    }
    if (hand[shogi::Board::Hand::Bishop] > 0) {
        ++current;
        if (indexRow == current) {
            count = hand[shogi::Board::Hand::Bishop];
            pt = shogi::Bishop;
        }
    }
    if (hand[shogi::Board::Hand::Rook] > 0) {
        ++current;
        if (indexRow == current) {
           count = hand[shogi::Board::Hand::Rook];
           pt = shogi::Rook;
        }
    }


    if (role == PieceCount) {
        return QVariant(count);
    }
    if (role == PieceType) {
        return QVariant(pt);
    }
    return QVariant();
}


void NorthHandModel::onDataChanged()
{
    beginResetModel();
    endResetModel();
}


QHash<int, QByteArray> NorthHandModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PieceCount] = "piececount";
    roles[PieceType] = "piecetype";
    return roles;
}
