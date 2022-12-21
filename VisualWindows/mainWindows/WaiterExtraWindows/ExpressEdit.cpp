//
// Created by sakuno on 22-12-18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExpressEdit.h" resolved

#include <QHBoxLayout>
#include "ExpressEdit.h"


ExpressEdit::ExpressEdit(QWidget *parent) :
    QDialog(parent) {
    initItem();
    initConnect();
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("快件设置");
}

ExpressEdit::~ExpressEdit() {

}

void ExpressEdit::initItem() {
    auto mainLayout = new QVBoxLayout;
    {
        auto editLayout = new QHBoxLayout;
        {
            auto titleLayout = new QVBoxLayout;
            {
                trackNumTitle = new QLabel(tr("订单号"));
                titleLayout->addWidget(trackNumTitle);

                compTitle = new QLabel(tr("快递公司"));
                titleLayout->addWidget(compTitle);

                reciNameTitle = new QLabel(tr("收件人姓名"));
                titleLayout->addWidget(reciNameTitle);

                reciPhoneNumTitle = new QLabel(tr("收件人电话"));
                titleLayout->addWidget(reciPhoneNumTitle);

                reciLocTitle = new QLabel(tr("收件人地址"));
                titleLayout->addWidget(reciLocTitle);

                reciPostTitle = new QLabel(tr("收件人邮编"));
                titleLayout->addWidget(reciPostTitle);

                sendNameTitle = new QLabel(tr("发件人姓名"));
                titleLayout->addWidget(sendNameTitle);

                sendPhoneNumTitle = new QLabel(tr("发件人电话"));
                titleLayout->addWidget(sendPhoneNumTitle);

                sendLocTitle = new QLabel(tr("发件人地址"));
                titleLayout->addWidget(sendLocTitle);

                sendPostTitle = new QLabel(tr("发件人邮编"));
                titleLayout->addWidget(sendPostTitle);

                itemWeightTitle = new QLabel(tr("物品重量"));
                titleLayout->addWidget(itemWeightTitle);

                pickCodeTitle = new QLabel(tr("取件码"));
                titleLayout->addWidget(pickCodeTitle);

                warehousingTimeTitle = new QLabel(tr("入库时间"));
                titleLayout->addWidget(warehousingTimeTitle);

            }
            editLayout->addLayout(titleLayout);

            auto enterLayout = new QVBoxLayout;
            {
                trackNumLine = new QLineEdit;
                enterLayout->addWidget(trackNumLine);

                compLine = new QLineEdit;
                enterLayout->addWidget(compLine);

                reciNameLine = new QLineEdit;
                enterLayout->addWidget(reciNameLine);

                reciPhoneNumLine = new QLineEdit;
                enterLayout->addWidget(reciPhoneNumLine);

                reciLocLine = new QLineEdit;
                enterLayout->addWidget(reciLocLine);

                reciPostLine = new QLineEdit;
                enterLayout->addWidget(reciPostLine);

                sendNameLine = new QLineEdit;
                enterLayout->addWidget(sendNameLine);

                sendPhoneNumLine = new QLineEdit;
                enterLayout->addWidget(sendPhoneNumLine);

                sendLocLine = new QLineEdit;
                enterLayout->addWidget(sendLocLine);

                sendPostLine = new QLineEdit;
                enterLayout->addWidget(sendPostLine);

                itemWeightBox = new QDoubleSpinBox;
                enterLayout->addWidget(itemWeightBox);

                pickCodeLine = new QLineEdit;
                pickCodeLine->setPlaceholderText("不填则自动生成");
                enterLayout->addWidget(pickCodeLine);

                warehousingTimeEdit = new QDateTimeEdit(QDateTime(QDate::currentDate(), QTime::currentTime()));
                enterLayout->addWidget(warehousingTimeEdit);


            }
            editLayout->addLayout(enterLayout);
        }
        mainLayout->addLayout(editLayout);
        auto btnLayout = new QHBoxLayout;
        {
            btnLayout->addStretch();

            ifTakenBox = new QCheckBox("是否已取");
            btnLayout->addWidget(ifTakenBox);

            yesBtn = new QPushButton("确定");
            btnLayout->addWidget(yesBtn);
        }
        mainLayout->addLayout(btnLayout);
    }
    setLayout(mainLayout);
}

void ExpressEdit::editOrder(OrderInfo *order) {
    trackNumLine->setText(order->trackNumber.c_str());
    compLine->setText(order->company.c_str());
    reciNameLine->setText(order->recipentName.c_str());
    reciPhoneNumLine->setText(order->recipentPhoneNum.c_str());
    reciLocLine->setText(order->recipentLocation.c_str());
    reciPostLine->setText(to_string(order->recipentPost).c_str());
    sendNameLine->setText(order->senderName.c_str());
    sendPhoneNumLine->setText(order->senderPhoneNum.c_str());
    sendLocLine->setText(order->senderLocation.c_str());
    sendPostLine->setText(to_string(order->senderPost).c_str());
    itemWeightBox->setValue(order->itemWeight);
    warehousingTimeEdit->setDateTime(
            QDateTime(QDate(order->warehousingTime->year,order->warehousingTime->month,order->warehousingTime->mDay),
                      QTime(order->warehousingTime->hour, order->warehousingTime->min, order->warehousingTime->second)));
    pickCodeLine->setText(order->pickCode.c_str());
    ifTakenBox->setChecked(order->hasBeenTaken);
    show();
}

void ExpressEdit::addOrder() {
    trackNumLine->setText("");
    compLine->setText("");
    reciNameLine->setText("");
    reciPhoneNumLine->setText("");
    reciLocLine->setText("");
    reciPostLine->setText("");
    sendNameLine->setText("");
    sendPhoneNumLine->setText("");
    sendLocLine->setText("");
    sendPostLine->setText("");
    itemWeightBox->setValue(1.0);
    warehousingTimeEdit->setDateTime(QDateTime::currentDateTime());
    pickCodeLine->setText("");
    ifTakenBox->setChecked(false);
    show();
}

void ExpressEdit::initConnect() {
    connect(yesBtn, SIGNAL(clicked()), this, SLOT(pushOkButton()));
}

void ExpressEdit::pushOkButton() {
    OrderInfo* resOrder = new OrderInfo;
    resOrder->trackNumber = trackNumLine->text().toStdString();
    resOrder->company = compLine->text().toStdString();
    resOrder->recipentName = reciNameLine->text().toStdString();
    resOrder->recipentPhoneNum = reciPhoneNumLine->text().toStdString();
    resOrder->recipentLocation = reciLocLine->text().toStdString();
    resOrder->recipentPost = Sakuno::toInt(reciPostLine->text().toStdString());
    resOrder->senderName = sendNameLine->text().toStdString();
    resOrder->senderPhoneNum = sendPhoneNumLine->text().toStdString();
    resOrder->senderLocation = sendLocLine->text().toStdString();
    resOrder->senderPost = Sakuno::toInt(sendPostLine->text().toStdString());
    resOrder->pickCode = pickCodeLine->text().toStdString();
    resOrder->itemWeight = itemWeightBox->value();
    resOrder->warehousingTime = new Sakuno::Time();
    resOrder->warehousingTime->year = warehousingTimeEdit->dateTime().date().year();
    resOrder->warehousingTime->month = warehousingTimeEdit->dateTime().date().month();
    resOrder->warehousingTime->mDay = warehousingTimeEdit->dateTime().date().day();
    resOrder->warehousingTime->hour = warehousingTimeEdit->dateTime().time().hour();
    resOrder->warehousingTime->min = warehousingTimeEdit->dateTime().time().minute();
    resOrder->warehousingTime->second = warehousingTimeEdit->dateTime().time().second();
    resOrder->hasBeenTaken = ifTakenBox->isChecked();
    emit doneEdit(new OrderInfo(Sakuno::databaseEntrance->spawnTakenCode(*resOrder)));
    close();
}

void ExpressEdit::closeEvent(QCloseEvent *event) {
    emit closeWindow();
    QDialog::closeEvent(event);
}
