//
// Created by sakuno on 22-12-20.
//

#include "MyExpresses.h"
#include "ui_MyExpresses.h"


MyExpresses::MyExpresses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyExpresses) {
    ui->setupUi(this);
    setWindowTitle("我的快件");
    setWindowModality(Qt::WindowModal);
    setFixedSize(1500, 912);
    initItem();
    initConnect();
}

MyExpresses::~MyExpresses() {
    delete ui;
}

void MyExpresses::initItem() {
    QStringList typeList;
    typeList << "全部" << "已取" << "未取";
    ui->typeBox->addItems(typeList);
}

void MyExpresses::fleshData() {
    stringstream errorSs;
    viewOrders =
            Sakuno::databaseEntrance->getCustomerOrders(
                    Sakuno::onlineAccount->phoneNumber,
                    errorSs,
                    false,
                    !selectAllExpress,
                    Sakuno::Time(QDateTime::currentDateTime()));
    if(!viewOrders){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    if(viewOrders->empty()){
        QMessageBox::information(this, "提示", "暂无快件");
        close();
        delete viewOrders;
        return;
    }
    QStringList hList;
    hList << "订单号" << "取件码" << "快递公司" << "接收者姓名" << "接收者手机号" << "接收者地址" << "接收者邮编"
          << "发送者姓名" << "发送者手机号" << "发送者地址" << "发送者邮编" << "快件重量" << "入库时间" << "是否取出";
    ui->packagesTable->clear();
    ui->packagesTable->setRowCount(viewOrders->size());
    ui->packagesTable->setColumnCount(hList.size());
    ui->packagesTable->setHorizontalHeaderLabels(hList);
    ui->packagesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0; i < hList.size(); i ++)
        ui->packagesTable->setColumnWidth(i, viewOrders->size());
    int rowI = 0;
    for(auto it : *viewOrders){
        ui->packagesTable->setItem(rowI, 0, new QTableWidgetItem(it.trackNumber.c_str()));
        ui->packagesTable->setItem(rowI, 1, new QTableWidgetItem(it.pickCode.c_str()));
        ui->packagesTable->setItem(rowI, 2, new QTableWidgetItem(it.company.c_str()));
        ui->packagesTable->setItem(rowI, 3, new QTableWidgetItem(it.recipentName.c_str()));
        ui->packagesTable->setItem(rowI, 4, new QTableWidgetItem(it.recipentPhoneNum.c_str()));
        ui->packagesTable->setItem(rowI, 5, new QTableWidgetItem(it.recipentLocation.c_str()));
        ui->packagesTable->setItem(rowI, 6, new QTableWidgetItem(to_string(it.recipentPost).c_str()));
        ui->packagesTable->setItem(rowI, 7, new QTableWidgetItem(it.senderName.c_str()));
        ui->packagesTable->setItem(rowI, 8, new QTableWidgetItem(it.senderPhoneNum.c_str()));
        ui->packagesTable->setItem(rowI, 9, new QTableWidgetItem(it.senderLocation.c_str()));
        ui->packagesTable->setItem(rowI, 10, new QTableWidgetItem(to_string(it.senderPost).c_str()));
        ui->packagesTable->setItem(rowI, 11, new QTableWidgetItem(to_string(it.itemWeight).c_str()));
        ui->packagesTable->setItem(rowI, 12, new QTableWidgetItem(Sakuno::Time(*(it.warehousingTime)).s_date().c_str()));
        ui->packagesTable->setItem(rowI, 13, new QTableWidgetItem(it.hasBeenTaken ? "是" : "否"));
        rowI ++;
    }
}

void MyExpresses::initConnect() {

}

void MyExpresses::toSeeAllPackages() {
    selectAllExpress = true;
    fleshData();
    show();
}

void MyExpresses::toSeeNowadaysPackages() {
    selectAllExpress = false;
    fleshData();
    show();
}