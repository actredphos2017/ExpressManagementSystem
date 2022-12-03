//
// Created by sakunoakarinn on 22-11-30.
//

#include "../GlobalAttribute.h"

#include "LoginDialog.h"

#include <QLayout>
#include <QMessageBox>

#include "DatabaseOption.h"

LoginDialog::LoginDialog(){
    initItems();
    initConnect();
}

void LoginDialog::initItems() {
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

            auto configConnect = new QVBoxLayout;
            {
                databaseOptionEntrance = new QPushButton(tr("配置连接"));
                configConnect->addWidget(databaseOptionEntrance);

                databaseConnectRetry = new QPushButton(tr("重试连接"));
                configConnect->addWidget(databaseConnectRetry);
            }
            databaseOptionLayout->addLayout(configConnect);
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

void LoginDialog::initConnect() {
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
        SLOT(toRegister())
    ); //注册

    connect(
        loginBtn, 
        SIGNAL(clicked()), 
        this, 
        SLOT(signIn())
    ); //登录

    connect(
        databaseConnectRetry,
        SIGNAL(clicked()),
        this,
        SLOT(checkSave())
    );
}

void LoginDialog::toConfigDatabase(){
    this->hide();
    emit pushDatabaseConfBtn();
}

void LoginDialog::toRegister(){
    this->hide();
    emit pushRegisterBtn();
}

void LoginDialog::comeBack(){
    qDebug() << Sakuno::connectSuccess;
    if(!Sakuno::connectSuccess)
        databaseStatusInfo->setText(tr("未连接"));
    else
        databaseStatusInfo->setText(tr("已连接到 ") + Sakuno::dbInfo->connectName.c_str());
    show();
}

void LoginDialog::signIn() {

}

void LoginDialog::init() {
    show();
    checkSave();
}

void LoginDialog::checkSave() {
    databaseStatusInfo->setText("检查中……");
    emit checkSaveDBInfo();
}

void LoginDialog::checkResult() {
    if(!Sakuno::connectSuccess){
        databaseStatusInfo->setText(tr("未连接"));
        QMessageBox::information(this,tr("提示"),tr("未连接到数据库！请重试或重新配置连接！"));
    }
    else
        databaseStatusInfo->setText(tr("已连接到 ") + Sakuno::dbInfo->connectName.c_str());

}
