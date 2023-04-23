import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root
    property string duration : "end"
    property alias position: slideProgress.value
    property alias to : slideProgress.to
    property string startText
    signal changePosition(int pos)
    height: 20

    Slider{
        id: slideProgress
        anchors{
            verticalCenter: root.verticalCenter
            left: txtStart.right
            right: txtEnd.left
            margins: 5
        }
        from: 0
        live: true
        onMoved: {
                changePosition(valueAt(slideProgress.position));
        }

    }

    Text {
        id: txtStart
        font.pixelSize: 15
        text: startText
        anchors{
            top: root.top
            left: root.left
        }
    }

    Text {
        id: txtEnd
        text: duration
        font.pixelSize: 15
        anchors{
            top: root.top
            right: root.right
        }
    }
}
