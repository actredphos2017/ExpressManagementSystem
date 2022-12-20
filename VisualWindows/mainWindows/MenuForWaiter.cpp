#include "MenuForWaiter.h"
#include "ui_MenuForWaiter.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QSpacerItem>
#include <QMessageBox>

MenuForWaiter::MenuForWaiter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuForWaiter)
{
    ui->setupUi(this);
    settingWin = new Settings(this);
    setMaximumSize(790, 320);
    setMinimumSize(790, 320);
}

void MenuForWaiter::setShadow(QWidget* widget){
    auto effect = new QGraphicsDropShadowEffect;
    effect->setColor("#666666");
    effect->setBlurRadius(12);
    effect->setOffset(5);
    widget->setGraphicsEffect(effect);
}

MenuForWaiter::~MenuForWaiter()
{
    delete ui;
}

void MenuForWaiter::loginSuccess() {
    initItems();
    initConnects();
    setWindowTitle(tr("欢迎 ") + Sakuno::onlineAccount->userName.c_str());
    show();
}

void MenuForWaiter::initItems() {
    auto dayRes = new QVBoxLayout;
    dayRes->setAlignment(Qt::AlignCenter);
    auto thisDate = new Sakuno::Time;
    thisDate->year = QDate::currentDate().year();
    thisDate->month = QDate::currentDate().month();
    thisDate->mDay = QDate::currentDate().day();
    taken_wareInfo = Sakuno::databaseEntrance->warehousing_takenMap(thisDate);
    dayResAndPick = new CircleProgressBar(taken_wareInfo[0], taken_wareInfo[1]);
    dayResBtn = new QPushButton(tr("当日取出/当日入库"));
    dayResBtn->setMaximumHeight(30);
    dayResBtn->setMinimumHeight(30);
    dayResBtn->setStyleSheet(
            "QPushButton{"
            "   border: outsize;"
            "   border-radius: 15px;"
            "   background-color: transparent;"
            "}"
            ""
            "QPushButton:hover{"
            "   background-color: white;"
            "}"
    );
    dayRes->addWidget(dayResAndPick);
    dayRes->addWidget(dayResBtn);

    auto allRes = new QVBoxLayout;
    allRes->setAlignment(Qt::AlignCenter);
    allResAndPick = new CircleProgressBar(taken_wareInfo[2], taken_wareInfo[3]);
    allResBtn = new QPushButton(tr("总取出/总入库"));
    allResBtn->setMinimumHeight(30);
    allResBtn->setMaximumHeight(30);
    allResBtn->setStyleSheet(
            "QPushButton{"
            "   border: outsize;"
            "   border-radius: 15px;"
            "   background-color: transparent;"
            "}"
            ""
            "QPushButton:hover{"
            "   background-color: white;"
            "}"
    );
    allRes->addWidget(allResAndPick);
    allRes->addWidget(allResBtn);
    ui->statusLayout->addLayout(dayRes);
    ui->statusLayout->addSpacing(10);
    ui->statusLayout->addLayout(allRes);
    ui->pickBtn->setDisabled(true);
    ui->pickBtn->setText("请输入取件码");
    setShadow(dayResAndPick);
    setShadow(allResAndPick);
    setShadow(ui->statusGroup);
    setShadow(ui->quickPickupGroup);
    setShadow(ui->addOrderBtn);
    setShadow(ui->manageAccountBtn);
    setShadow(ui->settingBtn);
    expressWindow = new WaiterExpressEditWindow(this);
    accountWindow = new AccountEditWindow(this);

}

void MenuForWaiter::initConnects() {
    connect(allResBtn,
            SIGNAL(clicked()),
            expressWindow,
            SLOT(showAllExpress()));
    connect(dayResBtn,
            SIGNAL(clicked()),
            expressWindow,
            SLOT(showDayExpress()));
    connect(ui->codeLine,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(quickInfo(const QString &)));
    connect(ui->pickBtn,
            SIGNAL(clicked()),
            this,
            SLOT(setPick()));
    connect(ui->manageAccountBtn,
            SIGNAL(clicked()),
            accountWindow,
            SLOT(toManageAccount()));
    connect(ui->settingBtn,
            SIGNAL(clicked()),
            settingWin,
            SLOT(toSetting()));
    connect(settingWin,
            SIGNAL(toLeave()),
            this,
            SLOT(close()));
}

void MenuForWaiter::updateProgresBar() {
    qDebug() << "Hello";
    auto thisDate = new Sakuno::Time;
    thisDate->year = QDate::currentDate().year();
    thisDate->month = QDate::currentDate().month();
    thisDate->mDay = QDate::currentDate().day();
    taken_wareInfo = Sakuno::databaseEntrance->warehousing_takenMap(thisDate);
    dayResAndPick->updateData(taken_wareInfo[0], taken_wareInfo[1]);
    allResAndPick->updateData(taken_wareInfo[2], taken_wareInfo[3]);
}

void MenuForWaiter::quickInfo(const QString & quickLineText) {
    quickOrder = nullptr;
    ui->pickBtn->setDisabled(true);
    ui->pickBtn->setText("请输入取件码");
    ui->recipentNameLabel->setText("");
    ui->recipentPhoneLabel->setText("");
    ui->trackNumLabel->setText("");
    if(quickLineText.size() < 9)
        return;
    quickOrder = Sakuno::databaseEntrance->getQuickOrder(quickLineText.toStdString());
    if(!quickOrder){
        ui->pickBtn->setText("无记录");
        ui->pickBtn->setDisabled(true);
        ui->recipentNameLabel->setText("");
        ui->recipentPhoneLabel->setText("");
        ui->trackNumLabel->setText("");
    }else{
        ui->recipentNameLabel->setText(quickOrder->recipentName.c_str());
        ui->recipentPhoneLabel->setText(quickOrder->recipentPhoneNum.c_str());
        ui->trackNumLabel->setText(quickOrder->trackNumber.c_str());
        if(!quickOrder->hasBeenTaken){
            ui->pickBtn->setDisabled(false);
            ui->pickBtn->setText("确认取件");
        }else{
            ui->pickBtn->setDisabled(true);
            ui->pickBtn->setText("该件已经被取走");
        }
    }
}

void MenuForWaiter::setPick() {
    if(quickOrder == nullptr){
        QMessageBox::information(this, "提示", "未知错误");
        return;
    }
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->setHasTaken(*quickOrder, true, errorSs)){
        QMessageBox::information(this, "提示", errorSs.str().c_str());
        return;
    }
    ui->pickBtn->setDisabled(true);
    ui->pickBtn->setText("该件已经被取走");
    updateProgresBar();
}

