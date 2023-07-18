import QtQuick 2.15
import QtQuick.Window 2.15
import "." as Qml

Window {
    objectName: "qml_root_window"
    width: QmlRootScreenWidth
    height: QmlRootScreenHeight
    visible: true
    title: qsTr("HMIFramework")

    Connections {
        target: QmlNgin
        function onInitCompleted() {
            console.log("Root Initialize Completed!!!")
        }
    }

    Rectangle {
        objectName: "qml_root_rect"
        anchors.fill: parent
        color: "transparent"

    }
}
