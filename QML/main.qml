import QtQuick 2.15
import QtQuick.Window 2.15
import "." as Qml

Window {
    objectName: "qml_root_window"
    width: QmlRootScreenWidth
    height: QmlRootScreenHeight
    visible: true
    title: qsTr("XXX")

    Connections {
        target: QmlNgin
        function onInitCompleted() {
            console.log("Root Initialize Completed!!!")
        }
    }

    Qml.QmlLoader {
        id: idQmlScreenLoader
        objectName: "qml_root_screen_loader"
        anchors.fill: parent
    }

    Qml.QmlLoader {
        objectName: "qml_root_popup_loader"
        anchors.centerIn: idQmlScreenLoader
    }
}
