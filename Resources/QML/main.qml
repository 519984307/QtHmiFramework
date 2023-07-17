import QtQuick 2.15
import QtQuick.Window 2.15
import Common.Qml 1.0
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

    QmlStackView {
        visible: true
        anchors.fill: parent
    }

    Qml.QmlLoader {
        visible: false
        id: idQmlScreenLoader
        objectName: "qml_root_screen_loader"
        anchors.fill: parent
    }

    Qml.QmlLoader {
        visible: false
        objectName: "qml_root_popup_loader"
        anchors.centerIn: idQmlScreenLoader
    }
}
