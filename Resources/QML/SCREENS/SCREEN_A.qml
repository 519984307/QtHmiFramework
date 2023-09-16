import QtQuick 2.15
import VIEWENUMS 1.0
import Common.Qml 1.0

import "../" as Qml

QmlScreen {
    color: "red"
    title: "SCREEN A"

    Text {
        id: idStackDepth
        text: `StackView Depth: ${QmlScreenManager.depth}`
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
                    QmlNgin.sendEvent(EVT.E_POPUP_X_EVT_SHOW)
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
                    QmlNgin.sendEvent(EVT.E_SCREEN_A_EVT_NAV_SCREEN_B)
                }
            }
        }
        Rectangle {
            width: 100
            height: 50
            color: "black"

            Text {
                text: qsTr("SCREEN C")
                anchors.centerIn: parent
                color: "white"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_SCREEN_A_EVT_NAV_SCREEN_C)
                }
            }
        }

        Rectangle {
            width: 100
            height: 50
            color: idScrAMouseBack.enabled ? "black" : "gray"

            Text {
                text: qsTr("Back")
                anchors.centerIn: parent
                color: "white"
            }
            MouseArea {
                id: idScrAMouseBack
                anchors.fill: parent
                enabled: true
                onClicked: {
                    QmlNgin.sendEvent(EVT.E_SCREEN_A_EVT_BACK)
                }
            }
        }
    }
}
