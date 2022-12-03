//
// Created by sakunoakarinn on 22-12-3.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_PERMISSIONGETDIALOG_H
#define EXPRESSMANAGEMENTSYSTEM_PERMISSIONGETDIALOG_H

#include "../GlobalAttribute.h"

#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>

class PermissionGetDialog : public QDialog{

    Q_OBJECT

private:

    QLineEdit* codeLine;

    QLineEdit* userNameOrPhoneNumLine;
    QLineEdit* passwordLine;

    QRadioButton* fromCode;
    QRadioButton* fromAccount;

    QPushButton* authenticateBtn;
    QPushButton* backBtn;

    void initItem();
    void initConnect();

signals:

    void getPermissionCode(string, string);
    void comeBack();

public slots:

    void toAuthenticate();
    void switchToCode();
    void switchToAccount();
    void beginAuthenticate();
    void backToRegister();

public:
    PermissionGetDialog();
};


#endif //EXPRESSMANAGEMENTSYSTEM_PERMISSIONGETDIALOG_H
