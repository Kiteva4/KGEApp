import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    id: _main
    visible: true
    width: 640
    height: 480

    TreeView {
        anchors.fill: parent
        model: _myTreeModel

        itemDelegate: Rectangle{
            color: styleData.selected ? "red" : "steelblue"
                       Text{
                           anchors.verticalCenter: parent.verticalCenter
                           anchors.left: parent.left // by default x is set to 0 so this had no effect
                           text: styleData.value
                       }
        }

        //            itemDelegate: Rectangle {
        //               color: "lightblue"
        //               height: 20

        //               Text {
        //                   anchors.verticalCenter: parent.verticalCenter
        //                   anchors.left: parent.left // by default x is set to 0 so this had no effect
        //                   text: styleData.value
        //               }
        //           }

        TableViewColumn {
            role: "name_role"
            title: "Hierarchy"
        }
    }

}
