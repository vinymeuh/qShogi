import QtQuick
import QtQuick.Controls

import qShogi

Item {
    id: root

    property int from
    property int to

    Dialog {
        id: dialog
        width: 200
        height: 150

        modal: true
        visible: true

        title: "Promote ?"
        standardButtons: Dialog.Yes | Dialog.No
        closePolicy: Popup.NoAutoClose

        onAccepted: GameController.moveAfterPromotionDecision(from, to, true)
        onRejected: GameController.moveAfterPromotionDecision(from, to, false)
    }
}
