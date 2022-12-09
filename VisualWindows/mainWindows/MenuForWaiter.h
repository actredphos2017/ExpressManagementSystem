#ifndef MENUFORWAITER_H
#define MENUFORWAITER_H

#include <QMainWindow>


#include "../userObjects/CircleProgressBar.h"

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
    CircleProgressBar *dayResAndPick;
    CircleProgressBar *allResAndPick;

    void setShadow(QWidget* widget);

public slots:
    void loginSuccess();
};

#endif // MENUFORWAITER_H
