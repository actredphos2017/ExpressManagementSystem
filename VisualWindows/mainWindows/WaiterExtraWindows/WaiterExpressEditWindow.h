//
// Created by sakuno on 22-12-17.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_WAITEREXPRESSEDITWINDOW_H
#define EXPRESSMANAGEMENTSYSTEM_WAITEREXPRESSEDITWINDOW_H

#include <QDialog>

#include "../../../GlobalAttribute.h"

#include "ExpressEdit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WaiterExpressEditWindow; }
QT_END_NAMESPACE

class WaiterExpressEditWindow : public QDialog {
Q_OBJECT

public:
    explicit WaiterExpressEditWindow(QWidget *parent = nullptr);

    ~WaiterExpressEditWindow() override;

private:
    Ui::WaiterExpressEditWindow *ui;

    OrderGroup* viewOrders{};
    string editingOrderTrackNum;
    ExpressEdit* editWin{};

    void initItems();
    void initConnects();

public slots:
    void showAllExpress();
    void showDayExpress();

    void setHasTaken(bool ifTaken);
    void fleshTable();
    void prepareEdit();
    void pushEdit(OrderInfo *order);
    void removeItem();

signals:
    void toEdit(OrderInfo *order);
};


#endif //EXPRESSMANAGEMENTSYSTEM_WAITEREXPRESSEDITWINDOW_H
