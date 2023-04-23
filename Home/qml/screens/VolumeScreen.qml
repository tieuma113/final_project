import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root
    Item {
        anchors.centerIn: root
        Image{
            id: minus
            source: "qrc:/images/minus.png"
            anchors{
                right: volumeSlider.left
                rightMargin: 5
                verticalCenter: parent.verticalCenter
            }
            width: volumeSlider.height
            height: volumeSlider.height
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    TRANSLATOR_CTRL.volume--;
                }
            }
        }

        Slider{
            id: volumeSlider
            anchors.centerIn: parent
            width: root.width * 1/2
            height: 50
            from: 0
            to: 10
            value: TRANSLATOR_CTRL.volume
            stepSize: 1
            onMoved: {
                TRANSLATOR_CTRL.volume = valueAt(position);
            }
        }

        Image{
            id: plus
            source: "qrc:/images/add.png"
            anchors{
                left: volumeSlider.right
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }
            width: volumeSlider.height
            height: volumeSlider.height
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    TRANSLATOR_CTRL.volume++;
                }
            }
        }

    }


}
