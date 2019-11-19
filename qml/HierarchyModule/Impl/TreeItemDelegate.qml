import QtQuick 2.0
import QtQuick 2.12


Item {
    id: delegateItem
    width: listView.width
    height: 50

    Rectangle {
        id: dragRect
        width: listView.width
        height: 50
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
                    listView.dragItemIndex = index;
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
