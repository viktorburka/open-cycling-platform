import QtQuick 2.7

Item {
    signal endWorkout()
    Grid {
        anchors.fill: parent
        rows: 3; columns: 3
        WorkoutMetric {
            header: "Time"
            value: workoutController.elapsedTime
            width: parent.width / 2; height: parent.height / 2
        }
        VerticalGridSpacer {
            height: parent.height / 2
        }
        WorkoutMetric {
            header: "Distance"
            value: "---"
            width: parent.width / 2; height: parent.height / 2
        }
        HorizontalGridSpacer {
            width: parent.width / 2
        }
        HorizontalGridSpacer {
            width: 1
        }
        HorizontalGridSpacer {
            width: parent.width / 2
        }
        WorkoutMetric {
            header: "Time Of Day"
            value: workoutController.currentTime
            width: parent.width / 2; height: parent.height / 2
        }
        VerticalGridSpacer {
            height: parent.height / 2
        }
        WorkoutMetric {
            header: "Calories"
            value: "---"
            width: parent.width / 2; height: parent.height / 2
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: { parent.endWorkout() }
    }
}
