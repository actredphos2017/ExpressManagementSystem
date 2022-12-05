#ifndef MENUFORCUSTOMER_H
#define MENUFORCUSTOMER_H

#include <QMainWindow>

namespace Ui {
class MenuForCustomer;
}

class MenuForCustomer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuForCustomer(QWidget *parent = nullptr);
    ~MenuForCustomer();

private:
    Ui::MenuForCustomer *ui;
};

#endif // MENUFORCUSTOMER_H
