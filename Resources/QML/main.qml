import QtQuick 2.15
import QtQuick.Window 2.15
import Api.Common 1.0
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
            Logger.qmlLogInfo("Root Initialize Completed!!!")
        }
    }

    function loadScreen() {
        var comp = Qt.createComponent(
                    "qrc:/QML_RESOURCE/SCREENS/SCREEN_A.qml")
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(idRootWindow, { "anchors.fill": idRootWindow.contentItem})
        }
    }
}
