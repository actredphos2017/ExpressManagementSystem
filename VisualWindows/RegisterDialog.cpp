//
// Created by sakunoakarinn on 22-11-30.
//

#include "../GlobalAttribute.h"

#include "RegisterDialog.h"

#include <QLayout>
#include <QMessageBox>

RegisterDialog::RegisterDialog() {
    initItem();
    initConnect();


    customerType->setChecked(true);
    switchToCustomerType();

    customerType->setChecked(true);
}

void RegisterDialog::initItem() {
    auto mainLayout = new QVBoxLayout;
    {
        auto regType = new QVBoxLayout;
        {
            regTypeTitle = new QLabel(tr("用户类型"));
            regType->addWidget(regTypeTitle);

            auto regTypeChoice = new QVBoxLayout;
            {
                customerType = new QRadioButton(tr("用户"));
                regTypeChoice->addWidget(customerType);

                auto waiterTypeGroup = new QHBoxLayout;
                {
                    waiterType = new QRadioButton(tr("服务员"));
                    waiterTypeGroup->addWidget(waiterType);

                    auto permissionGroup = new QVBoxLayout;
                    {
                        permissionCheck = new QPushButton(tr("开始认证"));
                        waiterTypeGroup->addWidget(permissionCheck);

                        permissionInfo = new QLabel(tr("未认证"));
                        waiterTypeGroup->addWidget(permissionInfo);
                    }
                    waiterTypeGroup->addLayout(permissionGroup);
                }
                regTypeChoice->addLayout(waiterTypeGroup);
            }
            regType->addLayout(regTypeChoice);
        }
        mainLayout->addLayout(regType);

        auto userInfoEnterSpace = new QHBoxLayout;
        {
            auto titleGroup = new QVBoxLayout;
            titleGroup->setAlignment(Qt::AlignRight);
            {
                userNameTitle = new QLabel(tr("用户名"));
                titleGroup->addWidget(userNameTitle);

                phoneNumTitle = new QLabel(tr("手机号"));
                titleGroup->addWidget(phoneNumTitle);

                passwordTitle = new QLabel(tr("密码"));
                titleGroup->addWidget(passwordTitle);

                checkPasswordTitle = new QLabel(tr("确认密码"));
                titleGroup->addWidget(checkPasswordTitle);
            }
            userInfoEnterSpace->addLayout(titleGroup);

            auto lineGroup = new QVBoxLayout;
            {
                userNameLine = new QLineEdit;
                userNameLine->setPlaceholderText(tr("用户可选填写"));
                lineGroup->addWidget(userNameLine);

                phoneNumLine = new QLineEdit;
                phoneNumLine->setPlaceholderText(tr("服务员可选填写"));
                lineGroup->addWidget(phoneNumLine);

                passwordLine = new QLineEdit;
                lineGroup->addWidget(passwordLine);

                checkPasswordLine = new QLineEdit;
                lineGroup->addWidget(checkPasswordLine);
            }
            userInfoEnterSpace->addLayout(lineGroup);
        }
        mainLayout->addLayout(userInfoEnterSpace);

        auto buttonGroup = new QHBoxLayout;
        {
            registerBtn = new QPushButton(tr("注册"));
            buttonGroup->addWidget(registerBtn);

            backBtn = new QPushButton(tr("返回"));
            buttonGroup->addWidget(backBtn);
        }
        mainLayout->addLayout(buttonGroup);
    }
    setWindowTitle(tr("注册账户"));
    setLayout(mainLayout);
}

void RegisterDialog::toRegister() {
    show();
}

void RegisterDialog::initConnect() {
    connect(backBtn,
            SIGNAL(clicked()),
            this,
            SLOT(backToLogin()));

    connect(registerBtn,
            SIGNAL(clicked()),
            this,
            SLOT(beginRegister()));

    connect(permissionCheck,
            SIGNAL(clicked()),
            this,
            SLOT(goToAuthenticate()));

    connect(waiterType,
            SIGNAL(clicked()),
            this,
            SLOT(switchToWaiterType()));

    connect(customerType,
            SIGNAL(clicked()),
            this,
            SLOT(switchToCustomerType()));
}

void RegisterDialog::backToLogin() {
    close();
    emit pushBackBtn();
}

void RegisterDialog::beginRegister() {
    if(customerType->isChecked()){
        if (phoneNumLine->text().isEmpty() ||
            passwordLine->text().isEmpty() ||
            checkPasswordLine->text().isEmpty()){
            QMessageBox::information(this,tr("提示"),tr("请填满必选信息框！"));
            return;
        }
        if(passwordLine->text() != checkPasswordLine->text()){
            QMessageBox::information(this,tr("提示"),tr("密码与确认密码不一致！"));
            return;
        }
        AccountInfo prepareAccount;
        prepareAccount.setCustomerAccount(userNameLine->text().toStdString(),
                                          phoneNumLine->text().toStdString(),
                                          passwordLine->text().toStdString());
        stringstream errorReport;
        if(!Sakuno::databaseEntrance->registerUserAccount(prepareAccount, errorReport)){
            QMessageBox::information(this,tr("提示"),tr(errorReport.str().c_str()));
            return;
        }
        QMessageBox::information(this,tr("提示"),tr("注册成功"));
    }else if(waiterType->isChecked()){
        if(permissionCode.empty()){
            QMessageBox::information(this,tr("提示"),tr("尚未获取认证"));
            return;
        }
        if (userNameLine->text().isEmpty() ||
            passwordLine->text().isEmpty() ||
            checkPasswordLine->text().isEmpty()){
            QMessageBox::information(this,tr("提示"),tr("请填满必选信息框！"));
            return;
        }
        if(passwordLine->text() != checkPasswordLine->text()){
            QMessageBox::information(this,tr("提示"),tr("密码与确认密码不一致！"));
            return;
        }
        AccountInfo prepareAccount;
        prepareAccount.setWaiterAccount(userNameLine->text().toStdString(),
                                          phoneNumLine->text().toStdString(),
                                          passwordLine->text().toStdString());
        stringstream errorReport;
        if(!Sakuno::databaseEntrance->registerWaiterAccount(prepareAccount, permissionCode, errorReport)){
            QMessageBox::information(this,tr("提示"),tr(errorReport.str().c_str()));
            return;
        }
        QMessageBox::information(this,tr("提示"),tr("注册成功"));
    }
}

void RegisterDialog::switchToWaiterType() {
    permissionCheck->setEnabled(true);
    if(permissionCode.empty()){
        QMessageBox::information(this,tr("提示"),tr("需要其他服务员账号或认证码提供认证"));
        userNameLine->setEnabled(false);
        phoneNumLine->setEnabled(false);
        passwordLine->setEnabled(false);
        checkPasswordLine->setEnabled(false);
    }
}

void RegisterDialog::switchToCustomerType() {
    permissionCheck->setEnabled(false);
    userNameLine->setEnabled(true);
    phoneNumLine->setEnabled(true);
    passwordLine->setEnabled(true);
    checkPasswordLine->setEnabled(true);
}

void RegisterDialog::comeBack() {
    show();
}

void RegisterDialog::goToAuthenticate() {
    hide();
    emit toAuthenticate();
}

void RegisterDialog::authenticateSuccess(string userName, string permCode) {
    permissionInfo->setText(tr("以获取到 ") + userName.c_str() + " 的认证");
    permissionCode = permCode;
    userNameLine->setEnabled(true);
    phoneNumLine->setEnabled(true);
    passwordLine->setEnabled(true);
    checkPasswordLine->setEnabled(true);
}
