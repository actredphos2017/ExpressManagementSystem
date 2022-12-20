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
    unregisterBtn->setCheckable(!(Sakuno::onlineAccount->userName == "root"));
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