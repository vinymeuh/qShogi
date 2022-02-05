import QtQuick
import qShogi

Item {
    id: root

    property int pieceType
    property int pieceColor
    property int pieceOrientation
    property int pieceCount: 0
    property int cellHeight
    property int cellWidth

    property alias myTurn: mouseArea.enabled

    height: root.cellHeight
    width: root.cellWidth

    Rectangle {
        height: root.height
        width: root.height
        color: "transparent"

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
                fillMode: Image.PreserveAspectFit
                opacity: (root.pieceCount > 0) ? 1.0 : 0.1
            }
            states: State {
                when: mouseArea.drag.active
                ParentChange { target: piece; parent: mainWindow }  // parent = mainWindow to display moving piece on top of all others widgets
                AnchorChanges { target: piece; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }
        }

        Rectangle {
            visible: root.pieceCount > 0
            anchors {
                bottom: piece.bottom
                right: piece.right
            }
            width: countText.contentWidth*2
            height: countText.contentHeight
            color: "red"
            radius: 4
            Text {
                id: countText
                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    family: "Helvetica"
                    bold: true
                    pointSize: 12
                }
                color: "white"
                text: model.piececount
            }
        }
    }
}
