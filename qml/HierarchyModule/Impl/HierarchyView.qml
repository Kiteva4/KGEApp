import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.12
//import HierarchyModule.Base 1.0


TreeView {
    id: _myTreeView
    anchors.fill: parent
    model: _myTreeModel

    TableViewColumn {
        id: _tableViewColumn
        width: _myTreeView.width
        //            movable: false
        //            resizable: false
        title: "Hierarchy"
    }

    headerDelegate: Rectangle {
        width: _myTreeView.width
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

    itemDelegate: TreeItemDelegate{

    }

    onDoubleClicked: isExpanded(index) ? collapse(index) : expand(index)

    onCurrentIndexChanged: {
        console.log("index = " + _myTreeView.currentIndex)
        //Show item properties
    }
}
