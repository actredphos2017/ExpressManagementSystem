#ifndef MENUFORWAITER_H
#define MENUFORWAITER_H

#include <QMainWindow>
#include <QPushButton>


#include "../userObjects/CircleProgressBar.h"
#include "WaiterExtraWindows/WaiterExpressEditWindow.h"

namespace Ui {
class MenuForWaiter;
}

class MenuForWaiter : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuForWaiter(QWidget *parent = nullptr);
    ~MenuForWaiter() override;

private:
    Ui::MenuForWaiter *ui;
    CircleProgressBar *dayResAndPick;
    CircleProgressBar *allResAndPick;
    QPushButton* dayResBtn;
    QPushButton* allResBtn;
    WaiterExpressEditWindow* expressWindow;

    void initItems();
    void initConnects();
    void setShadow(QWidget* widget);

public slots:
    void loginSuccess();
};

#endif // MENUFORWAITER_H
