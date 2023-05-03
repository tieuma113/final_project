import QtQuick 2.9
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import QtMultimedia 5.12
import AppEnums 1.0
import QtQml 2.12
import "../components"

Item {
    id: root
    property bool fullScreen: false
    StatusBar {
        visible: !MVIDEO_MODEL.fullScreen
        id: statusbar
        btnSrcList: ["qrc:/images/btn_back.png",
            "qrc:/images/btn_home.png",
            "qrc:/images/btn_full.png"]
        anchors {
            top: parent.top
            left: parent.left
        }
        width: parent.width

        onClickedBtn: {
            switch(idx){
            case 0:
                DBUS_CTRL.backHome();
                break;
            case 1:
                DBUS_CTRL.backHome();
                break;
            case 2:
                MVIDEO_CTRL.fullScreen(true);
                break;
            default:
                break;
            }
        }
    }

    VideoOutput{
        id: vd_output
        anchors{
            top: MVIDEO_MODEL.fullScreen ? root.top : statusbar.bottom
            left: root.left
        }
        width: root.width
        height: MVIDEO_MODEL.fullScreen ? root.height : root.height - statusbar.height
        source: MVIDEO_MODEL
        visible: true
    }

    Text {
        visible: !fullScreen
        id: txtFileName
        text: MVIDEO_MODEL.fileName === "" ? "fileName" : MVIDEO_MODEL.fileName
        anchors{
            top: md_controller.bottom
            left: root.left
            leftMargin: root.width / 20
            topMargin: 10
        }
        width: root.width - root.width / 10
        font.pixelSize: 25
    }

    MediaControllerBar{
        id :md_controller
        visible: !fullScreen
        z: MVIDEO_MODEL.fullScreen ? 0 : 1
        isPlay: MVIDEO_MODEL.player.state === MediaPlayer.PlayingState
        anchors.horizontalCenter:  root.horizontalCenter
        anchors.bottom: root.bottom
        anchors.bottomMargin: root.height * 2 /10

        onClickedBtn: {
            switch(idx){
            case 1:
                MVIDEO_MODEL.playList.previous();
                break;
            case 2:
                !isPlay ? MVIDEO_MODEL.player.pause() : MVIDEO_MODEL.player.play();
                break;
            case 3:
                MVIDEO_MODEL.plaList.next();
                break;
            default:
                break;
            }
        }
    }


    Timer{
       id: timerFullScreen
       interval: 5000
       repeat: true
       onTriggered: {
           fullScreen = true
       }
    }

    MouseArea{
        anchors{
            top: statusbar.bottom
            left: root.left
        }
        width: root.width
        height: root.height - statusbar.height

        onClicked: {
            timerFullScreen.restart();
            if (fullScreen){
                fullScreen = false;
            }
        }
    }

    MediaSlider{
        visible: !fullScreen
        duration: MVIDEO_MODEL.duration
        position: MVIDEO_MODEL.position
        id: md_slider
        anchors{
            bottom: parent.bottom
            bottomMargin: 30
            horizontalCenter: root.horizontalCenter
        }
        width: root.width - root.width * 1 / 10
        onChangePosition: {
            console.debug(pos);
            MVIDEO_MODEL.player.setPosition(pos);
        }
    }

    Component.onCompleted: {
        timerFullScreen.start()
    }

}
