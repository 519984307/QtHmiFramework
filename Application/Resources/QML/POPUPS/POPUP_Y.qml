import QtQuick 2.15
import VIEWENUMS 1.0
import Common.Qml 1.0

import "../" as Qml

QmlPopup {
    color: "orange"
    title: "POPUP Y"

    Text {
        id: idStackDepth
        text: `[Title:${title}] Depth: ${QmlPopupManager.depth}`
        color: "black"
        font.bold: true
        anchors {
            top: parent.top
            topMargin: 50
            left: parent.left
            leftMargin: 50
        }
    }

    Row {
        spacing: 10
        anchors.centerIn: parent
        Rectangle {
            width: 100
            height: 50
            color: "white"
            Text {
                text: qsTr("POPUP X")
                anchors.centerIn: parent
                color: "gray"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_POPUP_Y_EVT_OPEN_POPUP_X)
                }
            }
        }
        Rectangle {
            width: 100
            height: 50
            color: "white"
            Text {
                text: qsTr("POPUP Z")
                anchors.centerIn: parent
                color: "purple"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_POPUP_Y_EVT_OPEN_POPUP_Z)
                }
            }
        }
    }

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
                    QmlNgin.sendEvent(EVT.E_POPUP_Y_EVT_CANCEL)
                }
            }
        }
    }
}
