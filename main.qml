import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    width: 640
    height: 480
    visible: true
    StackLayout {
        id: layout
        anchors.fill: parent
        currentIndex: 1
        MainMenu {
            model: ListModel {
                ListElement { name: "Workout" }
                ListElement { name: "Settings" }
            }
            onMenuItemClicked: {
                switch(itemIndex) {
                  case 0:
                    layout.currentIndex = 1
                    break;
                  case 1:
                    layout.currentIndex = 2
                    break;
                }
            }
        }
        WorkoutSummary {
            onStartWorkoutClicked: {
                workoutController.startWorkout()
                layout.currentIndex = 3
            }
            onBackClicked: layout.currentIndex = 0
        }
        Settings {
        }
        Workout {
            onEndWorkout: {
                workoutController.stopWorkout()
                layout.currentIndex = 1
            }
        }
    }
}
