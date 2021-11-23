import QtQuick

import qShogi


Item {
    id: root

    property int cellSize
    property string pieceName
    property string pieceColor
    property string pieceImagePath
    property string turn
    property Item rootParent    // used to display moving piece on top of gamearea and all others pieces

    width: cellSize
    height: cellSize

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        enabled: pieceName !== "" && pieceColor == turn

        drag.target: piece

        onReleased: {
            parent = (piece.Drag.target !== null) ? piece.Drag.target : root
            if (parent.dropIndex) {
                if (parent.dropIndex === index) {
                    return
                }
                GameController.move(index, parent.dropIndex)
            }
        }
    }

    Item {
        id: piece

        width: root.width
        height: root.height

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: root.width / 2
        Drag.hotSpot.y: root.height / 2

        Image {
            anchors.fill: parent
            visible: pieceImagePath !== ""
            source: pieceImagePath
        }

        states: State {
            when: mouseArea.drag.active
            ParentChange { target: piece; parent: rootParent }
            AnchorChanges { target: piece; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
        }
    }
}


