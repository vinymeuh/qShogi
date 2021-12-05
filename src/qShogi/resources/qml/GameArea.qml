import QtQuick
import qShogi

Item {
    id: gamearea

    readonly property int cellSize: (height-2*(gamearea.boardInnerMargin+gamearea.boardOuterMargin))/9
    readonly property int boardInnerMargin: 10
    readonly property int boardOuterMargin: 20
    readonly property real handSizeRatio: 0.8

    readonly property string backgroundColor: "#ffffff"
    readonly property string boardColor: "#bcbcbc"

    width: height + 2*(gamearea.boardInnerMargin+gamearea.boardOuterMargin) + 2*cellSize

    // North Hand Area
    Rectangle {
        id: northHandArea
        height: parent.height
        width: gamearea.cellSize
        anchors.left: parent.left
        color: gamearea.backgroundColor

        Column {
            id: northHandStack
            anchors {
                top: parent.top
                topMargin: gamearea.boardOuterMargin
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
            width: gamearea.cellSize
            anchors {
                top: northHandStack.bottom
                horizontalCenter: parent.horizontalCenter
            }
            TextInput {
                text: "☖"
                font.pointSize: 20
                rotation: 180
                width: gamearea.cellSize
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
        color: gamearea.backgroundColor

        Rectangle {
            id: board
            height: parent.height - 2*gamearea.boardOuterMargin
            width: height
            color: gamearea.boardColor
            anchors {
                margins: gamearea.boardOuterMargin
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }

            Grid {
                id: boardGrid
                rows: 9
                columns: 9
                anchors {
                    margins: gamearea.boardInnerMargin
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                Repeater {
                    id: boardRepeater
                    model: BoardModel

                    DropArea {
                        id: dropArea

                        property int dropIndex: index   // used to keep index of entered cell, see PieceOnBoard

                        width: gamearea.cellSize
                        height: width

                        Rectangle {
                            id: cell
                            anchors.fill: parent
                            color: gamearea.boardColor
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
                    margins: gamearea.boardInnerMargin
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
        width: gamearea.cellSize
        anchors.left: boardArea.right
        color: gamearea.backgroundColor

        Column {
            id: southHandStack
            anchors {
                bottom: parent.bottom
                bottomMargin: gamearea.boardOuterMargin
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
            width: gamearea.cellSize
            anchors {
                bottom: southHandStack.top
                bottomMargin: 2*gamearea.boardOuterMargin
                horizontalCenter: parent.horizontalCenter
            }
            TextInput {
                text: "☗"
                font.pointSize: 20
                width: gamearea.cellSize
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                enabled: false
            }
        }
    }
}
