import QtQuick 2.7

Item {
    signal endWorkout()
    Rectangle {
        anchors.fill: parent
        width: parent.width
        Text {
            anchors.centerIn: parent
            text: "workout"
        }
    }
}
