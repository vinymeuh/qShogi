import QtQuick

import qShogi

Item {
    id: root

    property int pieceType
    property int pieceColor
    property int pieceOrientation
    property int pieceCount: 0
    property alias myTurn: mouseArea.enabled

    height: gamearea.handSizeRatio*gamearea.cellSize
    width: height

    Rectangle {
        height: root.height
        width: root.height

        MouseArea {
            id: mouseArea
            anchors.fill: parent

            drag.target: piece

            onReleased: {
                parent = (piece.Drag.target !== null) ? piece.Drag.target : root
                if (parent.dropIndex) {
                    GameController.drop(root.pieceType, root.pieceColor, parent.dropIndex)
                }
            }
        }

        Item {
            id: piece

            height: root.height
            width: height
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }

            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: root.width / 2
            Drag.hotSpot.y: root.height / 2

            Image {
                id: pieceImage
                anchors.fill: parent
                source: GameController.pieceImageFilePath(root.pieceType, root.pieceOrientation)
            }
            states: State {
                when: mouseArea.drag.active
                ParentChange { target: piece; parent: gamearea }
                AnchorChanges { target: piece; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }
        }

        Rectangle {
            anchors.verticalCenter: piece.bottom
            anchors.horizontalCenter: piece.horizontalCenter
            width: childrenRect.width
            height: childrenRect.height
            color: "white"
            radius: 10
            Text {
                text: model.piececount
            }
        }
    }
}
