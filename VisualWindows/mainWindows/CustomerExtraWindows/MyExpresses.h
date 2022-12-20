//
// Created by sakuno on 22-12-20.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_MYEXPRESSES_H
#define EXPRESSMANAGEMENTSYSTEM_MYEXPRESSES_H

#include <QDialog>
#include <QMessageBox>

#include "../../../GlobalAttribute.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyExpresses; }
QT_END_NAMESPACE

class MyExpresses : public QDialog {
Q_OBJECT

public:
    explicit MyExpresses(QWidget *parent = nullptr);

    ~MyExpresses() override;

private:
    Ui::MyExpresses *ui;

    OrderGroup* viewOrders;

    bool selectAllExpress;

    void initItem();
    void initConnect();

public slots:
    void toSeeAllPackages();
    void toSeeNowadaysPackages();
    void fleshData();
};


#endif //EXPRESSMANAGEMENTSYSTEM_MYEXPRESSES_H
