import QtQuick
import qShogi

Item {
    id: root

    readonly property int cellSize: (height-2*(root.boardInnerMargin+root.boardOuterMargin))/9
    readonly property int boardInnerMargin: 10
    readonly property int boardOuterMargin: 20
    readonly property real handSizeRatio: 0.8

    readonly property string backgroundColor: "#ffffff"
    readonly property string boardColor: "#bcbcbc"

    width: height + 2*(root.boardInnerMargin+root.boardOuterMargin) + 2*cellSize

    // North Hand Area
    Rectangle {
        id: northHandArea
        height: parent.height
        width: root.cellSize
        anchors.left: parent.left
        color: root.backgroundColor

        Column {
            id: northHandStack
            anchors {
                top: parent.top
                topMargin: root.boardOuterMargin
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 3
            Repeater {
                model: NorthHandModel
                delegate: PieceInHand {
                    id: northPieceInHand
                    pieceType: model.piecetype
                    pieceColor: GameController.northHandColor()
                    pieceOrientation: GameController.North
                    pieceCount: model.piececount
                    myTurn: model.piececount > 0 && (GameController.editMode || GameController.isNorthHandTurn())
                }
            }
        }

        Rectangle {
            id: northColorIndicator
            width: root.cellSize
            anchors {
                top: northHandStack.bottom
                horizontalCenter: parent.horizontalCenter
            }
            TextInput {
                text: "☖"
                font.pointSize: 20
                rotation: 180
                width: root.cellSize
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                enabled: false
            }
        }
    }


    // Board Area
    Rectangle {
        id: boardArea
        height: parent.height
        width: height
        anchors.left: northHandArea.right
        color: root.backgroundColor

        Rectangle {
            id: board
            height: parent.height - 2*root.boardOuterMargin
            width: height
            color: root.boardColor
            anchors {
                margins: root.boardOuterMargin
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }

            Grid {
                id: boardGrid
                rows: 9
                columns: 9
                anchors {
                    margins: root.boardInnerMargin
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                Repeater {
                    id: boardRepeater
                    model: BoardModel

                    DropArea {
                        id: dropArea

                        property int dropIndex: index   // used to keep index of entered cell, see PieceOnBoard

                        width: root.cellSize
                        height: width

                        Rectangle {
                            id: cell
                            anchors.fill: parent
                            color: root.boardColor
                            border.color: "black"
                            border.width: 1
                            states: [
                                State {
                                    when: dropArea.containsDrag
                                    PropertyChanges {target: cell; color: "grey"}
                                }
                            ]
                        }
                    }
                }
            }


            // Pieces on shogiban
            Grid {
                id: piecesGrid

                anchors {
                    margins: root.boardInnerMargin
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                rows: 9
                columns: 9

                Repeater {
                    id: piecesRepeater
                    model: BoardModel
                    delegate: PieceOnBoard {
                        pieceImagePath: GameController.pieceImageFilePath(index)
                        myTurn: GameController.editMode || (GameController.cellAtIndex(index) !== "" && GameController.cellColorAtIndex(index) === GameController.turn)
                    }
                }
            }
        }
    }


    // South Hand Area
    Rectangle {
        id: southHandArea
        height: parent.height
        width: root.cellSize
        anchors.left: boardArea.right
        color: root.backgroundColor

        Column {
            id: southHandStack
            anchors {
                bottom: parent.bottom
                bottomMargin: root.boardOuterMargin
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 3
            Repeater {
                model: SouthHandModel
                delegate:  PieceInHand {
                    id: pieceInRightHand
                    pieceType: model.piecetype
                    pieceColor: GameController.southHandColor()
                    pieceOrientation: GameController.South
                    pieceCount: model.piececount
                    myTurn: model.piececount > 0 && (GameController.editMode || GameController.isSouthHandTurn())
                }
            }
        }

        Rectangle {
            id: southColorIndicator
            width: root.cellSize
            anchors {
                bottom: southHandStack.top
                bottomMargin: 2*root.boardOuterMargin
                horizontalCenter: parent.horizontalCenter
            }
            TextInput {
                text: "☗"
                font.pointSize: 20
                width: root.cellSize
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                enabled: false
            }
        }
    }
}
