import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ProcessManager

Item {
    required property ProcessModel process

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Label {
                    text: process.standartOutput
                }
            }
// - CommandInput -
//            TextField {
//                Layout.fillWidth: true
//                height: 50
//            }
        }
// - ToolBar -
//        Rectangle {
//            Layout.fillHeight: true
//            width: 150
//            color: "#ff0000"
//        }
    }
}
