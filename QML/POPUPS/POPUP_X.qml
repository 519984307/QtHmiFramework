import QtQuick 2.15
import VIEWENUMS 1.0

import "../" as Qml

Qml.QmlContainer {
    width: 420
    height: 255
    color: "gray"
    title: "POPUP X"

    Row {
        spacing: 10
        anchors {
            bottom: parent.bottom
            right: parent.right
        }

        Rectangle {
            width: 100
            height: 50
            color: "white"
            Text {
                text: qsTr("YES")
                anchors.centerIn: parent
                color: "black"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {

                }
            }
        }

        Rectangle {
            width: 100
            height: 50
            color: "white"

            Text {
                text: qsTr("NO")
                anchors.centerIn: parent
                color: "black"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_POPUP_X_EVT_NAV_SCREEN_A)
                    //                    QmlNgin.previousView()
                }
            }
        }
    }
}
