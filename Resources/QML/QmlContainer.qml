import QtQuick 2.15

Rectangle {
    property string title: ""

    signal entry();
    signal exit();

    color: "gray"
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

    Component.onCompleted: {
//        console.log(`[Entry][${title}]`)
        entry()
    }

    Component.onDestruction: {
//        console.log(`[Exit][${title}]`)
        exit()
    }
}
