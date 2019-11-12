import QtQuick 2.0
import QtQuick 2.12

Rectangle {
        id: _itemDelegate
        color: styleData.selected? "lightskyblue" : "transparent"

        Text{
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            text: "obj"
        }
    }
