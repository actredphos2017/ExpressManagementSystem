//
// Created by sakunoakarinn on 22-11-30.
//

#include "../globalAttribute.h"

#include "databaseOption.h"

#include <QLayout>

void databaseOption::toConfigDatabase() {
    this->show();
}

void databaseOption::iniItem() {
    auto mainLayout = new QVBoxLayout;
    {
        auto connectStatus = new QHBoxLayout;
        connectStatus->setAlignment(Qt::AlignLeft);
        {
            connectStatusTitle = new QLabel(tr("连接状态："));
            QFont tempFont = connectStatusTitle->font();
            tempFont.setBold(true);
            connectStatusTitle->setFont(tempFont);
            connectStatus->addWidget(connectStatusTitle);

            connectStatusContent = new QLabel(tr("正在检查……"));
            connectStatus->addWidget(connectStatusContent);
        }
        mainLayout->addLayout(connectStatus);

        auto choosePath = new QVBoxLayout;
        {
            auto cptLayout = new QHBoxLayout;
            cptLayout->setAlignment(Qt::AlignLeft);
            {
                choosePathTitle = new QLabel(tr("选择连接源获取方式："));
                cptLayout->addWidget(choosePathTitle);
            }
            choosePath->addLayout(cptLayout);

            auto choosePathTitleButtonGroup = new QHBoxLayout;
            choosePathTitleButtonGroup->setAlignment(Qt::AlignLeft);
            {
                fromFile = new QRadioButton(tr("来自文件"));
                choosePathTitleButtonGroup->addWidget(fromFile);

                chooseFileBtn = new QPushButton(tr("选择文件"));
                choosePathTitleButtonGroup->addWidget(chooseFileBtn);
            }
            choosePath->addLayout(choosePathTitleButtonGroup);

            fromEnter = new QRadioButton(tr("手动输入"));
            choosePath->addWidget(fromEnter);
        }
        mainLayout->addLayout(choosePath);

        auto manualInputSpace = new QHBoxLayout;
        {
            auto enterTitles = new QVBoxLayout;
            enterTitles->setAlignment(Qt::AlignRight);
            {
                connectNameTitle = new QLabel(tr("连接名称"));
                enterTitles->addWidget(connectNameTitle);

                hostNameTitle = new QLabel(tr("连接地址"));
                enterTitles->addWidget(hostNameTitle);

                userNameTitle = new QLabel(tr("用户名"));
                enterTitles->addWidget(userNameTitle);

                passwordTitle = new QLabel(tr("密码"));
                enterTitles->addWidget(passwordTitle);
            }
            manualInputSpace->addLayout(enterTitles);

            auto enterSpace = new QVBoxLayout;
            {
                connectNameLine = new QLineEdit;
                enterSpace->addWidget(connectNameLine);

                hostNameLine = new QLineEdit;
                enterSpace->addWidget(hostNameLine);

                userNameLine = new QLineEdit;
                enterSpace->addWidget(userNameLine);

                passwordLine = new QLineEdit;
                enterSpace->addWidget(passwordLine);
            }
            manualInputSpace->addLayout(enterSpace);
        }
        mainLayout->addLayout(manualInputSpace);

        auto btnGroup = new QHBoxLayout;
        {
            checkBtn = new QPushButton("检查连接");
            btnGroup->addWidget(checkBtn);

            backBtn = new QPushButton("返回");
            btnGroup->addWidget(backBtn);
        }
        mainLayout->addLayout(btnGroup);
    }
    setLayout(mainLayout);
    setWindowTitle(tr("连接配置"));
}

databaseOption::databaseOption() {
    iniItem();
}