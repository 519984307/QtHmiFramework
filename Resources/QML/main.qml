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

    Qml.QmlLoader {
//        visible: false
        id: idQmlScreenLoader
        objectName: "qml_root_screen_loader"
        anchors.fill: parent
    }

    Qml.QmlLoader {
//        visible: false
        objectName: "qml_root_popup_loader"
        anchors.centerIn: idQmlScreenLoader
    }
}
