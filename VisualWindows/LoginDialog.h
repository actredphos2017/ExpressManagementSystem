//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_LOGINDIALOG_H
#define EXPRESSMANAGEMENTSYSTEM_LOGINDIALOG_H

#include "../GlobalAttribute.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

#include "userObjects/ClickableLabel.h"

using namespace Qt;

class LoginDialog : public QDialog {

    Q_OBJECT

private:
    DatabaseStatus* databaseEntrance{};

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
    QPushButton* databaseConnectRetry{};

    void initItems();
    void initConnect();


signals:
    void switchToDatabaseOption();
    void pushDatabaseConfBtn();
    void pushRegisterBtn();
    void checkSaveDBInfo();

public slots:
    void toRegister();
    void toConfigDatabase();
    void comeBack();
    void signIn();
    void checkResult();
    void checkSave();

public:
    LoginDialog();
    void init();
};


#endif //EXPRESSMANAGEMENTSYSTEM_LOGINDIALOG_H
