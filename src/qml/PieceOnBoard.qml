import QtQuick
import qShogi

Rectangle {
    id: root
    color: "transparent"

    property string pieceImagePath
    property alias myTurn: mouseArea.enabled

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: piece
        onReleased: {
            parent = (piece.Drag.target !== null) ? piece.Drag.target : root
            if (parent.dropIndex) {
                if (parent.dropIndex !== index) {
                    GameController.move(index, parent.dropIndex)
                }         
            }
            GameController.redraw()
        }
    }

    Item {
        id: piece
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        width: root.width
        height: root.height

        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: root.width / 2
        Drag.hotSpot.y: root.height / 2

        Image {
            anchors.fill: parent
            visible: pieceImagePath !== ""
            source: pieceImagePath
            fillMode: Image.PreserveAspectFit
        }

        states: State {
            when: mouseArea.drag.active
            ParentChange { target: piece; parent: mainWindow }  // parent = mainWindow to display moving piece on top of all others widgets
            AnchorChanges { target: piece; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
        }
    }
}
