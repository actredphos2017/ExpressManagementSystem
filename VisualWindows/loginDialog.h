//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_LOGINDIALOG_H
#define EXPRESSMANAGEMENTSYSTEM_LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

#include "userObjects/ClickableLabel.h"

using namespace Qt;

class loginDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* userNameEdit{};
    QLineEdit* passwordEdit{};
    QCheckBox* rememberPassword{};
    QCheckBox* autoLogin{};
    QPushButton* loginBtn{};
    QPushButton* cancelBtn{};
    QLabel* registerText{};
    ClickableLabel* registerBtn{};
    QLabel* databaseStatusTitle{};
    QLabel* databaseStatusInfo{};
    QPushButton* databaseOptionEntrance{};
    void iniItems();
    void iniConnect();

signals:
    void switchToDatabaseOption();

private slots:
    static void hw();
    void showDatabaseOption();
public:
    loginDialog();
};


#endif //EXPRESSMANAGEMENTSYSTEM_LOGINDIALOG_H
