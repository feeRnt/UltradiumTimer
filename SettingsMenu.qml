import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Item {
    width: 700
    height: 600
    //visible: settingsOn ? true : false
    //visible: true
    opacity: 1


    property bool settingsOpen: false
    property color settingsBgColor: Qt.lighter(colorItem.windowBgColor, .5)
    function getFgColor(bgColor) {
        var r = bgColor.r;
        var g = bgColor.g;
        var b = bgColor.b;

        var fgBrightness = Math.sqrt(
            0.241 * r * r +
            0.691 * g * g +
            0.068 * b * b
        );
        return fgBrightness;
    }
    property color settingsFgColor: getFgColor(settingsBgColor)

    Rectangle {
        anchors.fill: parent //this is imperative for subcomponents
        color: settingsBgColor

        Behavior on visible {
            NumberAnimation {
                //target: object
                //property: "name"
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

        Text {
            id: settings_text
            text: "Boobie text"
            color: settingsFgColor
        }
    }
}

