import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 360
    height: 600
    title: qsTr("Focus Timer")

    property bool isRunning: false
    property string currentQuote: ""

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: timerManager.onBreak ? "Break Time" : "Work Time"
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: Qt.formatTime(new Date(timerManager.remainingTime * 1000), "mm:ss")
            font.pixelSize: 40
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: isRunning ? "Stop" : "Start"
            onClicked: {
                if (isRunning) {
                    timerManager.stop()
                    isRunning = false
                } else {
                    timerManager.start(25, 5, false) // or use user inputs
                    isRunning = true
                }
            }
        }

        Text {
            visible: timerManager.onBreak
            text: quotesManager.randomQuote()
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            width: parent.width * 0.8
        }
    }

    Connections {
        target: timerManager
        onSessionComplete: currentQuote = quotesManager.randomQuote()
    }
}

