import QtQuick 2.15
import VIEWENUMS 1.0
import Common.Qml 1.0

import "../" as Qml

QmlScreen {
    color: "green"
    title: "SCREEN C"

    Text {
        id: idStackDepth
        text: `StackView Depth: ${0}`
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
        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            width: 100
            height: 50
            color: "black"
            Text {
                text: qsTr("POPUP")
                anchors.centerIn: parent
                color: "white"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_POPUP_Z_EVT_SHOW)
                }
            }
        }

        Rectangle {
            width: 100
            height: 50
            color: "black"

            Text {
                text: qsTr("SCREEN A")
                anchors.centerIn: parent
                color: "white"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_SCREEN_B_EVT_NAV_SCREEN_A)
                }
            }
        }

        Rectangle {
            width: 100
            height: 50
            color: "black"

            Text {
                text: qsTr("SCREEN B")
                anchors.centerIn: parent
                color: "white"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_SCREEN_C_EVT_NAV_SCREEN_B)
                }
            }
        }
        Rectangle {
            width: 100
            height: 50
            color: "black"

            Text {
                text: qsTr("Back")
                anchors.centerIn: parent
                color: "white"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_SCREEN_C_EVT_BACK)
                }
            }
        }
    }
}
