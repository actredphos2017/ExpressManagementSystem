//
// Created by sakuno on 22-12-20.
//

#include <QVBoxLayout>
#include "Settings.h"

Settings::Settings(QWidget *parent):
    QDialog(parent){
    setWindowModality(Qt::WindowModal);
    setWindowTitle("账号设置");
    initItem();
    initConnect();
}

void Settings::initItem() {
    auto mainLayout = new QVBoxLayout;
    {
        settingStatusLabel = new QLabel("");
        mainLayout->addWidget(settingStatusLabel);

        leaveBtn = new QPushButton("退出登录");
        mainLayout->addWidget(leaveBtn);

        resetPasswordBtn = new QPushButton("重置密码");
        mainLayout->addWidget(resetPasswordBtn);

        unregisterBtn = new QPushButton("注销账号");
        mainLayout->addWidget(unregisterBtn);
    }
    setLayout(mainLayout);

    resetPasswordWin = new ResetPassword(this);
}

void Settings::initDynamicItem(){
    settingStatusLabel->setText(tr("当前账号: ") + Sakuno::onlineAccount->userName.c_str());
    unregisterBtn->setDisabled(Sakuno::onlineAccount->userName == "root");
}

void Settings::initConnect() {
    connect(resetPasswordBtn,
            SIGNAL(clicked()),
            resetPasswordWin,
            SLOT(toResetPassword()));
    connect(leaveBtn,
            SIGNAL(clicked()),
            this,
            SLOT(prepareLeave()));
    connect(unregisterBtn,
            SIGNAL(clicked()),
            this,
            SLOT(prepareUnregister()));
}

void Settings::toSetting() {
    initDynamicItem();
    show();
}

void Settings::prepareLeave() {
    if(QMessageBox::information(this, "提示", "确定退出登录？", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Cancel)
        return;
    emit toLeave();
    delete Sakuno::onlineAccount;
    Sakuno::onlineAccount = nullptr;
}

void Settings::prepareUnregister() {
    if(QMessageBox::warning(this, "提示", "确定注销此账号？", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Cancel)
        return;
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->deleteSingleAccount(*Sakuno::onlineAccount, errorSs, true)){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    emit toLeave();
    delete Sakuno::onlineAccount;
    Sakuno::onlineAccount = nullptr;
}