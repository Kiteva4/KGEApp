#include "ComponentsForm.h"
#include "ui_componentsform.h"

ComponentsForm::ComponentsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentsForm)
{
    ui->setupUi(this);
}

ComponentsForm::~ComponentsForm()
{
    delete ui;
}
