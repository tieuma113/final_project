import QtQuick 2.0
import QtQuick.Controls 2.12
import AppEnums 1.0

Item{
    id: root
    anchors.fill: parent
    property var selectSrcChoice: [qsTr("ENGLISH_CHOICE") + TRANSLATOR_MODEL.emptyString, qsTr("VIETNAMESE_CHOICE") + TRANSLATOR_MODEL.emptyString]
    signal clickedChoice(int idx)

    Column{
        id: choicelist
        anchors.fill: parent
        Repeater{
            model: root.selectSrcChoice
            delegate: RadioButton{
                text: modelData
                width: choicelist.width
                height: 60
                checked: index === TRANSLATOR_CTRL.language
                onCheckedChanged: {
                    if (checked){
                        clickedChoice(index)
                    }
                }
            }
        }
    }
    onClickedChoice: {
        switch (idx){
        case 0:
            TRANSLATOR_CTRL.language = AppEnums.LANGUAGE_ENGLISH;
            break;
        case 1:
            TRANSLATOR_CTRL.language = AppEnums.LANGUAGE_VIETNAMESE;
            break;
        default:
            break;
        }
    }
}
