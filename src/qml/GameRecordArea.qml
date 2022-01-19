import QtQuick
import QtQuick.Controls

import qShogi

Item {
    id: root

    Rectangle {
        id: gamemoves
        border.color: "black"
        border.width: 1
        anchors.fill: parent

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

                        // useless for the moment
//                        MouseArea {
//                            anchors.fill: parent
//                            onClicked: { gamemovesListView.currentIndex = index; }
//                        }
                    }
                }

                onCountChanged: {
                    console.log(gamemovesListView.count)
                    gamemovesListView.currentIndex = gamemovesListView.count - 1
                    positionViewAtEnd()
                }
            }
        }
    }
}
