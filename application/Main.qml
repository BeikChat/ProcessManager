import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import ProcessManager

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Process Manager")

// - For tests -
//    menuBar: MenuBar {
//        id: menuBar
//        Menu {
//            title: "File"
//            Action {
//                text: "New"
//                onTriggered: ProcessManager.createProcess("ConsoleApplication.exe")
//            }
//        }
//    }

    RowLayout {
        anchors.margins: 5
        anchors.fill: parent

        Page {
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignLeft
            Layout.fillHeight: true

            header: Text { text: "Process List"; padding: 5 }

            Rectangle {
                anchors.fill: parent
                color: "#0f0000"
            }

            ListView {
                anchors.fill: parent
                spacing: 1
                clip: true

                delegate: ItemDelegate {
                    text: title
                    width: parent.width
                    onClicked: processTabsView.open(processModel)
                }

                model: ProcessListModel {}
            }
        }

        Page {
            id: processTabsView
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
            Layout.fillHeight: true

            property int activeIndex: 0
            Binding { processTabsView.activeIndex: processTabsBar.currentIndex }

            property list<ProcessModel> openedProcces: []

            header: TabBar {
                id: processTabsBar
                currentIndex: processTabsView.activeIndex

                Repeater {
                    model: processTabsView.openedProcces
                    delegate: TabButton { text: title; width: implicitWidth }
                }
            }

            StackLayout {
                id: processTabs
                anchors.fill: parent
                currentIndex: processTabsView.activeIndex

                Repeater {
                    model: processTabsView.openedProcces
                    delegate: ProcessView {
                        required property ProcessModel modelData
                        process: modelData
                    }//Rectangle { color: "#ff0000" }
                }
            }

            function indexOf(processModel) {
                for(var i = 0; i < openedProcces.length; i++) {
                    if (openedProcces[i].id === processModel.id)
                        return i
                }
                return -1
            }

            function setActive(index) {
                if (index >= 0 && index < openedProcces.length)
                    processTabsBar.currentIndex = index
            }

            function open(processModel) {
                let index = indexOf(processModel)

                if (index < 0) {
                    // вставляем всегда в конец
                    let length = openedProcces.push(processModel)
                    index = length - 1
                }

                setActive(index)
            }
        }

    }
}
