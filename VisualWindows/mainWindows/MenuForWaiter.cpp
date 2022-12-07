#include "MenuForWaiter.h"
#include "ui_MenuForWaiter.h"

MenuForWaiter::MenuForWaiter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuForWaiter)
{
    ui->setupUi(this);
}

MenuForWaiter::~MenuForWaiter()
{
    delete ui;
}

void MenuForWaiter::loginSuccess() {
    show();
}