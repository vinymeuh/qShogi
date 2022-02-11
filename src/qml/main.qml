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
        anchors.centerIn: parent
        height: parent.height
        width: leftpanel.width + rightpanel.width

        LeftPanel {
            id: leftpanel
            height: parent.height
        }

        RightPanel {
            id: rightpanel
            height: parent.height - 20
            width: 7*leftpanel.cellWidth
            anchors {
                top: parent.top; topMargin: 10
                left: leftpanel.right
            }
            cellHeight: leftpanel.cellHeight
            cellWidth: leftpanel.cellWidth
        }
    }

    footer: ToolBar {}

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
