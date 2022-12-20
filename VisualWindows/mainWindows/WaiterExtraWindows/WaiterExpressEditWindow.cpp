//
// Created by sakuno on 22-12-17.
//


#include "WaiterExpressEditWindow.h"
#include "ui_WaiterExpressEditWindow.h"

#include <QMessageBox>

WaiterExpressEditWindow::WaiterExpressEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaiterExpressEditWindow) {
    ui->setupUi(this);
    setFixedSize(1500, 927);
    initItems();
    initConnects();
}

WaiterExpressEditWindow::~WaiterExpressEditWindow() {
    delete ui;
}

void WaiterExpressEditWindow::initItems() {
    editWin = new ExpressEdit;
}

void WaiterExpressEditWindow::showAllExpress() {
    selectAllExpress = true;
    show();
    fleshTable();
}

void WaiterExpressEditWindow::showDayExpress() {
    selectAllExpress = false;
    show();
    fleshTable();
}

void WaiterExpressEditWindow::initConnects() {
    connect(ui->addBtn, SIGNAL(clicked()), editWin, SLOT(addOrder()));
    connect(ui->editBtn, SIGNAL(clicked()), this, SLOT(prepareEdit()));
    connect(this, SIGNAL(toEdit(OrderInfo *)), editWin, SLOT(editOrder(OrderInfo *)));
    connect(editWin, SIGNAL(doneEdit(OrderInfo *)), this, SLOT(pushEdit(OrderInfo *)));
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect(ui->comeBackBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->comeBackBtn, SIGNAL(clicked()), parent(), SLOT(updateProgresBar()));
}

void WaiterExpressEditWindow::fleshTable() {
    if(selectAllExpress)
        viewOrders = Sakuno::databaseEntrance->getAllOrders();
    else {
        auto thisDate = new Sakuno::Time;
        thisDate->year = QDate::currentDate().year();
        thisDate->month = QDate::currentDate().month();
        thisDate->mDay = QDate::currentDate().day();
        viewOrders = Sakuno::databaseEntrance->getDayOrders(thisDate);
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
    ui->expressTable->clear();
    ui->expressTable->setRowCount(viewOrders->size());
    ui->expressTable->setColumnCount(hList.size());
    ui->expressTable->setHorizontalHeaderLabels(hList);
    ui->expressTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0; i < hList.size(); i ++)
        ui->expressTable->setColumnWidth(i, viewOrders->size());
    int rowI = 0;
    for(auto it : *viewOrders){
        ui->expressTable->setItem(rowI, 0, new QTableWidgetItem(it.trackNumber.c_str()));
        ui->expressTable->setItem(rowI, 1, new QTableWidgetItem(it.pickCode.c_str()));
        ui->expressTable->setItem(rowI, 2, new QTableWidgetItem(it.company.c_str()));
        ui->expressTable->setItem(rowI, 3, new QTableWidgetItem(it.recipentName.c_str()));
        ui->expressTable->setItem(rowI, 4, new QTableWidgetItem(it.recipentPhoneNum.c_str()));
        ui->expressTable->setItem(rowI, 5, new QTableWidgetItem(it.recipentLocation.c_str()));
        ui->expressTable->setItem(rowI, 6, new QTableWidgetItem(to_string(it.recipentPost).c_str()));
        ui->expressTable->setItem(rowI, 7, new QTableWidgetItem(it.senderName.c_str()));
        ui->expressTable->setItem(rowI, 8, new QTableWidgetItem(it.senderPhoneNum.c_str()));
        ui->expressTable->setItem(rowI, 9, new QTableWidgetItem(it.senderLocation.c_str()));
        ui->expressTable->setItem(rowI, 10, new QTableWidgetItem(to_string(it.senderPost).c_str()));
        ui->expressTable->setItem(rowI, 11, new QTableWidgetItem(to_string(it.itemWeight).c_str()));
        ui->expressTable->setItem(rowI, 12, new QTableWidgetItem(Sakuno::Time(*(it.warehousingTime)).s_date().c_str()));
        ui->expressTable->setItem(rowI, 13, new QTableWidgetItem(it.hasBeenTaken ? "是" : "否"));
        rowI ++;
    }
}

void WaiterExpressEditWindow::setHasTaken(bool ifTaken) {
    if(ui->expressTable->currentRow() == -1)
        return;
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->setHasTaken((*viewOrders)[ui->expressTable->currentRow()] , ifTaken, errorSs)){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    fleshTable();
}

void WaiterExpressEditWindow::prepareEdit() {
    stringstream errorSs;
    OrderInfo* prepareOrder = Sakuno::databaseEntrance->getOrder(ui->expressTable->item(ui->expressTable->currentRow(), 0)->text().toStdString(), errorSs);
    if(!prepareOrder){
        QMessageBox::information(this, tr("提示"), errorSs.str().c_str());
        return;
    }
    editingOrderTrackNum = prepareOrder->trackNumber;
    emit toEdit(prepareOrder);
}

void WaiterExpressEditWindow::pushEdit(OrderInfo *order) {
    stringstream errorSs;
    if(editingOrderTrackNum.empty()){
        OrderGroup singleOrder;
        singleOrder.push_back(*order);
        if(!Sakuno::databaseEntrance->insertOrder(singleOrder, errorSs)){
            QMessageBox::information(this, "提示", errorSs.str().c_str());
            return;
        }
        QMessageBox::information(this, "提示", "插入成功");
    }else{
        if(!Sakuno::databaseEntrance->updateSingleOrder(editingOrderTrackNum, *order, errorSs)){
            qDebug() << errorSs.str().c_str();
            QMessageBox::information(this, "提示", errorSs.str().c_str());
            return;
        }
        editingOrderTrackNum.clear();
        QMessageBox::information(this, "提示", "修改成功");
    }
    fleshTable();
}

void WaiterExpressEditWindow::removeItem() {
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->deleteSingleOrder(ui->expressTable->item(ui->expressTable->currentRow(), 0)->text().toStdString(), errorSs)){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    fleshTable();
}
