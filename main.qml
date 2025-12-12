import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 720
    height: 600

    Item {
        id: colorItem
        property color windowBgColor: "#ffbdbd" //darkYellow doesn't work? Why?
        property real windowFgColor: {
            var r = windowBgColor.r;
            var g = windowBgColor.g;
            var b = windowBgColor.g

            var fgBrightness = Math.sqrt(
                0.241 * r * r +
                0.691 * g * g +
                0.068 * b * b
            );
            return fgBrightness;
        // Credits: https://www.nbdtech.com/Blog/archive/2008/04/27/Calculating-the-Perceived-Brightness-of-a-Color.aspx
        }
    }

    color: colorItem.windowBgColor
    property string currentMode: timerManager.onBreak ? "Long Break" : "Work Period"
    title: qsTr("Ultradium -- " + currentMode)

    property bool isRunning: false
    //QVariant runningVar(isRunning)
    property var textstring: isRunning.toString
    //property string textstring: "isRunning = " + isRunning
    property int counter: 0
    property string currentQuote: ""
    property bool q_breakNess: true

    Column {
        //anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.80
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
            text: {
                color: colorItem.windowFgColor
                isRunning ? "Stop Timer" : "Start Timer"
            }
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                q_breakNess = timerManager.onBreak
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
                        timerManager.start(timerManager.m_workDuration/60, timerManager.remainingTime/60, false, q_breakNess);
                        // Selecting whether to run break or work time is handled in timerManager. Keep the order correct here
                        isRunning = true
                        timerManager.onPause = false
                    }
                    else {
                        timerManager.start(timerManager.remainingTime/60, timerManager.m_breakDuration/60, false, q_breakNess);
                        isRunning = true
                        timerManager.onPause = false
                    }
                    // remainingTime is in seconds, function prototype is in minutes
                }
                else {
                    //timerManager.start(25, 5, false) // or use user inputs
                    //timerManager.m_onBreak = false
                    timerManager.start(25, 5, false, false) // or use user inputs
		    isRunning = true // initially turn break off with q_breakNess
                    timerManager.onPause = false
                }
            }
        }

        Text {
            id: quote
            //visible: timerManager.onBreak ? false : true
            //visible: !(isRunning)
            //visible: true
            //text: quotesManager.randomQuote() + "QUOTE!"
            //text: "wtf man" + quotesManager.randomQuote (Can't have the ())
            text: timerManager.onBreak? "Enjoy your break!" : quotesManager.randomQuote
            // Will allow persistent location, and to update quote whenver onBreak changes.
            color: colorItem.windowFgColor
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.8
            font.pixelSize: 26
        }

    }

    Connections {
        target: timerManager
        function onSessionComplete() {
        currentQuote = quotesManager.randomQuote
        }
        /*
        function onBreakChanged() {
            //quote.text = "hellllo" + textstring
            //quote.text = "boooooooo running? " + isRunning
            //quote.text = "Current onBreak = " + timerManager.onBreak
            //quote.text = /*quote.text /*"shieeeeeeeet"
            breakLightIndicator.text = breakLightIndicator.text
        }
        */
    }
}

