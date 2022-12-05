#ifndef MENUFORWAITER_H
#define MENUFORWAITER_H

#include <QMainWindow>

namespace Ui {
class MenuForWaiter;
}

class MenuForWaiter : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuForWaiter(QWidget *parent = nullptr);
    ~MenuForWaiter();

private:
    Ui::MenuForWaiter *ui;
};

#endif // MENUFORWAITER_H
