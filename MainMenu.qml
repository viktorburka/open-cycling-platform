import QtQuick 2.7

ListView {
    id: menu
    signal menuItemClicked(int itemIndex)
    clip: true
    delegate: Rectangle {
        width: ListView.view.width; height: 50
        gradient: Gradient {
            GradientStop {
                position: 0
                Behavior on color {ColorAnimation { duration: 100 }}
                color: button.pressed ? "#e0e0e0" : "#fff"
            }
            GradientStop {
                position: 1
                Behavior on color {ColorAnimation { duration: 100 }}
                color: button.pressed ? "#e0e0e0" : button.containsMouse ? "#f5f5f5" : "#eee"
            }
        }
        Image {
            id: image
            opacity: 0.7
            source: "qrc:/images/next.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 16
        }
        Item {
            id: button
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right:image.left
            height: implicitHeight
            width: buttonLabel.width + 20

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: menu.menuItemClicked(index)
                hoverEnabled: true
            }

            Text {
                id: buttonLabel
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                text: name
                color: "black"
                font.pixelSize: 22
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                styleColor: "white"
                style: Text.Raised

            }
        }
        Rectangle {
            height: 1
            color: "#ccc"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}
