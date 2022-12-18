//
// Created by sakuno on 22-12-17.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_WAITEREXPRESSEDITWINDOW_H
#define EXPRESSMANAGEMENTSYSTEM_WAITEREXPRESSEDITWINDOW_H

#include <QDialog>

#include "../../../GlobalAttribute.h"

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



    void initItems();
    void initConnects();


public slots:
    void showAllExpress();
    void showDayExpress();
    void fleshTable();
};


#endif //EXPRESSMANAGEMENTSYSTEM_WAITEREXPRESSEDITWINDOW_H
