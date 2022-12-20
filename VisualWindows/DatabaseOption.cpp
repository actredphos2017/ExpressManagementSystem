//
// Created by sakunoakarinn on 22-11-30.
//

#include "../GlobalAttribute.h"

#include "DatabaseOption.h"

#include <QLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

void DatabaseOption::toConfigDatabase() {
    show();
}

void DatabaseOption::initItem() {
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

            auto choosePathTitleButtonGroup = new QVBoxLayout;
            choosePathTitleButtonGroup->setAlignment(Qt::AlignTop);
            {
                auto choosePathTitleButton = new QHBoxLayout;
                {
                    fromFile = new QRadioButton(tr("来自文件"));
                    choosePathTitleButton->addWidget(fromFile);

                    selectFileBtn = new QPushButton(tr("选择文件"));
                    choosePathTitleButton->addWidget(selectFileBtn);
                }
                choosePathTitleButtonGroup->addLayout(choosePathTitleButton);

                auto selectedFile = new QHBoxLayout;
                selectedFile->setAlignment(Qt::AlignLeft);
                {
                    selectedFileTitle = new QLabel(tr("已选中数据库: "));
                    selectedFile->addWidget(selectedFileTitle);

                    selectedFileName = new QLabel(tr("未选择"));
                    selectedFile->addWidget(selectedFileName);
                }
                choosePathTitleButtonGroup->addLayout(selectedFile);

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

        saveFile = new QPushButton(tr("保存数据到本地"));
        mainLayout->addWidget(saveFile);

        auto btnGroup = new QHBoxLayout;
        {
            checkBtn = new QPushButton("检查连接");
            btnGroup->addWidget(checkBtn);

            backBtn = new QPushButton("返回");
            btnGroup->addWidget(backBtn);
        }
        mainLayout->addLayout(btnGroup);
    }


    setMinimumSize(400, 400);
    setMaximumSize(300, 400);

    fromFile->setChecked(true);
    switchToFile(true);

    setLayout(mainLayout);
}

void DatabaseOption::initConnect() {
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToLogin()));
    connect(fromEnter, SIGNAL(clicked(bool)), this, SLOT(switchToEnter(bool)));
    connect(fromFile, SIGNAL(clicked(bool)), this, SLOT(switchToFile(bool)));
    connect(selectFileBtn, SIGNAL(clicked()), this, SLOT(startChooseFile()));
    connect(saveFile, SIGNAL(clicked()), this, SLOT(saveToLocal()));
    connect(checkBtn, SIGNAL(clicked()), this, SLOT(checkDatabase()));
}

DatabaseOption::DatabaseOption(QWidget* parent) :
    QDialog(parent){
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("连接配置"));
    setWindowFlags(Qt::FramelessWindowHint);
    initItem();
    initConnect();
}

void DatabaseOption::backToLogin() {
    this->close();
    emit pushBackBtn();
}

void DatabaseOption::switchToEnter(bool isSelected) {
    if(!isSelected) return;
    selectFileBtn->setEnabled(false);
    connectNameLine->setEnabled(true);
    hostNameLine->setEnabled(true);
    userNameLine->setEnabled(true);
    passwordLine->setEnabled(true);
    saveFile->setEnabled(true);
}

void DatabaseOption::switchToFile(bool isSelected) {
    if(!isSelected) return;
    selectFileBtn->setEnabled(true);
    connectNameLine->setEnabled(false);
    hostNameLine->setEnabled(false);
    userNameLine->setEnabled(false);
    passwordLine->setEnabled(false);
    saveFile->setEnabled(false);
}

void DatabaseOption::startChooseFile() {
    QString prepareFilePath = QFileDialog::getOpenFileName(this,"Save Path",QDir::homePath(),(QString)"数据库连接数据文件 (*" + DB_INFO_FILENAME + ");;All Files (*)");
    if(prepareFilePath.isEmpty()){
        connectFailed();
        filePath.clear();
        return;
    }
    ifstream iF;
    iF.open(prepareFilePath.toStdString());
    bool connectFailed = false;
    if(iF.good())
        connectFailed = !Sakuno::dbInfo->read(iF);
    iF.close();
    if(connectFailed){
        QMessageBox::information(this, tr("提示"), tr("输入值错误！请检查文件格式！"));
        return;
    }else{
        Sakuno::haveDBInfo = true;
        filePath = prepareFilePath;
    }
    selectedFileName->setText(tr(Sakuno::dbInfo->connectName.c_str()));
}

void DatabaseOption::saveToLocal() {
    if (connectNameLine->text().isEmpty() ||
        hostNameLine->text().isEmpty() ||
        userNameLine->text().isEmpty() ||
        passwordLine->text().isEmpty()){
        QMessageBox::information(this,tr("提示"),tr("请填满信息框！"));
        return;
    }
    Sakuno::dbInfo->read(hostNameLine->text().toStdString(),
                userNameLine->text().toStdString(),
                passwordLine->text().toStdString(),
                connectNameLine->text().toStdString());
    QString savePath =
            QFileDialog::getSaveFileName(this,"保存路径",QDir::homePath(),(QString)"数据库连接数据文件 (*" + DB_INFO_FILENAME + ");;All Files (*)");
    if(savePath.isEmpty())
        return;
    if(Sakuno::getFileType(savePath.toStdString()).empty())
        savePath += DB_INFO_FILENAME;
    ofstream oF;
    oF.open(savePath.toStdString());
    if(oF.good()){
        Sakuno::dbInfo->write(oF);
        QMessageBox::information(this,tr("提示"),tr("保存成功！"));
    }else
        QMessageBox::information(this,tr("提示"),tr("保存失败！"));
}

void DatabaseOption::checkDatabase() {
    if(fromEnter->isChecked()){
        if (connectNameLine->text().isEmpty() ||
            hostNameLine->text().isEmpty() ||
            userNameLine->text().isEmpty() ||
            passwordLine->text().isEmpty()){
            QMessageBox::information(this,tr("提示"),tr("请填满信息框！"));
            return;
        }
        Sakuno::dbInfo->read(hostNameLine->text().toStdString(),
                    userNameLine->text().toStdString(),
                    passwordLine->text().toStdString(),
                    connectNameLine->text().toStdString());
    }else if(fromFile->isChecked()){
        if(filePath.isEmpty()){
            QMessageBox::information(this,tr("提示"),tr("未选择文件！"));
            return;
        }
    }

    stringstream errorSS;
    if(!Sakuno::databaseEntrance->connect(*Sakuno::dbInfo, errorSS)){
        QMessageBox::information(this,tr("提示"),tr(errorSS.str().c_str()));
        connectFailed();
        return;
    }else{
        connectStatusContent->setText(tr("已连接到 ") + tr(Sakuno::dbInfo->connectName.c_str()));
        createSave();
        Sakuno::connectSuccess = true;
        QMessageBox::information(this,tr("提示"),tr("连接成功"));
    }
}

void DatabaseOption::createSave() {
    if(!Sakuno::haveDBInfo)
        return;
    string sFilePath(QDir::homePath().toStdString() + PROGRAM_DATA_SAVE_DIR + "dbInfoSave");
    qDebug() << "Write " << sFilePath.c_str();
    ofstream oF;
    oF.open(sFilePath);
    if(!oF.good())
        return;
    oF << "$DBInfoSave" << endl;
    if(fromFile->isChecked()){
        oF << "fromFile ";
        oF << filePath.toStdString() << endl;
    }
    else if(fromEnter->isChecked()) {
        oF << "fromEnter" << endl;
        oF << connectNameLine->text().toStdString() << endl;
        oF << hostNameLine->text().toStdString() << endl;
        oF << userNameLine->text().toStdString() << endl;
        oF << passwordLine->text().toStdString() << endl;
    }
    oF.close();
}

void DatabaseOption::readSave() {
    ifstream iF;
    string sFilePath(QDir::homePath().toStdString() + PROGRAM_DATA_SAVE_DIR + "dbInfoSave");
    qDebug() << "Read " << sFilePath.c_str();
    iF.open(sFilePath);
    if (!iF.good())
        return;
    string head;
    iF >> head;
    if (head != "$DBInfoSave")
        return;
    string sourceType;
    iF >> sourceType;
    if (sourceType == "fromFile") {
        fromFile->setChecked(true);
        switchToFile(true);
        string prepareFilePath;
        iF >> prepareFilePath;
        iF.close();
        iF.open(prepareFilePath);
        if (!iF.good()) {
            iF.close();
            connectFailed();
            return;
        }
        if (!Sakuno::dbInfo->read(iF)) {
            iF.close();
            return;
        } else {
            Sakuno::haveDBInfo = true;
            Sakuno::databaseEntrance = new DatabaseStatus;
            if (!Sakuno::databaseEntrance->connect(*Sakuno::dbInfo)){
                connectFailed();
                return;
            }
            Sakuno::connectSuccess = true;
            connectStatusContent->setText(tr("已连接到 ") + tr(Sakuno::dbInfo->connectName.c_str()));
            selectedFileName->setText(tr(Sakuno::dbInfo->connectName.c_str()));
            filePath = prepareFilePath.c_str();
        }
    }
    else if (sourceType == "fromEnter") {
        fromEnter->setChecked(true);
        switchToEnter(true);
        string sConnectName, sHostName, sUserName, sPassword;
        iF >> sConnectName >> sHostName >> sUserName >> sPassword;
        connectNameLine->setText(sConnectName.c_str());
        hostNameLine->setText(sHostName.c_str());
        userNameLine->setText(sUserName.c_str());
        passwordLine->setText(sPassword.c_str());
        Sakuno::dbInfo->read(sHostName, sUserName, sPassword, sConnectName);
        Sakuno::haveDBInfo = true;
        if (!Sakuno::databaseEntrance->connect(*Sakuno::dbInfo))
            return;
        Sakuno::connectSuccess = true;
    }
}

void DatabaseOption::checkSave() {
    readSave();
    emit checkFinish();
}



void DatabaseOption::connectFailed() {
    Sakuno::haveDBInfo = false;
    Sakuno::dbInfo = new DatabaseInfo;
    Sakuno::connectSuccess = false;
    Sakuno::databaseEntrance = new DatabaseStatus;
    selectedFileName->setText(tr("未选择"));
    connectStatusContent->setText(tr("未连接"));
}
