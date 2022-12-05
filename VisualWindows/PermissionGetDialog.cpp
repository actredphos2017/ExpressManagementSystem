//
// Created by sakunoakarinn on 22-12-3.
//

#include <QLayout>
#include <QMessageBox>

#include "PermissionGetDialog.h"

void PermissionGetDialog::initItem() {
    auto mainLayout = new QVBoxLayout;
    {
        auto fromCodeGroup = new QVBoxLayout;
        {
            fromCode = new QRadioButton(tr("认证码认证"));
            fromCodeGroup->addWidget(fromCode);

            codeLine = new QLineEdit;
            codeLine->setPlaceholderText(tr("认证码"));
            fromCodeGroup->addWidget(codeLine);
        }
        mainLayout->addLayout(fromCodeGroup);

        auto fromAccountGroup = new QVBoxLayout;
        {
            fromAccount = new QRadioButton(tr("管理员账号认证"));
            fromAccountGroup->addWidget(fromAccount);

            userNameOrPhoneNumLine = new QLineEdit;
            userNameOrPhoneNumLine->setPlaceholderText(tr("用户名或手机号"));
            fromAccountGroup->addWidget(userNameOrPhoneNumLine);

            passwordLine = new QLineEdit;
            passwordLine->setPlaceholderText(tr("密码"));
            fromAccountGroup->addWidget(passwordLine);
        }
        mainLayout->addLayout(fromAccountGroup);

        auto BtnGroup = new QHBoxLayout;
        {
            authenticateBtn = new QPushButton(tr("认证"));
            BtnGroup->addWidget(authenticateBtn);

            backBtn = new QPushButton(tr("返回"));
            BtnGroup->addWidget(backBtn);
        }
        mainLayout->addLayout(BtnGroup);
    }
    setLayout(mainLayout);
}

PermissionGetDialog::PermissionGetDialog() {
    initItem();
    initConnect();
    fromCode->setChecked(true);
    switchToCode();
}

void PermissionGetDialog::initConnect() {
    connect(fromCode,
            SIGNAL(clicked()),
            this,
            SLOT(switchToCode()));

    connect(fromAccount,
            SIGNAL(clicked()),
            this,
            SLOT(switchToAccount()));

    connect(backBtn,
            SIGNAL(clicked()),
            this,
            SLOT(backToRegister()));

    connect(authenticateBtn,
            SIGNAL(clicked()),
            this,
            SLOT(beginAuthenticate()));
}

void PermissionGetDialog::toAuthenticate() {
    show();
}

void PermissionGetDialog::backToRegister() {
    close();
    emit comeBack();
}

void PermissionGetDialog::switchToCode() {
    codeLine->setEnabled(true);
    userNameOrPhoneNumLine->setEnabled(false);
    passwordLine->setEnabled(false);
}

void PermissionGetDialog::switchToAccount() {
    codeLine->setEnabled(false);
    userNameOrPhoneNumLine->setEnabled(true);
    passwordLine->setEnabled(true);
}

void PermissionGetDialog::beginAuthenticate() {
    if(fromCode->isChecked()) {
        if (codeLine->text().isEmpty()){
            QMessageBox::information(this, tr("提示"), tr("请输入认证码"));
            return;
        }
        string code = codeLine->text().toStdString();
        string userName = Sakuno::databaseEntrance->checkPermissionCode(code);
        if (userName.empty()){
            QMessageBox::information(this, tr("提示"), tr("认证失败"));
            return;
        }
        QMessageBox::information(this, tr("提示"), tr("认证成功"));
        emit getPermissionCode(userName, code);
    }
    else if(fromAccount->isChecked()){
        if (userNameOrPhoneNumLine->text().isEmpty() ||
            passwordLine->text().isEmpty()){
            QMessageBox::information(this, tr("提示"), tr("请填满输入框"));
            return;
        }
        AccountInfo accoInfo;
        if(userNameOrPhoneNumLine->text()[0].isNumber())
            accoInfo.setWaiterAccount("",
                                      userNameOrPhoneNumLine->text().toStdString(),
                                      passwordLine->text().toStdString());
        else if(userNameOrPhoneNumLine->text()[0].isLetter())
            accoInfo.setWaiterAccount(userNameOrPhoneNumLine->text().toStdString(),
                                      passwordLine->text().toStdString());
        else{
            QMessageBox::information(this, tr("提示"), tr("输入值不合法"));
            return;
        }
        stringstream errorSs;
        string code = Sakuno::databaseEntrance->getPermissionCode(accoInfo, errorSs);
        if(code.empty()){
            QMessageBox::information(this, tr("提示"), tr(errorSs.str().c_str()));
            return;
        }
        QMessageBox::information(this, tr("提示"), tr("认证成功"));
        backToRegister();
        emit getPermissionCode(userNameOrPhoneNumLine->text().toStdString(), code);
    }
}
