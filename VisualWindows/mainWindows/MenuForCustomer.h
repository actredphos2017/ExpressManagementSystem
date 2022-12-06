#ifndef MENUFORCUSTOMER_H
#define MENUFORCUSTOMER_H

#include "../../GlobalAttribute.h"
#include "../userObjects/PickupQuickTag.h"

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

private:
    ;
    orderGroup* customerPackage{};

    Ui::MenuForCustomer *ui;
    //void initItem();
    void initConnect();
    void addQuickTag(QVBoxLayout *quickTagsGroup, PickupQuickTag *quickTag);
    void initQuickBox();

public slots:
    void loginSuccess();
};

#endif // MENUFORCUSTOMER_H
