import QtQuick 2.0
import QtQml 2.12

Item {
    id: root
    clip: true
    height: txt_origin.height

    // text content
    property alias text: txt_origin.text
    property alias size: txt_origin.font.pixelSize

    // scroll setting
    property bool isAllowScroll: true
    property bool isScrollable: txt_origin.truncated

    // scrolling status
    property bool isScrolling: isAllowScroll && isScrollable

    // ME/Arabic mode
    property bool isMERegion: false
    property bool isArabicUIMode: false

    // calculate scroll position
    property bool isArabicText: {
        if (txt_origin.text.length > 0) {
            return (txt_origin.text.charCodeAt(0) > 0x0600)
                    && (txt_origin.text.charCodeAt(0) < 0x06FF)
        } else {
            return false
        }
    }
    property int scrollX: {
        if (isArabicUIMode) {
            if (isArabicText) {
                if(txt_origin.horizontalAlignment === Text.AlignHCenter){
                    return (root.width - txt_scroll_1.contentWidth - (root.width - txt_origin.contentWidth)/2)
                } else {
                    return root.width - txt_scroll_1.contentWidth
                }
            } else {
                if(txt_origin.horizontalAlignment === Text.AlignHCenter) {
                    return (root.width - txt_origin.contentWidth)/2
                } else {
                    return (root.width - txt_origin.contentWidth)
                }
            }
        } else {
            if (isArabicText) {
                if(txt_origin.horizontalAlignment === Text.AlignHCenter) {
                    return (txt_origin.contentWidth - txt_scroll_1.contentWidth + (root.width - txt_origin.contentWidth)/2)
                } else {
                    return txt_origin.contentWidth - txt_scroll_1.contentWidth
                }
            } else {
                if(txt_origin.horizontalAlignment === Text.AlignHCenter) {
                    return (root.width - txt_origin.contentWidth)/2
                } else {
                    return 0
                }
            }
        }
    }
    property int scrollWidth: {
        return txt_scroll_1.contentWidth + 24
    }

    // signal declare
    signal textScrollComplete()

    function moveText() {
        if (isMERegion && isArabicText) {
            if (txt_scroll_2.x + 1 >= scrollX) {
                txt_scroll_1.x = scrollX + scrollWidth
                txt_scroll_2.x = scrollX
                textScrollComplete()
                textTimer.stop()
                resetTimer.stop()
                pauseTimer.restart()
            } else {
                txt_scroll_1.x += 1
                txt_scroll_2.x += 1
            }
        } else {
            if (txt_scroll_2.x - 1 <= scrollX) {
                txt_scroll_1.x = scrollX - scrollWidth
                txt_scroll_2.x = scrollX
                textScrollComplete()
                textTimer.stop()
                resetTimer.stop()
                pauseTimer.restart()
            } else {
                txt_scroll_1.x -= 1
                txt_scroll_2.x -= 1
            }
        }
    }

    // reset animation
    function resetAnimation() {
        if (resetTimer.running) {
            resetTimer.stop()
        }
        if (textTimer.running) {
            textTimer.stop()
        }
        if (pauseTimer.running) {
            pauseTimer.stop()
        }
        txt_scroll_1.x = scrollX
        if (isMERegion && isArabicText) {
            txt_scroll_2.x = scrollX - scrollWidth
        } else {
            txt_scroll_2.x = scrollX + scrollWidth
        }
        if (isScrolling) {
            resetTimer.restart()
        }
    }
    onIsScrollingChanged: {
        resetAnimation()
    }
    onScrollXChanged: {
        resetAnimation()
    }
    onScrollWidthChanged: {
        resetAnimation()
    }

    // origin text
    BaseText {
        id: txt_origin
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
        width: parent.width
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        visible: !isScrolling
    }

    // scrolling text
    BaseText {
        id: txt_scroll_1
        text: txt_origin.text
        textFormat: txt_origin.textFormat
        font {
            family: txt_origin.font.family
            pixelSize: txt_origin.font.pixelSize
        }
        color: txt_origin.color
        visible: isScrolling
        x: scrollX
    }
    BaseText {
        id: txt_scroll_2
        text: txt_origin.text
        textFormat: txt_origin.textFormat
        font {
            family: txt_origin.font.family
            pixelSize: txt_origin.font.pixelSize
        }
        color: txt_origin.color
        visible: isScrolling
        x: scrollX + scrollWidth
    }

    Timer {
        id: resetTimer
        interval: 1000
        onTriggered: textTimer.restart()
        running: false
        repeat: false
    }

    Timer {
        id: textTimer
        interval: 40
        onTriggered: moveText()
        running: false
        repeat: isScrolling
        triggeredOnStart: isScrolling
    }

    Timer {
        id: pauseTimer
        interval: 1500
        onTriggered: resetAnimation()
        running: false
        repeat: false
    }
}
