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
    dayResAndPick = new CircleProgressBar(32, 100);
    allResAndPick = new CircleProgressBar(920, 1000);
    ui->statusLayout->addWidget(dayResAndPick);
    ui->statusLayout->addSpacing(20);
    ui->statusLayout->addWidget(allResAndPick);
    setShadow(dayResAndPick);
    setShadow(allResAndPick);
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