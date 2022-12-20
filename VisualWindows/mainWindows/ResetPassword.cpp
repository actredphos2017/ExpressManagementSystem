//
// Created by sakuno on 22-12-20.
//

#include "ResetPassword.h"

ResetPassword::ResetPassword(QWidget *parent):
    QDialog(parent){
    setWindowTitle("重置密码");
    setWindowModality(Qt::WindowModal);
    initItem();
    initConnect();
}

void ResetPassword::initItem() {
    auto mainLayout = new QVBoxLayout;
    {
        auto enterLayout = new QHBoxLayout;
        {
            auto titleLayout = new QVBoxLayout;
            {
                oldPasswordTitle = new QLabel("原密码");
                titleLayout->addWidget(oldPasswordTitle);

                newPasswordTitle = new QLabel("新密码");
                titleLayout->addWidget(newPasswordTitle);

                checkPasswordTitle = new QLabel("确认密码");
                titleLayout->addWidget(checkPasswordTitle);
            }
            enterLayout->addLayout(titleLayout);

            auto lineLayout = new QVBoxLayout;
            {
                oldPasswordLine = new QLineEdit;
                lineLayout->addWidget(oldPasswordLine);

                newPasswordLine = new QLineEdit;
                lineLayout->addWidget(newPasswordLine);

                checkPasswordLine = new QLineEdit;
                lineLayout->addWidget(checkPasswordLine);
            }
            enterLayout->addLayout(lineLayout);
        }
        mainLayout->addLayout(enterLayout);

        auto btnLayout = new QHBoxLayout;
        {
            btnLayout->addStretch();

            yesBtn = new QPushButton("确定");
            btnLayout->addWidget(yesBtn);

            cancelBtn = new QPushButton("取消");
            btnLayout->addWidget(cancelBtn);
        }
        mainLayout->addLayout(btnLayout);
    }
    setLayout(mainLayout);
}

void ResetPassword::initConnect() {
    connect(yesBtn,
            SIGNAL(clicked()),
            this,
            SLOT(prepareReset()));
    connect(cancelBtn,
            SIGNAL(clicked()),
            this,
            SLOT(close()));
}

void ResetPassword::toResetPassword() {
    show();
}

void ResetPassword::prepareReset() {
    if(oldPasswordLine->text().toStdString() != Sakuno::onlineAccount->password){
        QMessageBox::information(this, "提示", "原密码错误");
        return;
    }
    if(newPasswordLine->text().isEmpty()){
        QMessageBox::information(this, "提示", "请输入密码");
        return;
    }
    if(newPasswordLine->text() != checkPasswordLine->text()){
        QMessageBox::information(this, "提示", "两次密码输入不一致");
        return;
    }
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->resetPassword(*Sakuno::onlineAccount, newPasswordLine->text().toStdString(), errorSs)){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    Sakuno::onlineAccount->password = newPasswordLine->text().toStdString();
    QMessageBox::information(this, "提示", "密码重置成功");
    close();
}