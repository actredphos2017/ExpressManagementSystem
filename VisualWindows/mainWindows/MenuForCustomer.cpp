#include "MenuForCustomer.h"
#include "ui_MenuForCustomer.h"
#include "../userObjects/PickupQuickTag.h"

#include <QLayout>
#include <QGroupBox>
#include <QGraphicsEffect>

MenuForCustomer::MenuForCustomer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuForCustomer)
{
    ui->setupUi(this);

    QVBoxLayout* tempLayout = new QVBoxLayout;
    PickupQuickTag* Test;
    QGraphicsDropShadowEffect* effect;
    int y = 10;
    for(int i = 0; i < 10; i ++){
        Test = new PickupQuickTag("戴先生", "郭先生", "00-0-0000");
        tempLayout->addWidget(Test);
        effect = new QGraphicsDropShadowEffect;
        effect->setColor("#666666");
        effect->setBlurRadius(8);
        Test->setGraphicsEffect(effect);
    }
    QWidget* widget = new QWidget;
    widget->setLayout(tempLayout);
    ui->scrollArea->setWidget(widget);
    //ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

MenuForCustomer::~MenuForCustomer()
{
    delete ui;
}
