//
// Created by sakuno on 22-12-19.
//

#include <QMessageBox>
#include "AccountEditWindow.h"
#include "ui_AccountEditWindow.h"

AccountEditWindow::AccountEditWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::AccountEditWindow) {
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("用户编辑");
    initItem();
    initConnect();
}

AccountEditWindow::~AccountEditWindow() {
    delete ui;
}

void AccountEditWindow::toManageAccount() {
    fleshData();
    show();
}

void AccountEditWindow::fleshData() {
    stringstream errorSs;
    viewAccount = typeAccounts(*selectAccounts(
            *Sakuno::databaseEntrance->getAllAccounts(errorSs),
            !ui->searchLine->text().isEmpty(),
            ui->searchLine->text().toStdString()),
                   !(ui->typeBox->currentText() == "全部"),
                   ui->typeBox->currentText() == "管理员" ? Waiter : Customer);
    if(viewAccount->empty() && !errorSs.str().empty()){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }

    QStringList hList;
    hList << "用户名" << "手机号" << "密码" << "是否为管理员";
    ui->accountTable->clear();
    ui->accountTable->setRowCount(viewAccount->size());
    ui->accountTable->setColumnCount(hList.size());
    ui->accountTable->setHorizontalHeaderLabels(hList);
    ui->accountTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0; i < hList.size(); i ++)
        ui->accountTable->setColumnWidth(i, viewAccount->size());
    int rowI = 0;
    for(auto it : *viewAccount){
        ui->accountTable->setItem(rowI, 0, new QTableWidgetItem(it.userName.c_str()));
        ui->accountTable->setItem(rowI, 1, new QTableWidgetItem(it.phoneNumber.c_str()));
        ui->accountTable->setItem(rowI, 2, new QTableWidgetItem(it.password.c_str()));
        ui->accountTable->setItem(rowI, 3, new QTableWidgetItem(it.accountType == Waiter ? "是" : "否"));
        rowI ++;
    }
}

void AccountEditWindow::initItem() {
    QStringList itemList;
    itemList << "全部" << "用户" << "管理员";
    ui->typeBox->addItems(itemList);
    editWin = new AccountEdit(this);
}

void AccountEditWindow::initConnect() {
    connect(ui->editBtn,
            SIGNAL(clicked()),
            this,
            SLOT(prepareEditAccount()));
    connect(editWin,
            SIGNAL(doneEdit(AccountInfo *)),
            this,
            SLOT(finishEdit(AccountInfo *)));
    connect(ui->addBtn,
            SIGNAL(clicked()),
            editWin,
            SLOT(toAddAccount()));
    connect(ui->deleteBtn,
            SIGNAL(clicked()),
            this,
            SLOT(deleteAccount()));
    connect(editWin,
            SIGNAL(closeWindow()),
            this,
            SLOT(cancelEdit()));
    connect(ui->searchBtn,
            SIGNAL(clicked()),
            this,
            SLOT(fleshData()));
}

void AccountEditWindow::prepareEditAccount() {
    if(ui->accountTable->currentRow() < 0)
        return;
    stringstream errorSs;
    editTargetAccount = Sakuno::databaseEntrance->getAccount(
            ui->accountTable->item(ui->accountTable->currentRow(), 0)->text().toStdString(),
            ui->accountTable->item(ui->accountTable->currentRow(), 1)->text().toStdString(),
            errorSs
            );
    if(!editTargetAccount){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    emit editAccount(editTargetAccount);
}

void AccountEditWindow::finishEdit(AccountInfo *newInfo) {
    if(!editTargetAccount){
        AccountGroup singleAccount;
        singleAccount.push_back(*newInfo);
        stringstream errorSs;
        if(!Sakuno::databaseEntrance->insertAccount(singleAccount, errorSs)){
            QMessageBox::information(this, "提示", errorSs.str().c_str());
            return;
        }
        QMessageBox::information(this, "提示", "添加成功");
    }else{
        stringstream errorSs;
        if(!Sakuno::databaseEntrance->updateSingleAccount(*editTargetAccount, *newInfo, errorSs)){
            QMessageBox::information(this, "提示", errorSs.str().c_str());
            return;
        }
        delete editTargetAccount;
        editTargetAccount = nullptr;
        QMessageBox::information(this, "提示", "修改成功");
    }
    fleshData();
}

void AccountEditWindow::deleteAccount() {
    if(ui->accountTable->currentRow() < 0)
        return;
    AccountInfo account;
    account.userName = ui->accountTable->item(ui->accountTable->currentRow(), 0)->text().toStdString();
    account.phoneNumber = ui->accountTable->item(ui->accountTable->currentRow(), 1)->text().toStdString();
    account.password = ui->accountTable->item(ui->accountTable->currentRow(), 2)->text().toStdString();
    account.accountType = ui->accountTable->item(ui->accountTable->currentRow(), 3)->text() == "是" ? Waiter : Customer;
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->deleteSingleAccount(account, errorSs)){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    fleshData();
}

void AccountEditWindow::cancelEdit() {
    qDebug() << "hello";
    delete editTargetAccount;
    editTargetAccount = nullptr;
    fleshData();
}
