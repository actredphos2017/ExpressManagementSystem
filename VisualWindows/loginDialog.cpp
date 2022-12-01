//
// Created by sakunoakarinn on 22-11-30.
//

#include "../globalAttribute.h"

#include "loginDialog.h"

#include <QLayout>
#include <iostream>
#include <QDebug>

#include "databaseOption.h"

loginDialog::loginDialog(databaseStatus* databaseEntrance): 
databaseEntrance(databaseEntrance) {
    iniItems();
    iniConnect();
}

void loginDialog::iniItems() {
    auto mainLayout = new QVBoxLayout;
    {
        auto databaseOptionLayout = new QHBoxLayout;
        {
            auto databaseStatus = new QVBoxLayout;
            {
                databaseStatusTitle = new QLabel(tr("数据库状态："));
                auto tempFon = databaseStatusTitle->font();
                tempFon.setBold(true);
                databaseStatusTitle->setFont(tempFon);
                databaseStatus->addWidget(databaseStatusTitle);

                databaseStatusInfo = new QLabel(tr("检查中……"));
                databaseStatus->addWidget(databaseStatusInfo);
            }
            databaseOptionLayout->addLayout(databaseStatus);

            databaseOptionEntrance = new QPushButton(tr("配置连接"));
            databaseOptionLayout->addWidget(databaseOptionEntrance);
        }
        mainLayout->addLayout(databaseOptionLayout);

        auto enterLayout = new QHBoxLayout;
        {
            auto lineEditGroup = new QVBoxLayout;
            {
                auto userNameGroup = new QHBoxLayout;
                {
                    userNameEdit = new QLineEdit;
                    userNameEdit->setPlaceholderText(tr("用户名/手机号"));
                    userNameGroup->addWidget(userNameEdit);
                }
                lineEditGroup->addLayout(userNameGroup);

                auto passwordGroup = new QHBoxLayout;
                {
                    passwordEdit = new QLineEdit;
                    passwordEdit->setEchoMode(QLineEdit::Password);
                    passwordEdit->setPlaceholderText(tr("密码"));
                    passwordGroup->addWidget(passwordEdit);
                }
                lineEditGroup->addLayout(passwordGroup);
            }
            enterLayout->addLayout(lineEditGroup);

            auto checkBoxGroup = new QVBoxLayout;
            {
                rememberPassword = new QCheckBox(tr("记住密码"));
                checkBoxGroup->addWidget(rememberPassword);

                autoLogin = new QCheckBox(tr("自动登录"));
                checkBoxGroup->addWidget(autoLogin);
            }
            enterLayout->addLayout(checkBoxGroup);
        }
        mainLayout->addLayout(enterLayout);

        auto registerGroup = new QHBoxLayout;
        {
            registerText = new QLabel(tr("还没有账号？立即"));
            registerGroup->addWidget(registerText);

            registerBtn = new ClickableLabel(tr("注册"));
            registerBtn->setStyleSheet("color: #add8e6");
            registerGroup->addWidget(registerBtn);
        }
        registerGroup->setAlignment(AlignLeft);
        mainLayout->addLayout(registerGroup);

        auto buttonGroup = new QHBoxLayout;
        {
            loginBtn = new QPushButton(tr("登录"));
            buttonGroup->addWidget(loginBtn);

            cancelBtn = new QPushButton(tr("退出"));
            buttonGroup->addWidget(cancelBtn);
        }
        mainLayout->addLayout(buttonGroup);
    }

    setLayout(mainLayout);
    setWindowTitle(tr("快件管理系统"));
}

void loginDialog::iniConnect() {
    connect(
        databaseOptionEntrance,
        SIGNAL(clicked()), 
        this, 
        SLOT(toConfigDatabase())
    ); //数据库配置

    connect(
        cancelBtn, 
        SIGNAL(clicked()), 
        this, 
        SLOT(close())
    ); //退出

    connect(
        registerBtn, 
        SIGNAL(clicked()), 
        this, 
        SLOT(hw())
    ); //注册

    connect(
        loginBtn, 
        SIGNAL(clicked()), 
        this, 
        SLOT(hw())
    ); //登录
}

void loginDialog::toConfigDatabase(){
    this->hide();
    emit pushDatabaseConfBtn();
}

void loginDialog::toRegister(){
    this->hide();
    emit pushRegisterBtn();
}

void loginDialog::comeBack(){
    this->show();
}