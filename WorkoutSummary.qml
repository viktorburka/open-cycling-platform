import QtQuick 2.7
import QtQuick.Controls 2.0

Item {
    signal startWorkoutClicked()
    signal backClicked()
    Text {
        id: previousWorkoutSummaryText
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width; height: 100
        text: "Previous Workout Summary"
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    Text {
        id: previousWorkoutSummaryValue
        anchors.top: previousWorkoutSummaryText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width; height: 50
        text: "1:23 minutes"
        font.pixelSize: 22
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    Item {
        id: spacer1
        anchors.top: previousWorkoutSummaryValue.bottom
        height: 100
    }
    Button {
        anchors.top: spacer1.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Start Workout"
        highlighted: true
        font.pixelSize: 16
        onClicked: {
            parent.startWorkoutClicked()
        }
    }
    BottomBar {
        id: bottomBar
        anchors.bottom: parent.bottom
        width: parent.width
        height: 40
        onBackClicked: parent.backClicked()
    }

//    states: [
//        State {
//            name: ""
//            PropertyChanges { target: previousWorkoutSummaryText; visible: true }
//            PropertyChanges { target: previousWorkoutSummaryValue; visible: true }
//        },
//        State {
//            name: "workout"
////            PropertyChanges { target: signal; color: "red"}
//        },
//        State {
//            name: "summary"
////            PropertyChanges { target: signal; color: "red"}
//        }
//    ]
}
