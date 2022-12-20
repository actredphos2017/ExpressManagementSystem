//
// Created by sakuno on 22-12-19.
//

#include <QLayout>
#include <QMessageBox>
#include "AccountEdit.h"

AccountEdit::AccountEdit(QWidget* parent):
    QDialog(parent){
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("设置账号");
    initItem();
    initConnect();
}

void AccountEdit::initItem() {
    auto mainLayout = new QVBoxLayout;
    {
        auto enterLayout = new QHBoxLayout;
        {
            auto titleLayout = new QVBoxLayout;
            {
                userNameTitle = new QLabel(tr("用户名"));
                titleLayout->addWidget(userNameTitle);

                phoneNumTitle = new QLabel(tr("手机号"));
                titleLayout->addWidget(phoneNumTitle);

                passwordTitle = new QLabel(tr("密码"));
                titleLayout->addWidget(passwordTitle);
            }
            enterLayout->addLayout(titleLayout);

            auto lineLayout = new QVBoxLayout;
            {
                userNameLine = new QLineEdit;
                lineLayout->addWidget(userNameLine);

                phoneNumLine = new QLineEdit;
                lineLayout->addWidget(phoneNumLine);

                passwordLine  = new QLineEdit;
                lineLayout->addWidget(passwordLine);
            }
            enterLayout->addLayout(lineLayout);
        }
        mainLayout->addLayout(enterLayout);

        auto btnLayout = new QHBoxLayout;
        {
            btnLayout->addStretch();

            ifWaiterBox = new QCheckBox(tr("管理员"));
            btnLayout->addWidget(ifWaiterBox);

            yesBtn = new QPushButton("确定");
            btnLayout->addWidget(yesBtn);
        }
        mainLayout->addLayout(btnLayout);
    }
    setLayout(mainLayout);
}

void AccountEdit::initConnect() {
    connect(parent(),
            SIGNAL(editAccount(AccountInfo *)),
            this,
            SLOT(toEditAccount(AccountInfo *)));
    connect(yesBtn,
            SIGNAL(clicked()),
            this,
            SLOT(clickYes())
            );
}

void AccountEdit::toEditAccount(AccountInfo *account) {
    userNameLine->setText(account->userName.c_str());
    phoneNumLine->setText(account->phoneNumber.c_str());
    passwordLine->setText(account->password.c_str());
    ifWaiterBox->setChecked(account->accountType == Waiter);
    oldAccount = account;
    show();
}

void AccountEdit::toAddAccount() {
    userNameLine->setText("");
    phoneNumLine->setText("");
    passwordLine->setText("");
    ifWaiterBox->setChecked(false);
    oldAccount = nullptr;
    show();
}

void AccountEdit::clickYes() {
    if(passwordLine->text().isEmpty()){
        QMessageBox::information(this, "提示", "密码为空！");
        return;
    }
    auto doneAccount = new AccountInfo;
    doneAccount->accountType = ifWaiterBox->isChecked() ? Waiter : Customer;
    doneAccount->phoneNumber = phoneNumLine->text().toStdString();
    doneAccount->userName = userNameLine->text().toStdString();
    doneAccount->password = userNameLine->text().toStdString();
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->checkPrepareAccount(*doneAccount, errorSs, oldAccount)){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        delete doneAccount;
        return;
    }
    emit doneEdit(doneAccount);
    close();
}

void AccountEdit::closeEvent(QCloseEvent *event) {
    emit closeWindow();
    QDialog::closeEvent(event);
}
