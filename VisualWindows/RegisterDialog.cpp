//
// Created by sakunoakarinn on 22-11-30.
//

#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"

#include <QMessageBox>
#include <QGraphicsEffect>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    initItem();
    initConnect();
    setWindowFlags(Qt::FramelessWindowHint);
    dragSpaces.push_back(ui->backGround);
    switchToCustomerType();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::setShadow(QWidget *qw, int radius) {
    auto* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(QColor("black"));
    shadowEffect->setBlurRadius(radius);

    qw->setGraphicsEffect(shadowEffect);
}

void RegisterDialog::setBlur(QWidget* qw, int radius){
    auto* blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(radius);
    qw->setGraphicsEffect(blurEffect);
}

void RegisterDialog::initItem() {
    ui->authenicateOffer->setStyleSheet("QLabel{font-size: 12px;color: red;}");
    ui->permissionInfo->setStyleSheet("QLabel{font-size: 12px;color: red;}");

    ui->userNameLine->setPlaceholderText(tr("用户名"));
    ui->phoneNumLine->setPlaceholderText(tr("手机号"));
    ui->passwordLine->setPlaceholderText(tr("密码"));
    ui->checkPasswordLine->setPlaceholderText(tr("确认密码"));

    setShadow(ui->MainSpace, 12);
    setShadow(ui->chooseType, 12);
    setShadow(ui->authenicateGroup, 12);

    setBlur(ui->backGround, 64);
}

void RegisterDialog::toRegister() {
    show();
}

void RegisterDialog::initConnect() {
    connect(ui->backBtn,
            SIGNAL(clicked()),
            this,
            SLOT(backToLogin()));

    connect(ui->registerBtn,
            SIGNAL(clicked()),
            this,
            SLOT(beginRegister()));

    connect(ui->permissionCheck,
            SIGNAL(clicked()),
            this,
            SLOT(goToAuthenticate()));

    connect(ui->waiterType,
            SIGNAL(clicked()),
            this,
            SLOT(switchToWaiterType()));

    connect(ui->customerType,
            SIGNAL(clicked()),
            this,
            SLOT(switchToCustomerType()));

    connect(
            this,
            SIGNAL(toAuthenticate()),
            &authenticateInterface,
            SLOT(toAuthenticate())
    ); //连接注册界面与认证界面

    connect(
            &authenticateInterface,
            SIGNAL(getPermissionCode(string, string)),
            this,
            SLOT(authenticateSuccess(string, string))
    );
}

void RegisterDialog::backToLogin() {
    close();
    emit pushBackBtn();
}

void RegisterDialog::beginRegister() {
    if(ui->customerType->isChecked()){
        if (ui->phoneNumLine->text().isEmpty() ||
                ui->passwordLine->text().isEmpty() ||
                ui->checkPasswordLine->text().isEmpty()){
            QMessageBox::information(this,tr("提示"),tr("请填满必选信息框！"));
            return;
        }
        if(ui->passwordLine->text() != ui->checkPasswordLine->text()){
            QMessageBox::information(this,tr("提示"),tr("密码与确认密码不一致！"));
            return;
        }
        AccountInfo prepareAccount;
        prepareAccount.setCustomerAccount(ui->userNameLine->text().toStdString(),
                                          ui->phoneNumLine->text().toStdString(),
                                          ui->passwordLine->text().toStdString());
        stringstream errorReport;
        if(!Sakuno::databaseEntrance->registerUserAccount(prepareAccount, errorReport)){
            QMessageBox::information(this,tr("提示"),tr(errorReport.str().c_str()));
            return;
        }
        QMessageBox::information(this,tr("提示"),tr("注册成功"));
    }else if(ui->waiterType->isChecked()){
        if(permissionCode.empty()){
            QMessageBox::information(this,tr("提示"),tr("尚未获取认证"));
            return;
        }
        if (ui->userNameLine->text().isEmpty() ||
                ui->passwordLine->text().isEmpty() ||
                ui->checkPasswordLine->text().isEmpty()){
            QMessageBox::information(this,tr("提示"),tr("请填满必选信息框！"));
            return;
        }
        if(ui->passwordLine->text() != ui->checkPasswordLine->text()){
            QMessageBox::information(this,tr("提示"),tr("密码与确认密码不一致！"));
            return;
        }
        AccountInfo prepareAccount;
        prepareAccount.setWaiterAccount(ui->userNameLine->text().toStdString(),
                                        ui->phoneNumLine->text().toStdString(),
                                        ui->passwordLine->text().toStdString());
        stringstream errorReport;
        if(!Sakuno::databaseEntrance->registerWaiterAccount(prepareAccount, permissionCode, errorReport)){
            QMessageBox::information(this,tr("提示"),tr(errorReport.str().c_str()));
            return;
        }
        QMessageBox::information(this,tr("提示"),tr("注册成功"));
    }
}

void RegisterDialog::switchToWaiterType() {
    ui->waiterType->setChecked(true);
    ui->customerType->setChecked(false);
    ui->authenicateGroup->show();
    ui->userNameLine->setPlaceholderText(tr("用户名"));
    ui->phoneNumLine->setPlaceholderText(tr("手机号 (选填)"));
    ui->permissionCheck->setEnabled(true);
    if(permissionCode.empty()){
        if(!haveAsked){
            QMessageBox::information(this,tr("提示"),tr("需要其他服务员账号或认证码提供认证"));
            haveAsked = true;
        }
        ui->authenicateOffer->setStyleSheet("QLabel{font-size: 12px;color: red;}");
        ui->permissionInfo->setStyleSheet("QLabel{font-size: 12px;color: red;}");
        ui->userNameLine->setEnabled(false);
        ui->phoneNumLine->setEnabled(false);
        ui->passwordLine->setEnabled(false);
        ui->checkPasswordLine->setEnabled(false);
    }
}

void RegisterDialog::switchToCustomerType() {
    ui->waiterType->setChecked(false);
    ui->customerType->setChecked(true);
    ui->authenicateGroup->hide();
    ui->userNameLine->setPlaceholderText(tr("用户名 (选填)"));
    ui->phoneNumLine->setPlaceholderText(tr("手机号"));
    ui->permissionCheck->setEnabled(false);
    ui->userNameLine->setEnabled(true);
    ui->phoneNumLine->setEnabled(true);
    ui->passwordLine->setEnabled(true);
    ui->checkPasswordLine->setEnabled(true);
}

void RegisterDialog::goToAuthenticate() {
    emit toAuthenticate();
}

void RegisterDialog::authenticateSuccess(string userName, string permCode) {
    ui->authenicateOffer->setText(tr(userName.c_str()));
    ui->authenicateOffer->setStyleSheet("QLabel{font-size: 12px;color: green;}");
    ui->permissionInfo->setText(tr("已认证"));
    ui->permissionInfo->setStyleSheet("QLabel{font-size: 12px;color: green;}");

    permissionCode = permCode;
    ui->userNameLine->setEnabled(true);
    ui->phoneNumLine->setEnabled(true);
    ui->passwordLine->setEnabled(true);
    ui->checkPasswordLine->setEnabled(true);
}


void RegisterDialog::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        for(auto it : dragSpaces){
            QRect rect = it->rect();
            rect.setBottom(rect.top() + 220);
            if (rect.contains(event->pos()))
            {
                m_bDragging = true;
                m_poStartPosition = event->globalPos();
                m_poFramePosition = frameGeometry().topLeft();
                break;
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void RegisterDialog::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (m_bDragging)
        {
            QPoint delta = event->globalPos() - m_poStartPosition;
            move(m_poFramePosition + delta);
        }
    }
    QWidget::mouseMoveEvent(event);
}

void RegisterDialog::mouseReleaseEvent(QMouseEvent* event)
{
    m_bDragging = false;
    QWidget::mouseReleaseEvent(event);
}


