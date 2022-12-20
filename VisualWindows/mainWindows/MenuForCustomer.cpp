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
    settingWin = new Settings(this);
    setWindowTitle("我的快件");
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
    customerPackage = typeOrder(*Sakuno::databaseEntrance->getCustomerOrders(Sakuno::onlineAccount->phoneNumber, errorSs),
                                true,
                                false);
    if(customerPackage->empty())
        QMessageBox::information(this, tr("提示"), tr(errorSs.str().c_str()));
    for(const auto& it : *customerPackage)
        addQuickTag(tempLayout, new PickupQuickTag(it.senderName.c_str(), it.recipentName.c_str(), it.pickCode.c_str()));
    auto widget = new QWidget;
    widget->setLayout(tempLayout);
    ui->quickPickupCodeArea->setWidget(widget);
}


void MenuForCustomer::initItems(){
    expressWindow = new MyExpresses(this);
    addShadow(ui->pickupMessage);
    addShadow(ui->btnGroupBox);
    addShadow(ui->greetGroupBox);
}

void MenuForCustomer::initConnect(){
    connect(ui->settings,
            SIGNAL(clicked()),
            settingWin,
            SLOT(toSetting()));
    connect(ui->allExpresses,
            SIGNAL(clicked()),
            expressWindow,
            SLOT(toSeeAllPackages()));
    connect(ui->nowadaysExpresses,
            SIGNAL(clicked()),
            expressWindow,
            SLOT(toSeeNowadaysPackages()));
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
    initDynamicItems();
    show();
}

void MenuForCustomer::initDynamicItems() {
    initQuickBox();
    ui->greetsUsername->setText((
            Sakuno::onlineAccount->userName.empty() ?
            Sakuno::onlineAccount->phoneNumber :
            Sakuno::onlineAccount->userName).c_str());
    ui->packageNumLabel->setText(tr(to_string(customerPackage->size()).c_str()) + "件");
}