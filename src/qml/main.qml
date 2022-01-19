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
            title: qsTr("&Edit Position")
            Action {
                text: (!GameController.editMode) ? qsTr("&Start Edition") : qsTr("&Stop Edition");
                onTriggered: GameController.toggleEditMode()
            }
            MenuSeparator {}
            Menu {
                title: qsTr("Initial Position")
                enabled: GameController.editMode
                Action { text: qsTr("Even"); onTriggered: { GameController.newGame(0) } }
                Action { text: qsTr("Lance Handicap"); onTriggered: { GameController.newGame(1) } }
                Action { text: qsTr("Bishop Handicap"); onTriggered: { GameController.newGame(2) } }
                Action { text: qsTr("Rook Handicap"); onTriggered: { GameController.newGame(3) } }
                Action { text: qsTr("Rook and Lance Handicap"); onTriggered: { GameController.newGame(4) } }
                Action { text: qsTr("2 Pieces Handicap"); onTriggered: { GameController.newGame(5) } }
                Action { text: qsTr("4 Pieces Handicap"); onTriggered: { GameController.newGame(6) } }
                Action { text: qsTr("6 Pieces Handicap"); onTriggered: { GameController.newGame(7) } }
                Action { text: qsTr("8 Pieces Handicap"); onTriggered: { GameController.newGame(8) } }
                Action { text: qsTr("10 Pieces Handicap"); onTriggered: { GameController.newGame(9) } }
            }
            Action { text: qsTr("Change Turn"); enabled: GameController.editMode; onTriggered: { GameController.switchSideToMove() } }
        }
        /* useless now,  perhaps later if I implement to interface with UCI engines
        Menu {
            title: qsTr("&Game")
            Action { text: qsTr("&Start New Game"); onTriggered: openDialog("NewGameDialog.qml") }
        }
        */
        Menu {
            title: qsTr("&Game Record")
            Menu {
                title: qsTr("Move format")
                ActionGroup { id: moveFormatAG }
                Action {
                    text: qsTr("Debug");
                    checkable: true;
                    ActionGroup.group: moveFormatAG;
                    onTriggered: { GameController.setMoveFormat(0) }
                }
                Action {
                    text: qsTr("USI");
                    checkable: true;
                    checked: true;
                    ActionGroup.group: moveFormatAG;
                    onTriggered: { GameController.setMoveFormat(1) } }
                Action {
                    text: qsTr("Hodges");
                    checkable: true;
                    ActionGroup.group: moveFormatAG;
                    onTriggered: { GameController.setMoveFormat(2) } }
                Action {
                    text: qsTr("Hosking");
                    checkable: true;
                    ActionGroup.group: moveFormatAG;
                    onTriggered: { GameController.setMoveFormat(3) } }
            }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About"); onTriggered: openDialog("AboutDialog.qml") }
        }
    }

    // Game area
    GameArea {
        id: gamearea
        height: parent.height
    }

    // Game record area
    GameRecordArea {
        id: gamerecordarea
        height: parent.height - 20
        width: parent.width - gamearea.width - 20
        anchors {
            top: parent.top; topMargin: 10
            left: gamearea.right
        }
    }

    // Status bar
    footer: ToolBar {
        Text {
            text: (GameController.editMode) ? GameController.turn + " (Edit mode)" : GameController.turn
        }
    }

    // Function used for dialogs dynamic instantiation
    function openDialog(qmlfile) {
        var component = Qt.createComponent(qmlfile)
        if(component.status === Component.Ready) {
            var dialog = component.createObject(root)
            dialog.open()
        } else {
            console.error(component.errorString())
        }
    }

}
