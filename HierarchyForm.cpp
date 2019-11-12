#include "HierarchyForm.h"
#include "ui_hierarchyform.h"
#include "TreeModel.h"
HierarchyForm::HierarchyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HierarchyForm)
{
    ui->setupUi(this);

    treeView = new TreeView();
    ui->gridLayout->addWidget(treeView);
}

HierarchyForm::~HierarchyForm()
{
    delete ui;
}
