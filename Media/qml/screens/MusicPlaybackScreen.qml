import QtQuick 2.9
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import QtQml 2.12
import AppEnums 1.0
import "../components"

Item {
    id: root
    StatusBar {
        id: statusbar
        btnSrcList: ["qrc:/images/btn_back.png",
            "qrc:/images/btn_home.png",
            "qrc:/images/btn_list.png"]
        anchors {
            top: parent.top
            left: parent.left
        }
        width: parent.width

        onClickedBtn: {
            switch(idx){
            case 0:
                console.debug("BACK");
                DBUS_CTRL.backHome();
                break;
            case 1:
                console.debug("HOME");
                DBUS_CTRL.backHome();
                break;
            case 2:
                SCREEN_CTRL.pushScreen(AppEnums.SCREEN_ID_MUSIC_LIST);
                break;
            default:
                break;
            }
        }
    }

    Rectangle{
        id: contentSong
        width: root.width - imgCoverArt.width - 100
        height: imgCoverArt.height*1/3
        anchors{
            left: root.left
            top: statusbar.bottom
            leftMargin: root.width / 20
            topMargin: root.height /6
        }

        ScrollingText{
            id: txtsongTitle
            anchors{
                left: contentSong.left
                top: contentSong.top
            }
            text: MPLAYER_MODEL.Title === "" ? (qsTr("MUSIC_TITLE") + SETTING_MODEL.emptyString) : MPLAYER_MODEL.Title
            size: 25
            width: parent.width
            isAllowScroll: false
            Component.onCompleted: {
                if(txtsongTitle.isScrollable){
                    txtsongTitle.isAllowScroll = true;
                }
            }

            onTextScrollComplete: {
                if (txtAlbumn.isScrollable){
                    txtsongTitle.isAllowScroll = false;
                    txtAlbumn.isAllowScroll  = true;
                }else if (txtArtist.isScrollable){
                    txtsongTitle.isAllowScroll = false
                    txtArtist.isAllowScroll = true
                }
            }
        }


        ScrollingText {
            id: txtAlbumn
            anchors{
                top: txtsongTitle.bottom
                left: contentSong.left
                topMargin: 10
            }
            text: MPLAYER_MODEL.Title === "" ? qsTr("MUSIC_ALBUM") + SETTING_MODEL.emptyString : MPLAYER_MODEL.Album
            size: 20
            width: contentSong.width
            isAllowScroll: txtsongTitle.isScrollable ===false ? true : false
            onTextScrollComplete: {
                if (txtArtist.isScrollable){
                    txtAlbumn.isAllowScroll = false;
                    txtArtist.isAllowScrool = true;
                }else if(txtsongTitle.isScrollable){
                    txtAlbumn.isAllowScroll = false;
                    txtsongTitle.isAllowScroll = true
                }
            }
        }

        ScrollingText {
            id: txtArtist
            anchors{
                top: txtAlbumn.bottom
                topMargin: 10
                left: contentSong.left
            }
            text: MPLAYER_MODEL.Artist === "" ? qsTr("MUSIC_ARTIST") + SETTING_MODEL.emptyString : MPLAYER_MODEL.Artist
            size: 20
            width: contentSong.width
            isAllowScroll: {
                if (txtsongTitle.isScrollable === false && txtAlbumn.isScrollable === false){
                    return true;
                }else {
                    return false;
                }
            }
            onTextScrollComplete: {
                if (txtsongTitle.isScrollable){
                    txtArtist.isAllowScroll = false;
                    txtsongTitle.isAllowScroll = true;
                } else if (txtAlbumn.isScrollable){
                    txtArtist.isAllowScroll = false;
                    txtAlbumn.isAllowScroll = true;
                }
            }
        }
    }

    Image{
        id: imgCoverArt
        anchors{
            top: statusbar.bottom
            right: root.right
            topMargin: root.height / 24
            rightMargin: root.height /24
        }
        width: 300
        height: 300
        source: MPLAYER_MODEL.coverImagePath
    }

    MediaControllerBar{
        id: controllButton
        isPlay: MPLAYER_MODEL.isPlay
        anchors{
            top: contentSong.bottom
            topMargin: root.height /10
            left: root.left
            leftMargin: root.width / 6
        }
        onClickedBtn: {
            console.debug(idx);
            switch(idx){
            case 1:
                MPLAYER_CTRL.prevSong();
                break;
            case 2:
                !isPlay ? MPLAYER_CTRL.pauseSong() : MPLAYER_CTRL.continueSong();
                break;
            case 3:
                MPLAYER_CTRL.nextSong();
            }
        }
    }

    MediaSlider{
        id: contrllSlider
        startText: MPLAYER_MODEL.valuePosition
        duration: MPLAYER_MODEL.Duration
        position: MPLAYER_MODEL.position
        to: MPLAYER_MODEL.msDuration
        anchors{
            top: controllButton.bottom
            topMargin: root.height /12
            left: root.left
            leftMargin: root.width / 24
            right: root.right
            rightMargin: root.width /24
        }
        onChangePosition: {
            console.debug(pos);
            MPLAYER_CTRL.changePosition(pos);
        }
    }
}
