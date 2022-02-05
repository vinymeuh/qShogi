import QtQuick
import qShogi

Rectangle {
    id: root

    property int cellHeight
    property int cellWidth
    property int orientation

    property alias model: pieceRepeater.model

    height: root.cellHeight
    radius: 5

    function isMyTurn() {
        if (root.orientation === GameController.North)
            return GameController.isNorthHandTurn()
        else
            return GameController.isSouthHandTurn()
    }

    function myColor() {
        if (root.orientation === GameController.North)
            return GameController.northHandColor()
        else
            return GameController.southHandColor()
    }

    Row {
        id: pieces
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: 7*root.cellWidth
        Repeater {
            id: pieceRepeater
            delegate: PieceInHand {
                id: piece
                pieceType: model.piecetype
                pieceColor: myColor()
                pieceOrientation: root.orientation
                pieceCount: model.piececount
                myTurn: model.piececount > 0 && (GameController.editMode || isMyTurn())

                cellWidth: root.cellWidth
                cellHeight: root.cellHeight
            }
        }
    }
}
