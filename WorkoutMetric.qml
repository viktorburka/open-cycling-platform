import QtQuick 2.7

Item {
    id: root
    property string header
    property string value
    Column {
        anchors.fill: parent
        Text {
            font.pixelSize: 32
            text: root.header
            width: parent.width; height: parent.height / 2
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            font.pixelSize: 54
            font.bold: true
            font.family: "Fixed"
            text: root.value
            width: parent.width; height: parent.height / 2
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
        }
    }
}
