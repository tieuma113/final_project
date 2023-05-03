import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root
    property alias duration : slideProgress.to
    property alias position: slideProgress.value
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
            console.log("triggle")
            changePosition(valueAt(slideProgress.position));
        }

    }

    Text {
        id: txtStart
        font.pixelSize: 15
        text: position === 0 ? "00:00" : formatTime(position)
        anchors{
            top: root.top
            left: root.left
        }
    }

    Text {
        id: txtEnd
        text: duration === 0 ? "00:00" : formatTime(duration)
        font.pixelSize: 15
        anchors{
            top: root.top
            right: root.right
        }
    }

    function formatTime(ms) {
        var seconds = Math.floor(ms / 1000);
        var minutes = Math.floor(seconds / 60);
        var hours = Math.floor(minutes / 60);
        var secondsString = String(seconds % 60).padStart(2, "0");
        var minutesString = String(minutes % 60).padStart(2, "0");
        var hoursString = String(hours).padStart(2, "0");
        return hours > 0 ? hoursString + ":" + minutesString + ":" + secondsString
                         : minutesString + ":" + secondsString;
    }
}
