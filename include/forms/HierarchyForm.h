#ifndef HIERARCHYFORM_H
#define HIERARCHYFORM_H

#include "TreeModel.h"
#include "TreeView.h"

#include <QWidget>
#include <QQuickWidget>


namespace Ui {
class HierarchyForm;
}

class HierarchyForm : public QWidget
{
    Q_OBJECT

public:
    explicit HierarchyForm(QWidget *parent = nullptr);
    ~HierarchyForm();

private:
    Ui::HierarchyForm* ui;
    TreeView *treeView;
};

#endif // HIERARCHYFORM_H
