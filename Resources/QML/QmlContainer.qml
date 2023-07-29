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
        QmlLogger.qmlLogInfo(`[Entry][${title}]`)
        entry()
    }

    Component.onDestruction: {
        QmlLogger.qmlLogInfo(`[Exit][${title}]`)
        exit()
    }
}
