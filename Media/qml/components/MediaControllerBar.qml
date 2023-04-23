import QtQuick 2.0
Rectangle{
    id: root
    color: "transparent"
    width:  240
    height: 80
    signal clickedBtn(int idx)
    property bool isPlay
    Row {
        id:btn_list
        anchors.fill: root
        BaseButton{
            height: root.height
            width: root.height
            id: btnPrev
            btnIconSrc: "qrc:/images/icon_prev.png"
            onBtnClicked: {
                clickedBtn(1);
            }
        }

        BaseButton{
            height: root.height
            width: root.height
            id: btnPlay
            btnIconSrc: isPlay ? "qrc:/images/icon_pause.png" : "qrc:/images/icon_play.png"
            onBtnClicked: {
                isPlay = !isPlay;
                clickedBtn(2);
            }
        }

        BaseButton{
            height: root.height
            width: root.height
            id: btnNext
            btnIconSrc: "qrc:/images/icon_next.png"
            onBtnClicked: {
                clickedBtn(3);
            }
        }

    }
}
