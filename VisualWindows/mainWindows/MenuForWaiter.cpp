#include "MenuForWaiter.h"
#include "ui_MenuForWaiter.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QSpacerItem>

MenuForWaiter::MenuForWaiter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuForWaiter)
{
    ui->setupUi(this);
    initItems();
    initConnects();
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
    show();
}

void MenuForWaiter::initItems() {
    auto dayRes = new QVBoxLayout;
    dayRes->setAlignment(Qt::AlignCenter);
    dayResAndPick = new CircleProgressBar(32, 100);
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
    allResAndPick = new CircleProgressBar(920, 1000);
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
    setShadow(dayResAndPick);
    setShadow(allResAndPick);
    setShadow(ui->statusGroup);
    setShadow(ui->quickPickupGroup);
    setShadow(ui->addOrderBtn);
    setShadow(ui->manageAccountBtn);
    setShadow(ui->settingBtn);

    expressWindow = new WaiterExpressEditWindow(this);
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
}
