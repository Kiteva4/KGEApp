#include "TreeView.h"
#include <QHeaderView>

//TreeView::TreeView(TreeModelTest *model)
//{
//    setModel(model);
//    TreeView();
//}

TreeView::TreeView()
{
    treeModelTest = new TreeModelTest();
//    connect(this, &QTreeView::pressed, this, &QTreeView::expandAll);
    setDragEnabled(true);
    setAcceptDrops(true);
    resizeColumnToContents(0);
//    resize(400, 500);
    setSelectionMode(QAbstractItemView::SingleSelection);
    expandAll();
//    connect(this, &QTreeView::pressed, this, &QTreeView::expandAll);
    header()->setVisible(false);
//    setIndentation(5);

    setModel(treeModelTest);

    setEditTriggers(QAbstractItemView::EditTriggers());
}
