import QtQuick
import QtQuick.Controls
//import QtQuick.Layouts

import qShogi

MenuBar {
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
                    text: qsTr("USI");
                    checkable: true;
                    checked: true;
                    ActionGroup.group: moveFormatAG;
                    onTriggered: { GameController.setMoveFormat(0) } }
                Action {
                    text: qsTr("Hodges");
                    checkable: true;
                    ActionGroup.group: moveFormatAG;
                    onTriggered: { GameController.setMoveFormat(1) } }
                Action {
                    text: qsTr("Hosking");
                    checkable: true;
                    ActionGroup.group: moveFormatAG;
                    onTriggered: { GameController.setMoveFormat(2) } }
            }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About"); onTriggered: openDialog("AboutDialog.qml") }
        }
    }
