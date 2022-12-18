//
// Created by sakuno on 22-12-17.
//


#include "WaiterExpressEditWindow.h"
#include "ui_WaiterExpressEditWindow.h"



WaiterExpressEditWindow::WaiterExpressEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaiterExpressEditWindow) {
    ui->setupUi(this);
}

WaiterExpressEditWindow::~WaiterExpressEditWindow() {
    delete ui;
}

void WaiterExpressEditWindow::initItems() {

}

void WaiterExpressEditWindow::showAllExpress() {
    show();
}

void WaiterExpressEditWindow::showDayExpress() {
    show();
}

void WaiterExpressEditWindow::initConnects() {

}

void WaiterExpressEditWindow::fleshTable() {
    ui->expressTable->clear();
    ui->expressTable->setRowCount();
    QStringList hList;
    hList << "订单号" << "快递公司" << "接收者姓名" << "接收者手机号" << "接收者地址" << "接收者邮编"
          << "发送者姓名" << "发送者手机号" << "发送者地址" << "发送者邮编" << "快件重量" << "入库时间" << "是否取出";

}