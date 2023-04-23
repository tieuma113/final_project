import QtQuick 2.9

Item {
    id: root

    property alias btnBg: btn_bg
    property alias btnIconSrc: btn_icon.source

    signal btnClicked()

    Rectangle {
        id: btn_bg
        anchors.fill: parent
        opacity: ma.pressed ? 0.8 : 1.0
        color: "transparent"
    }

    Image {
        id: btn_icon
        anchors.centerIn: parent
        opacity: ma.pressed ? 0.8 : 1.0
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        onClicked: {
            btnClicked()
        }
    }
}
