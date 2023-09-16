import QtQuick 2.15
import QtQuick.Window 2.15
import "." as Qml

Window {
    id: idRootWindow
    objectName: "qml_root_window"
    width: QmlRootScreenWidth
    height: QmlRootScreenHeight
    visible: true
    title: qsTr("HMIFramework")

    Connections {
        target: QmlNgin
        function onInitCompleted() {
        }
    }
}
