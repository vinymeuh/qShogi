import QtQuick
import qShogi

Rectangle {
    id: root

    property bool isMyTurn
    property alias text: playertext.text

    height: playertext.contentHeight
    border {
        color: (GameController.editMode == false) ? "lawngreen" : "red"
        width: ( root.isMyTurn ) ? 4 : 0
    }
    Text {
        id: playertext
        font {
            family: "Helvetica"
            pointSize: 20
        }
        leftPadding: 10
    }
}
