#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "HierarchyForm.h"
#include "ComponentsForm.h"
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHierarchy_triggered()
{
    loadSubWindow(new HierarchyForm(this));
}


void MainWindow::on_actionComponents_triggered()
{
    loadSubWindow(new ComponentsForm(this));
}

void MainWindow::loadSubWindow(QWidget *widget)
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->setWindowTitle(widget->windowTitle());
    window->setWindowIcon(widget->windowIcon());
    window->show();
}
