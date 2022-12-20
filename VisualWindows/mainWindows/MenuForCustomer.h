#ifndef MENUFORCUSTOMER_H
#define MENUFORCUSTOMER_H

#include "../../GlobalAttribute.h"
#include "CustomerExtraWindows/MyExpresses.h"
#include "../userObjects/PickupQuickTag.h"
#include "Settings.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsEffect>

namespace Ui {
class MenuForCustomer;
}

class MenuForCustomer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuForCustomer(QWidget *parent = nullptr);
    ~MenuForCustomer();

    Settings* settingWin{};

private:
    void addShadow(QWidget *widget);
    OrderGroup* customerPackage{};
    MyExpresses* expressWindow;

    Ui::MenuForCustomer *ui;
    void addQuickTag(QVBoxLayout *quickTagsGroup, PickupQuickTag *quickTag);
    void initQuickBox();

    void initItems();
    void initDynamicItems();
    void initConnect();

public slots:
    void loginSuccess();
};

#endif // MENUFORCUSTOMER_H
