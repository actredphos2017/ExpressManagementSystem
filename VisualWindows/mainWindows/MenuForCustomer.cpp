#include "MenuForCustomer.h"
#include "ui_MenuForCustomer.h"
#include "../userObjects/PickupQuickTag.h"

#include <QLayout>
#include <QGraphicsEffect>
#include <QMessageBox>

MenuForCustomer::MenuForCustomer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuForCustomer)
{
    ui->setupUi(this);
    initItems();
    initConnect();
}

MenuForCustomer::~MenuForCustomer()
{
    delete ui;
}

void MenuForCustomer::initQuickBox(){
    auto tempLayout = new QVBoxLayout;
    PickupQuickTag* Test;

    stringstream errorSs;
    customerPackage = Sakuno::databaseEntrance->getCustomerOrders(Sakuno::onlineAccount->phoneNumber, errorSs);
    if(customerPackage->empty())
        QMessageBox::information(this, tr("提示"), tr(errorSs.str().c_str()));
    for(const auto& it : *customerPackage)
        addQuickTag(tempLayout, new PickupQuickTag(it.senderName.c_str(), it.recipentName.c_str(), it.pickCode.c_str()));
    auto widget = new QWidget;
    widget->setLayout(tempLayout);
    ui->quickPickupCodeArea->setWidget(widget);
}

void MenuForCustomer::initItems(){
    settingWin = new Settings(this);
    addShadow(ui->pickupMessage);
    addShadow(ui->btnGroupBox);
    addShadow(ui->greetGroupBox);
    addShadow(ui->infoGroupBox);
}

void MenuForCustomer::initConnect(){
    connect(settingWin,
            SIGNAL(toLeave()),
            this,
            SLOT(close()));
};

void MenuForCustomer::addShadow(QWidget* widget){
    auto effect = new QGraphicsDropShadowEffect;
    effect->setColor("#666666");
    effect->setBlurRadius(8);
    effect->setOffset(2, 2);
    widget->setGraphicsEffect(effect);
}

void MenuForCustomer::addQuickTag(QVBoxLayout* quickTagsGroup,PickupQuickTag* quickTag){
    quickTagsGroup->addWidget(quickTag);
    addShadow(quickTag);
}

void MenuForCustomer::loginSuccess() {
    initQuickBox();
    this->show();
}
