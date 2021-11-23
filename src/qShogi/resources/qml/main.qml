import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import qShogi

ApplicationWindow {
    id: root

    visible: true
    minimumHeight: Screen.height * 0.5
    minimumWidth: minimumHeight * 1.9
    height: minimumHeight
    width: minimumWidth

    // Menu bar
    menuBar: MenuBar {
        leftPadding: 10
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&Quit"); onTriggered: Qt.quit() }
        }
        Menu {
            title: qsTr("&Game")
            Action { text: qsTr("&Start New Game"); onTriggered: showNewGameDialog() }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About"); onTriggered: showAboutDialog() }
        }
    }

    // Game area
    GameArea {
        id: gamearea
        height: parent.height
    }

    // Moves log
    Rectangle {
        id: gamelog
        height: parent.height - 12
        width: parent.width - gamearea.width - 20
        border.color: "black"
        border.width: 1
        anchors {
            top: parent.top; topMargin: 10
            left: gamearea.right
        }

        ListView {
            id: gamelogListView
            anchors.fill: parent
            anchors.margins: 10
            clip: true

            model: GameLogModel
            delegate: Component {
                Item {
                    height: 20
                    Row {
                        spacing: 10
                        Text {
                            text: count
                            font.pixelSize: 14
                        }
                        Text {
                            text: usi
                            font.pixelSize: 14
                        }
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                parent: gamelog
                policy: ScrollBar.AlwaysOn
                anchors {
                    top: parent.top; topMargin: gamelog.topPadding
                    bottom: parent.bottom; bottomMargin: gamelog.bottomPadding
                    right: parent.right; rightMargin: 1
                }
            }
        }
    }

    // Status bar
    footer: ToolBar {
        Text {
            text: GameController.turn
        }
    }

    // Functions used for dialogs dynamic instantiation
    function showNewGameDialog() {
        var component = Qt.createComponent("NewGameDialog.qml")
        if(component.status === Component.Ready) {
            var dialog = component.createObject(root)
            dialog.open()
        } else {
            console.error(component.errorString())
        }
    }

    function showAboutDialog() {
        var component = Qt.createComponent("AboutDialog.qml")
        if(component.status === Component.Ready) {
            var dialog = component.createObject(root)
            dialog.open()
        } else {
            console.error(component.errorString())
        }
    }    
}
