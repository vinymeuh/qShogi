import QtQuick
import QtQuick.Controls

Dialog {
    id: root

    anchors.centerIn: parent
    modal: true
    closePolicy: Popup.CloseOnEscape
    width: 200
    height: 100

    title: qsTr("About")
    Label {
        anchors.fill: parent
        text: qsTr("qShogi version 0.0")
        horizontalAlignment: Text.AlignHCenter
        rightInset: 100
    }
    standardButtons: DialogButtonBox.Ok
}
