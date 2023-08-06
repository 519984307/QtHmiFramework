import QtQuick 2.15
import Api.Common 1.0

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

    Text {
        id: idStackDepth
        text: `StackView Depth: ${QmlViewManager.depth}`
        color: "black"
        font.bold: true
        anchors {
            top: parent.top
            topMargin: 50
            left: parent.left
            leftMargin: 50
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
