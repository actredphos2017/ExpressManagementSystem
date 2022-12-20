//
// Created by sakuno on 22-12-19.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_ACCOUNTEDIT_H
#define EXPRESSMANAGEMENTSYSTEM_ACCOUNTEDIT_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include "../../../GlobalAttribute.h"

class AccountEdit : public QDialog {
Q_OBJECT

private:

    QLabel* userNameTitle{};
    QLabel* phoneNumTitle{};
    QLabel* passwordTitle{};

    QLineEdit* userNameLine{};
    QLineEdit* phoneNumLine{};
    QLineEdit* passwordLine{};

    QCheckBox* ifWaiterBox{};

    QPushButton* yesBtn{};
    QPushButton* cancelBtn{};

    AccountInfo* oldAccount{};

    void initItem();
    void initConnect();

public:
    explicit AccountEdit(QWidget* parent = nullptr);

public slots:
    void toEditAccount(AccountInfo*);
    void toAddAccount();
    void clickYes();

signals:
    void doneEdit(AccountInfo*);
};


#endif //EXPRESSMANAGEMENTSYSTEM_ACCOUNTEDIT_H
