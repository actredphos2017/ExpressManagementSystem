#ifndef MENUFORWAITER_H
#define MENUFORWAITER_H

#include <QMainWindow>
#include <QPushButton>


#include "../userObjects/CircleProgressBar.h"
#include "WaiterExtraWindows/WaiterExpressEditWindow.h"
#include "WaiterExtraWindows/AccountEditWindow.h"
#include "Settings.h"

namespace Ui {
class MenuForWaiter;
}

class MenuForWaiter : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuForWaiter(QWidget *parent = nullptr);
    ~MenuForWaiter() override;

    Settings* settingWin;

private:
    Ui::MenuForWaiter *ui;

    CircleProgressBar *dayResAndPick;
    CircleProgressBar *allResAndPick;
    QPushButton* dayResBtn;
    QPushButton* allResBtn;

    WaiterExpressEditWindow* expressWindow;
    AccountEditWindow* accountWindow;

    vector<int> taken_wareInfo;
    OrderInfo* quickOrder;

    void initItems();
    void initConnects();
    void initPaint();
    void setShadow(QWidget* widget);

public slots:
    void loginSuccess();
    void quickInfo(const QString &);
    void updateProgresBar();
    void setPick();
};

#endif // MENUFORWAITER_H
