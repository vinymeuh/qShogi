import QtQuick
import qShogi

Item {
    id: root

    //readonly property int cellWidth: 0.888*boardImage.paintedWidth/9
    //readonly property int cellHeight: 0.919*boardImage.paintedHeight/9
    readonly property int cellWidth: 0.891*boardImage.paintedWidth/9
    readonly property int cellHeight: 0.925*boardImage.paintedHeight/9
    readonly property int boardInnerMargin: 10
    readonly property int boardOuterMargin: 20
    readonly property real handSizeRatio: 0.8

    readonly property string backgroundColor: "#ffffff"
    readonly property string boardColor: "#bcbcbc"

    width: height + 2*(root.boardInnerMargin+root.boardOuterMargin)

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
        radius: 5

        Image {
            id: boardImage
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/assets/board/grid.svg"
            fillMode: Image.PreserveAspectFit
            height: parent.height

            Grid {
                id: boardGrid
                rows: 9
                columns: 9
                anchors {
                    horizontalCenter: boardImage.horizontalCenter
                    verticalCenter: boardImage.verticalCenter
                }

                Repeater {
                    id: boardRepeater
                    model: BoardModel
                    DropArea {
                        id: dropArea
                        width: root.cellWidth
                        height: root.cellHeight
                        property int dropIndex: index   // used to keep index of entered cell, see PieceOnBoard
                        Rectangle {
                            id: cell
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                verticalCenter: parent.verticalCenter
                            }
                            width: root.cellWidth*0.9
                            height: root.cellHeight*0.9
                            color: "transparent"
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
                rows: 9
                columns: 9
                anchors {
                    horizontalCenter: boardImage.horizontalCenter
                    verticalCenter: boardImage.verticalCenter
                }

                Repeater {
                    id: piecesRepeater
                    model: BoardModel
                    delegate: PieceOnBoard {
                        height: root.cellHeight
                        width: root.cellWidth
                        pieceImagePath: GameController.pieceImageFilePath(index)
                        myTurn: GameController.editMode || (GameController.cellAtIndex(index) !== "" && GameController.cellColorAtIndex(index) === GameController.turn)
                    }
                }
            }
        }
    }
}
