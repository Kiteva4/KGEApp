import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.12
import Qt.labs.folderlistmodel 2.1

import HierarchyModule.Impl 1.0
import HierarchyModule.Base 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480

    BaseTreeView {
       id: _myTreeView
       anchors.fill: parent
       model: _myTreeModel

       property int dragItemIndex: -1

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

       itemDelegate: Item {
           id: delegateItem
           width: _myTreeView.width
           height: 15

           Rectangle {
               id: dragRect
               width: _myTreeView.width
               height: 15
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.verticalCenter: parent.verticalCenter
               color: "salmon"
               border.color: Qt.darker(color)

               Text{
                   color: "white"
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.left: parent.left
                   text: "obj"
               }

               MouseArea {
                   id: mouseArea
                   anchors.fill: parent
                   drag.target: dragRect

                   drag.onActiveChanged: {
                       if (mouseArea.drag.active) {
                           _myTreeView.dragItemIndex = _myTreeView.index;
                       }
                       dragRect.Drag.drop();
                   }
               }

               states: [
                   State {
                       when: dragRect.Drag.active
                       ParentChange {
                           target: dragRect
                           parent: root
                       }

                       AnchorChanges {
                           target: dragRect
                           anchors.horizontalCenter: undefined
                           anchors.verticalCenter: undefined
                       }
                   }
               ]

               Drag.active: mouseArea.drag.active
               Drag.hotSpot.x: dragRect.width / 2
               Drag.hotSpot.y: dragRect.height / 2
           }
       }

       onDoubleClicked: isExpanded(index) ? collapse(index) : expand(index)

       onCurrentIndexChanged: {
           console.log("index = " + _myTreeView.currentIndex)
           //Show item properties
       }
   }
}
