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
    void addShadow(QWidget *widget);
    orderGroup* customerPackage{};

    Ui::MenuForCustomer *ui;
    void addQuickTag(QVBoxLayout *quickTagsGroup, PickupQuickTag *quickTag);
    void initQuickBox();

    void initItems();
    void initConnect();

public slots:
    void loginSuccess();
};

#endif // MENUFORCUSTOMER_H
