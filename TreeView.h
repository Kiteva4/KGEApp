#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QObject>
#include <QTreeView>
#include "TreeModelTest.h"

class TreeView : public QTreeView
{
public:

    TreeView();
    TreeModelTest * treeModelTest;
};

#endif // TREEVIEW_H
