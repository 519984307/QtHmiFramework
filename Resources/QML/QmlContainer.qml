import QtQuick 2.15
import Common.Utilities 1.0

Rectangle {
    property string title: ""

    signal entry();
    signal exit();

    color: "gray"
    visible: false
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
//        Logger.qmlLogInfo(`[Entry][${title}]`)
        entry()
    }

    Component.onDestruction: {
//        Logger.qmlLogInfo(`[Exit][${title}]`)
        exit()
    }
}
