import QtQuick 2.9
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import AppEnums 1.0
import "../components"

Item {
    id: root
    StatusBar {
        id: statusbar
        anchors {
            top: parent.top
            left: parent.left
        }
        width: parent.width
        btnSrcList: []
    }
    // home content
    // TODO
    SwipeView{
        id: svContent
        currentIndex: 0
        anchors{
            top: statusbar.bottom
            right: root.right
        }
        height: root.height - statusbar.height
        width: root.width

        Item{
            id: firstPage
            Row{
                anchors.margins: 30
                anchors.fill: parent
                spacing: 50
                Rectangle{
                    id: music
                    clip: true
                    width: firstPage.width * 4/9
                    height: firstPage.height * 4/5
                    color: "gray"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            DBUS_CTRL.openMode(AppEnums.APP_MUSIC)
                        }
                    }

                    Text {
                        id: txtMusic
                        text: qsTr("MUSIC_APP_TITLE") + TRANSLATOR_MODEL.emptyString
                        anchors{
                            horizontalCenter: music.horizontalCenter
                            top: music.top
                            topMargin: music.height / 10
                        }
                    }

                    Image {
                        id: imgMusic
                        source: DBUS_MODEL.cover
                        anchors{
                            top: txtMusic.bottom
                            topMargin: music.height / 10
                            horizontalCenter: music.horizontalCenter
                        }
                        width: music.height / 2
                        height: width
                    }

                    ScrollingText{
                        id: stxtSongTitle
                        text: DBUS_MODEL.title
                        size: 15
                        anchors{
                            top: imgMusic.bottom
                            topMargin: music.height / 15
                            horizontalCenter: music.horizontalCenter
                        }
                        width: imgMusic.width
                    }

                    ScrollingText{
                        id: stxtArtistName
                        text: DBUS_MODEL.artist
                        size: 15
                        anchors{
                            top: stxtSongTitle.bottom
                            topMargin: music.height /15
                            horizontalCenter: music.horizontalCenter
                        }
                        width: imgMusic.width
                    }
                }

                Rectangle{
                    id: video
                    clip: true
                    width: firstPage.width * 4/9
                    height: firstPage.height * 4/5
                    color: "gray"
                    Text {
                        id: txtVideo
                        text: qsTr("VIDEO_APP_TITLE") + TRANSLATOR_MODEL.emptyString
                        anchors{
                            horizontalCenter: video.horizontalCenter
                            top: video.top
                            topMargin: video.height / 10
                        }
                    }

                    Image {
                        id: imgVideo
                        source: "qrc:/images/icon_video.png"
                        anchors{
                            top: txtVideo.bottom
                            topMargin: video.height / 10
                            horizontalCenter: video.horizontalCenter
                        }
                        width: video.height / 2
                        height: width
                    }

                    ScrollingText{
                        id: stxtItemname
                        text: DBUS_MODEL.videoName
                        size: 15
                        anchors{
                            top: imgVideo.bottom
                            topMargin: video.height / 15
                            horizontalCenter: video.horizontalCenter
                        }
                        width: imgVideo.width
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            DBUS_CTRL.openMode(AppEnums.APP_VIDEO)
                        }
                    }
                }

            }
        }

        Item{
            id: secondPage
            Rectangle{
                id: setting
                anchors{
                    top: secondPage.top
                    left: secondPage.left
                    margins: 30
                }

                clip: true
                width: secondPage.width * 4/9
                height: secondPage.height * 4/5
                color: "gray"
                Text {
                    id: txtSetting
                    text: qsTr("SETTING_APP_TITLE") + TRANSLATOR_MODEL.emptyString
                    anchors{
                        horizontalCenter: setting.horizontalCenter
                        top: setting.top
                        topMargin: setting.height / 10
                    }
                }

                Image {
                    id: imgSetting
                    source: "qrc:/images/icon_setup.png"
                    anchors{
                        top: txtSetting.bottom
                        topMargin: setting.height / 10
                        horizontalCenter: setting.horizontalCenter
                    }
                    width: setting.height / 2
                    height: width
                }

                MouseArea {
                    anchors.fill: setting
                    onClicked: {
                        SCREEN_CTRL.pushScreen(AppEnums.SCREEN_ID_HOME_SETUP)
                    }
                }
            }
        }
    }
    PageIndicator{
        id: indicator
        count: svContent.count
        currentIndex: svContent.currentIndex
        anchors.bottom: root.bottom
        anchors.horizontalCenter: root.horizontalCenter
        anchors.bottomMargin: root.height / 20
        delegate: Rectangle{
            height: 10
            width: 20
            color: index === indicator.currentIndex ? "cyan" : "white"
            border{
                color: "black"
                width: 1
            }
        }
    }

}
