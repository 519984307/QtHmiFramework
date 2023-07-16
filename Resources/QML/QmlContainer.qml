import QtQuick 2.15

Rectangle {
    property string title: ""
    color: "transparent"
    Text {
        id: idScreenTitle
        text: title
        color: "black"
        font.bold: true
        anchors {
            top: parent.top
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }
    }
}
