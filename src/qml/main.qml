import QtQuick
import QtQuick.Controls
import qShogi

ApplicationWindow {
    id: root

    visible: true
    minimumHeight: Screen.height * 0.5
    minimumWidth: minimumHeight * 1.9
    height: minimumHeight
    width: minimumWidth

    menuBar: AppMenuBar {}

    Item {
        id: mainWindow
        anchors.fill: parent

        LeftPanel {
            id: leftpanel
            height: parent.height
        }

        RightPanel {
            id: rightpanel
            height: parent.height - 20
            width: parent.width - leftpanel.width - 20
            anchors {
                top: parent.top; topMargin: 10
                left: leftpanel.right
            }
            cellHeight: leftpanel.cellHeight
            cellWidth: leftpanel.cellWidth
        }
    }

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
