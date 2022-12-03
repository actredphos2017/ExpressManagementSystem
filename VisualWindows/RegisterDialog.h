//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_REGISTERDIALOG_H
#define EXPRESSMANAGEMENTSYSTEM_REGISTERDIALOG_H

#include "../GlobalAttribute.h"

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>

class RegisterDialog : public QDialog{

    Q_OBJECT

private:
    QLabel* regTypeTitle;
    QLabel* userNameTitle;
    QLabel* phoneNumTitle;
    QLabel* passwordTitle;
    QLabel* checkPasswordTitle;
    QLabel* permissionInfo;

    QLineEdit* userNameLine;
    QLineEdit* phoneNumLine;
    QLineEdit* passwordLine;
    QLineEdit* checkPasswordLine;

    QRadioButton* waiterType;
    QRadioButton* customerType;

    QPushButton* permissionCheck;
    QPushButton* registerBtn;
    QPushButton* backBtn;

    void initItem();
    void initConnect();
    string permissionCode;

signals:
    void pushBackBtn();
    void toAuthenticate();


public slots:
    void comeBack();
    void toRegister();
    void goToAuthenticate();
    void backToLogin();
    void beginRegister();
    void switchToWaiterType();
    void switchToCustomerType();
    void authenticateSuccess(string userName, string permCode);

public:
    RegisterDialog();
};


#endif //EXPRESSMANAGEMENTSYSTEM_REGISTERDIALOG_H
