// SPDX-License-Identifier: GPL-3.0-only
/* main.qml - Main Qt Meta Language file for the UltradiumTimer GUI
 *
 * Copyright (C) 2025 feeRnt; <81442162+feeRnt@users.noreply.github.com>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */


import QtQuick 2.15
//import QtQuick.Controls 2.15
import QtQuick.Window 2.15
//import QtQuick.Dialogs 2
import QtQuick.Controls.Material 2.4
//import QtQuick.Controls.Fusion

/* TO-DO:
  1. instead of top padding elements, top pad the column,
  and also left pad the column.

  Items will not overlap in this way, and IF you need,
  add bottom padding to the item before the one which needs to be added/padded
*/

ApplicationWindow {
    visible: true
    width: 840
    height: 600
    //width: mainWindow.width
    //height: mainWindow.height


    Item {
        id: colorItem
        /*if file
            workBgColor: workBgColor INI value
            breakColor: breakBgColor INI value
        else
            workColor: 48d291
            breakColor: ffbdbd;
            save to INI (nah just always have the ini file.. but what if the user deletes the ini?? OOOHhhhh right.)
        */
            property color windowBgColor: timerManager.onBreak? "#48d291" : "#ffbdbd" //darkYellow doesn't work? Why?
        //oldWork: "#" "#c4808d"
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
            /* Credits: https: Based on formula from
            https://www.nbdtech.com/Blog/archive/2008/04/27/Calculating-the-Perceived-Brightness-of-a-Color.aspx
            https://alienryderflex.com/hsp.html */
        }
        property color windowFgColor: getFgColor(windowBgColor)
    }

    color: colorItem.windowBgColor
    property string currentMode: timerManager.onBreak ? "Long Break" : "Work Period"
    title: qsTr("Ultradium -- " + currentMode)

    property bool isRunning: false
    property string currentQuote: ""
    property bool qml_breakness: true
    property bool quotesOn: false
    property int counterUser: 0
    property bool qml_ultradianModeRequested: false
    property int longBreakAfter: 3
    property bool settingsOn: false

    property bool qml_eyeTimerIsRunning: false
    property bool qml_onEyeBreak: false

    header: ToolBar {

        //RowLayout {
            //anchors.fill: parent
            //background: colorItem.windowBgColor
            ToolButton {
                id: header_settings_button
                text: "\u2630"
                font.pointSize: 18
                onClicked: {
                    settingsOn = !settingsOn
                }
            }
            height: header_settings_button.height * .5
            /*Label {
                text: "Title"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                //Layout.fillWidth: true
            }
            */
            /*ToolButton {
                text: qsTr("⋮")
                onClicked: menu.open()
            }
            */
        }
    //}

    /*SettingsMenu {
        visible: settingsOn ? true : false
    }
    */

    Rectangle {
     //   width: parent.width
     //   height: parent.heights
        id: settingsWindow
        anchors.fill: parent
        opacity: 1
        visible: settingsOn ? true : false
        z: 10

        property color settingsBgColor: Qt.lighter(colorItem.windowBgColor, .5)
        property color settingsFgColor: colorItem.getFgColor(settingsBgColor)
        color: "black"
        border.color: "black"
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "#000000";
            }
            GradientStop {
                position: 1.00;
                color: "#ffffff";
            }
        }

        Rectangle {
            anchors.fill: parent //this is imperative for subcomponents
            color: settingsWindow.settingsBgColor

            Behavior on visible {
                NumberAnimation {
                    from: 0
                    to: 1
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }

            Rectangle {
                id: color_selector_box
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: settings_bgcolor_text
                    text: "Change the background colors?"
                    color: settingsWindow.settingsFgColor
                }

                Button {
                    id: colorSelectorButton
                    anchors.left: settings_bgcolor_text.right
                    text: {
                    "\u1f3a8"
                    }
                    background:
                        Rectangle {
                        color: "transparent"
                        border.width: 0
                    }
                    onClicked: {
                        //colorDialog.open
                        colorPicker.
                        colorItem.windowFgColor = colorDialog.colorDialogPickedColor
                    }
                }

            }
        }
    }


    Popup {
        id: popup
        x: 100
        y: 100
        width: 300
        height: 50
        modal: true // Disallows exiting by clicking outside of box
        focus: true
        dim: true
        //visible: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside //| Popup.CloseOnPressOutsideParent

        contentItem: Text {
            id: popUpText
            //text: "Selected " + workTimeSelector.text + " minute(s) as work time."
            //font.bold: true
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
            color: colorItem.windowFgColor
        }
        background: Rectangle {
               // Set the background color
               color: "#B0BEC5" // A light gray-blue color
               border.color: "#333"
               border.width: 1
               radius: 5
        }
    }
/*
    ColorDialog {
        property color pickedColor
        property color colorDialogPickedColor
        id: colorDialog
        title: "Pick the breaktime color:"
        pickedColor: Qt.rgba(1, 1, 1, 1)

        onAccepted:
            colorDialogPickedColor = pickedColor
    }
*/
    Column {
        id: leftColumn
        width: (1 - mainColumn.width )/2 //0.275
        //leftPadding: 10
        height: parent.height
        anchors.left: parent.left
        anchors.right: mainColumn.left
        //anchors.rightMargin: 2
        visible: true


        /*Item {
            id: workBreakTimeSelector
            width: parent.width
            height: 30 // If you see heigth = parent.height, then the whole of the column will
                    // be filled by this "empty" item, even though there's nothing in it.
                    // Meaning other things besides and within this item, will not be visible.
            //visible: true
            //anchors.left: parent.left (You cannot set anchor for items inside column. Error.
            //Column handles it automatically

            //You also can't do anchors.left: parent.anchors.left; that is wrong syntax.
            //You also can't really do width: parent, this is wrong syntax
            //The compiler will not tell you about this error. You'll be in endless limbo
            //not knowing the issue was wrong syntax.

            //However, for anchors.fill: parent seems to be correct
        */
        Text {
            width: parent.width
            //height: 10 // height literally messes with everything. Don't specify unless needed
            topPadding: 25
            leftPadding: 22
            text: "\u25a3 How long do you want your Pomodoro (typically 25 minute) work sessions to be, in minutes?"
            font.bold: true
            wrapMode: Text.Wrap
        }
        TextField {
            id: workTimeSelector
            leftInset: 20
            leftPadding: 24
            //anchors.margins: 66
            topInset: 17
            topPadding: 21
            //implicitWidth: 200
            width: 250
            //height: 10 //not in pixels when inside Item { ?
            //implicitHeight: 10
            placeholderText: qsTr("Enter a value between 0.01, and 1000\n ") //\n& hit Enter")
            //Material.containerStyle: Material.Filled //prevents the placeholder from floating above :: edit: doesn't
            //font.capitalization: "AllUppercase"
            //font.pixelSize: 10
            placeholderTextColor: colorItem.windowFgColor
            font.pixelSize: 14
            font.weight: Font.Light

            validator: DoubleValidator {
                bottom: 0.01
                top: 1000
                decimals: 2
                notation: DoubleValidator.StandardNotation
            }

            /*Item {
                id: workTimeSelectorItem
                width: 10
                height: 4
            }*/
            onAccepted: { //onEditingFinished creates double popup: Once with Enter Press,
                //                                                  then with lost focus.
                //timerManager.m_workPeriod_min = workTimeSelector.text
                //timerManager.workPeriodChanged()
                timerManager.m_workPeriod_minSetter(workTimeSelector.text)
                console.log("selector's text is " + workTimeSelector.text)
                popUpText.text = "Selected " + workTimeSelector.text + " minute(s) as work time."
                //popup.contentItem = workTimSelectorItem
                //workTimeSelectorItemText
                popup.open()
            }
            onEditingFinished: {
                timerManager.m_workPeriod_minSetter(workTimeSelector.text)
            }
        }



        Text {
            id: breakTimeSelectorText
            text: "\u25a3 How much time would you like as a short break in between your work? (Usually 5 minutes)"
            width: parent.width
            topPadding: 35
            leftPadding: 22
            font.bold: true
            wrapMode: Text.Wrap //without wrap, it just goes beyond your boundaries
        }
        TextField {
            id: breakTimeSelector
            leftInset: 20
            leftPadding: 24
            topInset: 16
            topPadding: topInset + 4
            implicitWidth: 200
            width: 250
            //height: 10
            //implicitHeight: 10
            placeholderText: qsTr("Enter a value between 0.01, and 1000\n ")//\n& hit Enter")
            //Material.containerStyle: Material.Filled
            font.pixelSize: 14
            font.weight: Font.Light
            placeholderTextColor: colorItem.windowFgColor
            validator: DoubleValidator {
                bottom: 0.01
                top: 1000
                decimals: 2
                notation: DoubleValidator.StandardNotation
            }
            onAccepted: {
                //popup.textToShow = breakTimeSelector.text
                //timerManager.m_shortBreakPeriod_min = breakTimeSelector.text
                //timerManager.shortBreakPeriodChanged()
                timerManager.m_shortBreakPeriod_minSetter(breakTimeSelector.text)
                console.log("selector's text is " + breakTimeSelector.text)
                popUpText.text = "Selected " + breakTimeSelector.text + " minute(s) as break time."
                popup.open()
            }
            onEditingFinished: {
                timerManager.m_shortBreakPeriod_minSetter(breakTimeSelector.text)
            }
        }


        Text {
            id: longBreakTimeSelectorText
            width: parent.width
            topPadding: 25
            leftPadding: 24
            text: "\u25a3 How long do you want your long break to be? (Typically 5+30 minutes)"
            font.bold: true
            wrapMode: Text.Wrap
        }
        TextField {
            id: longBreakTimeSelector
            leftInset: 22
            leftPadding: 22
            topInset: 16
            topPadding: 16+4
            width: 250
            placeholderText: qsTr("Enter a value between 0.01, and 1000\n ")//\n& hit Enter")
            //Material.containerStyle: Material.Filled //doesn't help?
            //\n helps with wrappign it seems even though there's only a space after it

            placeholderTextColor: colorItem.windowFgColor
            font.pixelSize: 14
            font.weight: Font.Light
            validator: DoubleValidator {
                bottom: 0.01
                top: 1000
                decimals: 2
                notation: DoubleValidator.StandardNotation
            }

            onAccepted: {
                //timerManager.m_longBreakPeriod_min = longBreakTimeSelector.text
                //timerManager.longBreakPeriodChanged()
                // DOES not work. Use a setter function like below...
                timerManager.m_longBreakPeriod_minSetter(longBreakTimeSelector.text)
                console.log("selector's text is " + longBreakTimeSelector.text)
                popUpText.text = "Selected " + longBreakTimeSelector.text + " minute(s) as the long break time."
                //popup.contentItem = workTimSelectorItem
                //workTimeSelectorItemText
                popup.open()
            }
            onEditingFinished: {
                timerManager.m_longBreakPeriod_minSetter(longBreakTimeSelector.text)
            }
        }
        Text {
            id: quotesOnOffSwitchText
            text: "\u2364 Enable displaying a few inspirational quotes?"
           //wrapMode: 1
            topPadding: 66 // The padding is relative to the last special item, like Switch
            leftPadding: 20
            width: parent.width
            //height: parent.height
            visible: true
            font.bold: true
            wrapMode: Text.Wrap
        }
        Switch {
            id: quotesOnOffSwitch
            topPadding: 6 // if you use an item class, then everything has to be
                        // manually padded like an insane man (seems like it)
                        // but this way, it's slightly easier?

            // Switches and TextFields have different apparent padding than normal text
            leftPadding: 20

            text: {
                qsTr("")
            }

            checked: false
            onToggled: {
                if (checked) {  // on toggled means: AFTER toggling, if checked, then turn on .. quotes
                    quotesOn = true
                  //  checked = true
                }
                else if (!checked) {
                    quotesOn = false
                //  checked = false (toggled automatically swtiches the checked bool)
                //  This creates a forever off cycle.
                }
            }
        }
    }

    Column {
        //anchors.centerIn: parent
        id: mainColumn
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.45
        //spacing: 20

        Text {
            id: breakLightIndicator
            text: timerManager.onBreak ? "Break Time" : "Work Time"
            font.pointSize: 24
            font.weight: 22
            font.bold: true
            font.family: "Helvetica"
            //horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.TopAnchor: parent.top + 20
            topPadding: 30
            color: colorItem.windowFgColor
        }

        Text {
            id: timer
            //visible: timerManager.onBreak ? false : true
            text: /*timerManager.onBreak?
                      "" :*/
                      Qt.formatTime(new Date(timerManager.remainingTime * 1000), "mm:ss")
            font.pixelSize: 40
            anchors.horizontalCenter: parent.horizontalCenter
            color: colorItem.windowFgColor
            //padding:
            bottomPadding: 40
        }

        Button {
            id: timerOnOffSwitch
            text: {
                color: colorItem.windowFgColor
                isRunning ? "Stop Timer" : "Start Timer"
            }
            anchors.horizontalCenter: parent.horizontalCenter
            Material.background: Material.Pink
            onClicked: {
                qml_breakness = timerManager.onBreak
                /*
                if (counter == 3) {
                    isRunning = true
                    timerManager.start(0, 30, true)
                }
                */
                if (isRunning) {
                    //counter = counter + 1
                    timerManager.onPause = true
                    //timerManager.onBreak = true
                    timerManager.stop()
                    isRunning = false
                }
                else if (!isRunning && timerManager.remainingTime > 0) {
                    if (timerManager.onBreak) {
                        timerManager.start(timerManager.m_workDuration/60, timerManager.remainingTime/60, false, qml_breakness, timerManager.counter);
                        // Selecting whether to run break or work time is handled in timerManager. Keep the order correct here
                        isRunning = true
                        timerManager.onPause = false
                    }
                    else {
                        timerManager.start(timerManager.remainingTime/60, timerManager.m_breakDuration/60, false, qml_breakness, timerManager.counter);
                        isRunning = true
                        timerManager.onPause = false
                    }
                    // remainingTime is in seconds, function prototype is in minutes
                }
                else {
                    //timerManager.start(25, 5, false) // or use user inputs
                    //timerManager.m_onBreak = false
                    timerManager.workPeriod //m_elements are not accessible by QML... Only Q_PROPERTY listed vars are
                    timerManager.start(timerManager.workPeriod_min, timerManager.shortBreakPeriod_min, qml_ultradianModeRequested, false, counterUser) // or use user inputs
                    isRunning = true // initially turn break off with qml_breakness
                    timerManager.onPause = false // <--- wont' work?
                }
            }
        }

        Button {
            id: resetButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: {
                "Reset the timer"
            }

            Material.background: Material.Blue
            /*palette: {
                button: "#234235"
            }*/
            //Fusion.buttonColor: "#234235"

            /*background: {
                color: "#blue"
            }*/

            onClicked: {
                timerManager.reset()
                timerManager.onPause = false
                isRunning = false
            }
        }

        Text {
            id: quote
            //visible: timerManager.onBreak ? false : true
            //visible: !(isRunning)
            //visible: true
            //text: quotesManager.randomQuote() + "QUOTE!"
            //text: "wtf man" + quotesManager.randomQuote (Can't have the ())
            text: timerManager.onBreak? "Enjoy your break!" : quotesOn ? quotesManager.randomQuote : ""
            // Will allow persistent location, and to update quote whenver onBreak changes.
            color: colorItem.windowFgColor
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.8
            font.pixelSize: 26
        }

    }

    Column {
        id: rightColumn
        width: (1 - mainColumn.width )/2 //0.275
        height: parent.height
        anchors.left: mainColumn.right
        anchors.right: parent.right
        visible: true

        CheckBox {
            text: "yolo?"
        }

        Text {
            visible: false
            id: dummyText
            text: "👁   00:00"
            font.pixelSize: 19
        }

        Rectangle {
            color: eyeTimer.onEyeBreak ? "#992430" : "Blue"
            id: eyeBreakTimer
            visible: true
            property real width_largest: eyeBreakTimerText.width + eyeBreakTimerText.width*0.6
            property real height_largest: eyeBreakTimerText.height + 4

            /*width:  width_largest > eyeBreakTimerText.width + eyeBreakTimerText.width*0.6 ?
                        width_largest
                      : eyeBreakTimerText.width + eyeBreakTimerText.width*0.6*/
            width: dummyText.width + dummyText.width*0.6
            height: eyeBreakTimerText.height + 4 // a little padding looks nice here
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: eyeBreakTimerText
                text: eyeTimer.onEyeBreak ? "👁   " + Qt.formatTime(new Date(eyeTimer.eyeTimerRemainingTime * 1000), "mm:ss")
                                          : "🗺️   " + Qt.formatTime(new Date(eyeTimer.eyeTimerRemainingTime * 1000), "mm:ss")
                font.pixelSize: 19
                color: colorItem.windowFgColor
                anchors.horizontalCenter: parent.horizontalCenter
            }

        }

        Text {
            id: eyeBreakText
            visible: true
            text: eyeTimer.onEyeBreak ? "Give your eyes a break!\n"
            /*: "asd " + String.fromCharCode(0x1F441) +  "w \u128065 toooo \u1F441 toooo \uF09F9181"//"\n\n\n"
               Just not working for some reason */
            : " --- \n" // padding for consistent height. With empty space or no character, it is evaluated as non existent space
            anchors.horizontalCenter: parent.horizontalCenter


            font.pixelSize: 17
            //style: Text.Outline
            wrapMode: Text.Wrap
            bottomPadding: 3
            // font.family: "Segoe UI ladflks" // mention emoji font in main.cpp
        }

        Button {
            id: eyeTimerOnOffSwitch
            text: {
                color: colorItem.windowFgColor
                qml_eyeTimerIsRunning ? "Stop" : "Start"
            }
            //anchors.left: parent.horizontalCenter - 1
            anchors.horizontalCenter: parent.horizontalCenter
            Material.background: Material.Red
            onClicked: {
                qml_onEyeBreak = eyeTimer.onEyeBreak

                if (qml_eyeTimerIsRunning) {
                    eyeTimer.eyeTimerStop()
                    qml_eyeTimerIsRunning = false
                }
                else if (!qml_eyeTimerIsRunning && eyeTimer.eyeTimerRemainingTime > 0) {
                    if (eyeTimer.onEyeBreak) {
                        eyeTimer.eyeTimerStart(eyeTimer.eyeTimerDuration, eyeTimer.eyeTimerRemainingTime/60, qml_onEyeBreak);
                        qml_eyeTimerIsRunning = true
                        // TODO: Make *60 multiplicatives apply to timer start function only for timerManager too
                    }
                    else {
                        eyeTimer.eyeTimerStart(eyeTimer.eyeTimerRemainingTime/60, eyeTimer.eyeTimerBreakDuration, qml_onEyeBreak);
                        qml_eyeTimerIsRunning = true
                    }
                }
                else {
                    eyeTimer.eyeTimerStart(eyeTimer.eyeTimerDuration_default, eyeTimer.eyeTimerBreakDuration_default, false)
                    //eyeTimer.eyeTimerStart(.2, .02, false)
                    qml_eyeTimerIsRunning = true
                }
            }
        }

        Button {
            id: eyeTimerResetButton
            //anchors.left: eyeTimerOnOffSwitch.right
            //anchors.top: eyeTimerOnOffSwitch.
            anchors.horizontalCenter: parent.horizontalCenter
            text: {
                "Reset"
            }
            Material.background: Material.Grey
            onClicked: {
                eyeTimer.eyeTimerReset()
                qml_eyeTimerIsRunning = false
            }
        }

        Text {
            id: remainingWorkRoundsText
            visible: true    // These values are initialized, but they wil be NaN if QML has no way no way to get them (no Getter)
            /*remainingTime: !isRunning ? (3 * timerManager.workPeriod_min + 2 * timerManager.shortBreakPeriod_min) :
                timerManager.ultradianMode ? 0 :
                Math.round((timerManager.remainingTime/60 + (( (3 - timerManager.counter - 1)*(timerManager.workPeriod_min) +
                                                              (3 - timerManager.counter - 1)*(timerManager.shortBreakPeriod_min))) )*100)/100
            */
            property real totalRemainingTime: (timerManager.ultradianModeOn ? 0
                         /*: (!isRunning && timerManager.remainingTime > 0 && !timerManager.onBreak) ? timerManager.workPeriod_min + (longBreakAfter-1)*(timerManager.workPeriod_min + timerManager.shortBreakPeriod_min) //this conditioning is redundant
                         : !isRunning ? timerManager.workPeriod_min + (longBreakAfter-1)*(timerManager.workPeriod_min + timerManager.shortBreakPeriod_min)*/
                         : (!timerManager.onBreak && timerManager.remainingTime >= 0) ? timerManager.remainingTime/60 + (longBreakAfter - timerManager.counter - 1)*(timerManager.workPeriod_min + timerManager.shortBreakPeriod_min)
                         : ( timerManager.onBreak && timerManager.remainingTime >= 0) ? timerManager.remainingTime/60 + timerManager.workPeriod_min + (longBreakAfter - timerManager.counter - 1)*(timerManager.workPeriod_min + timerManager.shortBreakPeriod_min)
                         : ( timerManager.remainingTime <= 0) ? timerManager.workPeriod_min + (longBreakAfter-1)*(timerManager.workPeriod_min + timerManager.shortBreakPeriod_min)
                         : 0 ).toFixed(2) // -1 in line 3 & 4 because we already count the existing cycle's periods explicitly
            text: (3 - timerManager.counter) + "/3 work sessions are left.\n" +
                    "A total of "+ totalRemainingTime + " minutes left."
              //          + (timerManager.remainingTime + ((3 - timerManager.counter - 1)*(timerManager.workPeriod_min + timerManager.shortBreakPeriod_min)))
            //    + "minutes left.", 'f', 2)
            bottomPadding: 16
        }

        Text {
            text: "\u2635 How many work cycles in would you like to start the timer?"
            width: parent.width * .90
            font.family: "NSimSun"
            style: Text.Outline
            //verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            wrapMode: Text.Wrap
        }

        ComboBox {
            //displayText: "How many work cycles in would you like to start the timer?"
            font.pixelSize: 14
            width: parent.width * 0.98
            model: ["First Cycle", "Second Cycle", "Third Cycle", "Ultradian Period (Long Break)"]
            onActivated:
                if (currentIndex===0) {
                    counterUser = 0;
                    qml_ultradianModeRequested = false;
                }
                else if (currentIndex===1) {
                    counterUser = 1;
                    qml_ultradianModeRequested = false;
                }
                else if (currentIndex===2) {
                    counterUser = 2;
                    qml_ultradianModeRequested = false;
                }
                else if (currentIndex===3) {
                    qml_ultradianModeRequested = true;
                    counterUser = 3 - 1; // 1 will be added in the next part, to match against counter = 3
                }
        }

    }

    Connections {
        target: timerManager
        function onSessionComplete() {
            currentQuote = quotesManager.randomQuote
        }

        function onBreakChanged() {
            //breakLightIndicator.text = breakLightIndicator.text
            breakLightIndicator.text = timerManager.onBreak ? "Break Time" : "Work Time"
        }

        function onWorkPeriodChanged() {
            timerManager.m_workPeriod = workTimeSelector.text
        }
    }

    Connections {
        target: timerManager
        function onEyeTimerReset_from_timerManager() {
            eyeTimer.eyeTimerReset()
        }
    }
}
