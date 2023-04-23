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
        btnSrcList: [
            "qrc:/images/btn_back.png",
            "qrc:/images/btn_home.png"
        ]

        onClickedBtn: {
            switch (idx){
            case 0 :
                SCREEN_CTRL.popScreen();
                break;
            case 1:
                SCREEN_CTRL.popToRoot();
                break;
            }
        }
    }
    // setup content
    // TODO
    Rectangle{
        id: rectSelectSetting
        color: "lightblue"
        width: root.width / 4
        height: root.height - statusbar.height
        anchors{
            top: statusbar.bottom
            left: root.left
        }
        property var selectSrcChoice: [qsTr("LANGUAGE_SETTING") + TRANSLATOR_MODEL.emptyString
            , qsTr("VOLUME_SETTING") + TRANSLATOR_MODEL.emptyString]
        property int indexSelect
        Column{
            id: choicelist
            anchors.fill: parent
            Repeater{
                model: rectSelectSetting.selectSrcChoice
                delegate: Button{
                    width: choicelist.width
                    height: 60
                    text: modelData
                    onClicked: {
                        rectSelectSetting.indexSelect = index;
                    }
                }
            }
        }
    }

    Loader{
        id: loadScreen
        anchors{
            top: statusbar.bottom
            left: rectSelectSetting.right
        }
        width: root.width - rectSelectSetting.width
        height: root.height - statusbar.height
        source: {
            switch (rectSelectSetting.indexSelect){
            case 0:
                return "qrc:/qml/screens/LanguageScreen.qml"
            case 1:
                return "qrc:/qml/screens/VolumeScreen.qml"
            }
        }


    }

}
