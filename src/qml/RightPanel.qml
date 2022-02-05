import QtQuick
import QtQuick.Controls
import qShogi

Item {
    id: root

    property int cellHeight
    property int cellWidth

    Column {
        anchors {
            left: parent.left
            top: parent.top
        }
        height: parent.height
        width: 7*root.cellWidth + spacing

        spacing: 10

        Hand {
            id: northhand
            color: "#bcbcbc"    // TODO: global boardColor
            width: parent.width

            cellHeight: root.cellHeight
            cellWidth: root.cellWidth
            model: NorthHandModel
            orientation: GameController.North
        }

        Rectangle {
            id: gamemoves
            border.color: "black"
            border.width: 1
            height: parent.height - 2*root.cellHeight - 2*parent.spacing
            width: parent.width

            ScrollView {
                anchors.fill: parent
                ScrollBar.vertical.policy: ScrollBar.AsNeeded
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView {
                    id: gamemovesListView
                    anchors.fill: parent
                    anchors.margins: 10
                    clip: true

                    model: GameLogModel
                    delegate: Component {
                        Rectangle {
                            width: gamemovesListView.width
                            height: 20
                            color: ListView.isCurrentItem ? "lightskyblue" : "white"
                            Text {
                                text: move
                                font.pixelSize: 12
                                font.family: "Consolas";
                            }
                        }
                    }

                    onCountChanged: {
                        gamemovesListView.currentIndex = gamemovesListView.count - 1
                        positionViewAtEnd()
                    }
                }
            }
        }

        Hand {
            id: southhand
            color: "#bcbcbc"    // TODO: global boardColor
            width: parent.width

            cellHeight: root.cellHeight
            cellWidth: root.cellWidth
            model: SouthHandModel
            orientation: GameController.South
        }
    }
}
