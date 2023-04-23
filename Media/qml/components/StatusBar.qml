import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import AppEnums 1.0

Rectangle {
    id: root
    color: "black"
    height: 74

    property var btnSrcList: []

    signal clickedBtn(int idx)

    // btn list
    Row {
        id: btn_list
        anchors {
            left: parent.left
            leftMargin: 0
            top: parent.top
            topMargin: 0
        }
        height: parent.height
        Repeater {
            model: btnSrcList
            delegate: BaseButton {
                width: btn_list.height
                height: btn_list.height
                btnIconSrc: modelData
                onBtnClicked: {
                    clickedBtn(index)
                }
            }
        }


        // time area
        // TODO

    }
    Row{
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        spacing: 8

        Text {
            font.pixelSize: 20
            color: "white"
            id: txtHour
        }

        Text{
            font.pixelSize: 15
            color: "white"
            id: txtDate
        }

        Timer{
            running: true
            repeat: true
            interval: 1000
            onTriggered: {
                let currentDate = new Date();
                txtHour.text = Qt.formatDateTime(currentDate ,"H:mm AP");
                txtDate.text = Qt.formatDate(currentDate, "d.M");
            }
            triggeredOnStart: true;
        }
    }
}
