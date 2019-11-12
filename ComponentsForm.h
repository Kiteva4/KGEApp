#ifndef COMPONENTSFORM_H
#define COMPONENTSFORM_H

#include <QWidget>
#include <QQuickWidget>

namespace Ui {
class ComponentsForm;
}

class ComponentsForm : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentsForm(QWidget *parent = nullptr);
    ~ComponentsForm();

private:
    Ui::ComponentsForm *ui;
};

#endif // COMPONENTSFORM_H
