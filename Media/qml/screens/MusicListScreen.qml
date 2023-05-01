import QtQuick 2.9
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import AppEnums 1.0
import "../components"

Item {
    id: root
    StatusBar {
        id: statusbar
        btnSrcList: ["qrc:/images/btn_back.png",
            "qrc:/images/btn_home.png"]
        anchors {
            top: parent.top
            left: parent.left
        }
        width: parent.width

        onClickedBtn: {
            switch(idx){
            case 0:
                SCREEN_CTRL.popScreen();
                break;
            case 1:
                console.debug("HOME");
                DBUS_CTRL.backHome();
                break;
            default:
                break;
            }
        }
    }

    ListView{
        id: lvMusicList
        anchors{
            top: statusbar.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
            margins: 5
        }
        model: MPLAYER_MODEL.playList
        delegate: Item{
            width: root.width
            height: 60
            Rectangle{
                property bool selected: MPLAYER_MODEL.playList.getIndex() === index ? true : false
                anchors{
                    fill: parent
                }

                Image{
                    id: selectedImage
                    anchors{
                        top:parent.top
                        left: parent.left
                    }
                    source: "qrc:/images/icon_music.png"
                    height: 60
                    width: parent.selected ? height : 0
                }

                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: selectedImage.right
                    font.pixelSize: 20
                    color: parent.selected ? "red" : "black"
                    text: name
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if (!parent.selected){
                            MPLAYER_MODEL.playList.setIndex(index);
                        }
                        SCREEN_CTRL.popScreen();
                    }
                }
            }

            Rectangle{
                anchors{
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }
                color: "blue"
                height: 1
            }
        }
    }
}
