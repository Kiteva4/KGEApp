import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4

TreeView {
    id: _treeview
    anchors.fill: parent

    TableViewColumn{
        title: "Objects"
        role: "objectName"
        width: parent.width
    }
}
