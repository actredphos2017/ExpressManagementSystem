//
// Created by sakuno on 22-12-20.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_SETTINGS_H
#define EXPRESSMANAGEMENTSYSTEM_SETTINGS_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include "../../GlobalAttribute.h"
#include "ResetPassword.h"

class Settings : public QDialog{
Q_OBJECT

private:
    QLabel* settingStatusLabel{};

    QPushButton* leaveBtn{};
    QPushButton* resetPasswordBtn{};
    QPushButton* unregisterBtn{};
    ResetPassword* resetPasswordWin{};

    void initItem();
    void initDynamicItem();
    void initConnect();

public:
    explicit Settings(QWidget* parent = nullptr);

public slots:
    void toSetting();
    void prepareLeave();
    void prepareUnregister();

};


#endif //EXPRESSMANAGEMENTSYSTEM_SETTINGS_H
