import QtQuick 2.7

Rectangle {
    id: bar
    signal backClicked()
    Rectangle {
        height: 1
        color: "#ccc"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        height: 1
        color: "#fff"
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right
    }

    gradient: Gradient {
        GradientStop { position: 0 ; color: "#eee" }
        GradientStop { position: 1 ; color: "#ccc" }
    }

    MouseArea{
        anchors.fill: parent
        //enabled: ei.visible
        //Eats mouse events
    }

    Image {
        id: back
        source: "qrc:/images/back.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 2
        anchors.left: parent.left
        anchors.leftMargin: 16

        MouseArea {
            id: mouse
            hoverEnabled: true
            anchors.centerIn: parent
            width: 38
            height: 31
            anchors.verticalCenterOffset: -1
            onClicked: bar.backClicked()
            Rectangle {
                anchors.fill: parent
                opacity: mouse.pressed ? 1 : 0
                Behavior on opacity { NumberAnimation{ duration: 100 }}
                gradient: Gradient {
                    GradientStop { position: 0 ; color: "#22000000" }
                    GradientStop { position: 0.2 ; color: "#11000000" }
                }
                border.color: "darkgray"
                antialiasing: true
                radius: 4
            }
        }
    }
}
