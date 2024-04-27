import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: "File"
            Action { text: "New" }
        }
    }

    RowLayout {
        anchors.margins: 5
        anchors.fill: parent

        Page {
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignLeft
            Layout.fillHeight: true

            header: Text { text: "Title"; padding: 5 }

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
                    onClicked: processTabsView.open(title)
                }

                model: ListModel {
                    ListElement { title: "First"}
                    ListElement { title: "Second"}
                    ListElement { title: "Third"}
                }
            }
        }

        Page {
            id: processTabsView
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
            Layout.fillHeight: true

            component Process : QtObject {
                property string title
                property string desc
            }

            property Component template: Process {};

            property int activeIndex: 0
            Binding { processTabsView.activeIndex: processTabsBar.currentIndex }

            property list<Process> openedProcces: [
                Process { title: "First" },
                Process { title: "Second" }
            ]

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
                    delegate: Rectangle { color: "#ff0000" }
                }
            }

            function indexOf(title) {
                for(var i = 0; i < openedProcces.length; i++) {
                    if (openedProcces[i].title === title)
                        return i
                }
                return -1
            }

            function setActive(index) {
                if (index >= 0 && index < openedProcces.length)
                    processTabsBar.currentIndex = index
            }

            function open(title) {
                let index = indexOf(title);

                if (index < 0) {
                    let process = template.createObject(this, { title: title })
                    let length = openedProcces.push(process)
                    // вставляем всегда в конец
                    index = length - 1
                }

                setActive(index)
            }
        }

    }
}
