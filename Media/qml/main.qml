import QtQuick 2.9
import QtQuick.Window 2.12

Window {
    id: root
    visible: SETTING_MODEL.visible;
    title: qsTr("MUSIC_APP_TITLE") + SETTING_MODEL.emptyString

    width: 1060
    height: 540
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width


    readonly property int _ANIMATION_TYPE_NONE: 0
    readonly property int _ANIMATION_TYPE_PUSH: 1
    readonly property int _ANIMATION_TYPE_POP: 2

    property int animationType: _ANIMATION_TYPE_NONE
    property var layerBase: layer_base_1

    function loadScreen() {
        layerBase.source = ""
        layerBase.source = SCREEN_MODEL.currentScreen
    }

    function swapLayerBase(from, to) {
        console.log("handle swap layer with animation type: " + animationType)
        if (from.item !== null) {
            from.item.visible = false
            from.source = ""
        }
        if (to.item !== null) {
            to.item.visible = true
        }
        layerBase = from
    }

    // common screen loader
    Loader {
        id: layer_base_1
        anchors.fill: parent

        onLoaded: {
            swapLayerBase(layer_base_2, layer_base_1)
        }
    }

    Loader {
        id: layer_base_2
        anchors.fill: parent

        onLoaded: {
            swapLayerBase(layer_base_1, layer_base_2)
        }
    }

    Connections {
        target: SCREEN_MODEL
        ignoreUnknownSignals: true

        onScreenPushed: {
            console.log("onScreenPushed animation: " + animation)

            // set animation type
            if (animation) {
                animationType = _ANIMATION_TYPE_PUSH
            } else {
                animationType = _ANIMATION_TYPE_NONE
            }

            // load new screen
            layerBase.source = ""
            layerBase.source = SCREEN_MODEL.currentScreen
        }

        onScreenPopped: {
            console.log("onScreenPopped animation: " + animation)

            // set animation type
            if (animation) {
                animationType = _ANIMATION_TYPE_POP
            } else {
                animationType = _ANIMATION_TYPE_NONE
            }

            // load new screen
            layerBase.source = ""
            layerBase.source = SCREEN_MODEL.currentScreen
        }
    }
}
