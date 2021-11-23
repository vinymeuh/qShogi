import QtQuick
import QtQuick.Controls

import qShogi

Dialog {
    id: root

    anchors.centerIn: parent
    modal: true
    closePolicy: Popup.CloseOnEscape

    title: qsTr("New Game")

    Column {
        anchors.fill: parent

        GroupBox {
            id: spGroupBox
            title: qsTr("Starting Position")
            Column {
                Row {
                    CheckBox {
                        id: spPredefined
                        text: qsTr("Predefined")
                        autoExclusive : true    // used to disable double click
                        checked: true
                        onClicked: {
                            spPredefined.checked = true
                            spSFEN.checked = false
                            spCurrent.checked = false
                        }
                    }
                    ComboBox {
                        id: spPredefinedChoice
                        width: 180      // TODO: compute dynamically
                        model: [
                            qsTr("Even"),
                            qsTr("Lance Handicap"),
                            qsTr("Bishop Handicap"),
                            qsTr("Rook Handicap"),
                            qsTr("Rook and Lance Handicap"),
                            qsTr("2 Pieces Handicap"),
                            qsTr("4 Pieces Handicap"),
                            qsTr("6 Pieces Handicap"),
                            qsTr("8 Pieces Handicap"),
                            qsTr("10 Pieces Handicap"),
                        ]
                        enabled: spPredefined.checked
                    }
                }
                Row {
                    CheckBox {
                        id: spSFEN
                        text: qsTr("Custom SFEN string")
                        autoExclusive : true    // used to disable double click
                        onClicked: {
                            spPredefined.checked = false
                            spSFEN.checked = true
                            spCurrent.checked = false
                        }
                    }
                    TextField {
                        id: spSFENText  // TODO: validate sfen
                        width: 126  // TODO: compute dynamically
                        enabled: spSFEN.checked
                    }
                }
                CheckBox {
                    id: spCurrent
                    text: qsTr("Current Position")
                    autoExclusive : true    // used to disable double click
                    onClicked: {
                        spPredefined.checked = false
                        spSFEN.checked = false
                        spCurrent.checked = true
                    }
                }
            }
        }
    }

    standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

    onAccepted: {
        if (spPredefined.checked) {
            GameController.newGame(spPredefinedChoice.currentIndex);
        }
        else if (spSFEN.checked) {
            GameController.newGame(-1, spSFENText.text);
        }
        else if (spCurrent.checked) {
            GameController.newGame(-2);
        }
    }
}
