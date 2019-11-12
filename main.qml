import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.12
//import HierarchyModule.Impl 1.0

Window {
    id: _main2
    visible: true
    width: 640
    height: 480

    //    HierarchyView{

    //    }

    Rectangle{
        anchors.fill: parent
        id: _main
        TreeView {
            id: _myTreeView
            anchors.fill: parent
            width: _main.width
            model: _myTreeModel

            TableViewColumn {
                id: _tableViewColumn
                width: _main.width
                //            movable: false
                //            resizable: false
                title: "Hierarchy"
            }


            headerDelegate: Rectangle {
                width: _main.width
                height: 20
                color: "#303030"

                Text {
                    id: _headerTex
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:  Text.AlignVCenter
                    text: qsTr("Hierarchy")
                    color: "aquamarine"
                }

                Rectangle{
                    height: 1
                    anchors{
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }
                }
            }

            style: TreeViewStyle{
                backgroundColor: "#303030"
                alternateBackgroundColor:"#303030"
                //branch delegates are used for delegating the arrow on the left
                branchDelegate: theBranchDelegate
            }

            alternatingRowColors: false
            clip: true

            selectionMode: SelectionMode.ExtendedSelection

            selection: ItemSelectionModel {
                id: _itemselection
                model: _myTreeModel
            }

            rowDelegate: Rectangle {

                height: 20
                color: "transparent"

                Rectangle {
                    height: 1
                    border.width : 1
                    anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }
                }
            }

            itemDelegate: Rectangle {
                id: _itemDelegate
                color: styleData.selected? "lightskyblue" : "transparent"

                Text{
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    text: "obj"
                }
            }

            onDoubleClicked: {

                if(!isExpanded(index))
                    expand(index)
                else
                    collapse(index)
            }

            onCurrentIndexChanged: {
                console.log("index = " + _myTreeView.currentIndex)
                //Show item properties
            }
        }
    }
}
