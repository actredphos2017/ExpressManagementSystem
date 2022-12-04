#include "LoginDialog.h"
#include "ui_LoginDialog.h"

#include <QMessageBox>
#include <QDir>
#include <QGraphicsEffect>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //setFixedSize(469,335);
    initItem();
    initConnect();
    setWindowFlags(Qt::FramelessWindowHint);
    resize(size());
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setBlur(QWidget* qw){
    auto* blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(64);
    qw->setGraphicsEffect(blurEffect);
}

void LoginDialog::setShadow(QWidget *qw) {
    auto* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(QColor("black"));
    shadowEffect->setBlurRadius(12);

    qw->setGraphicsEffect(shadowEffect);
}
void LoginDialog::initItem() {
    setShadow(ui->connectCheckGroup);
    setShadow(ui->loginBtn);
    setShadow(ui->MainSpace);
    setShadow(ui->picture);
    setShadow(ui->cancelBtn);

    setBlur(ui->backGround);

    dragSpaces.push_back(ui->MainSpace);
    dragSpaces.push_back((ui->Title));

    ui->userNameEdit->setPlaceholderText(tr("用户名/手机号"));
    ui->passwordEdit->setPlaceholderText(tr("密码"));
    qDebug() << ui->picture->styleSheet();
}

void LoginDialog::initConnect() {
    connect(
            ui->databaseOptionEntrance,
            SIGNAL(clicked()),
            this,
            SLOT(toConfigDatabase())
    ); //数据库配置

    connect(
            ui->cancelBtn,
            SIGNAL(clicked()),
            this,
            SLOT(close())
    ); //退出

    connect(
            ui->registerBtn,
            SIGNAL(clicked()),
            this,
            SLOT(toRegister())
    ); //注册

    connect(
            ui->loginBtn,
            SIGNAL(clicked()),
            this,
            SLOT(signIn())
    ); //登录

    connect(
            ui->databaseConnectRetry,
            SIGNAL(clicked()),
            this,
            SLOT(checkSave())
    );
}

void LoginDialog::toConfigDatabase(){
    this->hide();
    emit pushDatabaseConfBtn();
}

void LoginDialog::toRegister(){
    this->hide();
    emit pushRegisterBtn();
}


void LoginDialog::comeBack(){
    qDebug() << Sakuno::connectSuccess;
    if(!Sakuno::connectSuccess){
        ui->databaseStatusTitle->setText(tr("未连接"));
        QMessageBox::information(this,tr("提示"),tr("未连接到数据库！请重试或重新配置连接！"));
    }
    else{
        ui->databaseStatusTitle->setText(tr("已连接到"));
        ui->databaseStatusInfo->setText(tr(Sakuno::dbInfo->connectName.c_str()));
    }
    show();
}

void LoginDialog::signIn() {

}

void LoginDialog::init() {
    show();
    checkSave();
}

void LoginDialog::checkSave() {
    ui->databaseStatusInfo->setText("");
    emit checkSaveDBInfo();
}

void LoginDialog::checkResult() {
    if(!Sakuno::connectSuccess){
        ui->databaseStatusTitle->setText(tr("未连接"));
        QMessageBox::information(this,tr("提示"),tr("未连接到数据库！请重试或重新配置连接！"));
    }
    else{
        ui->databaseStatusTitle->setText(tr("已连接到"));
        ui->databaseStatusInfo->setText(tr(Sakuno::dbInfo->connectName.c_str()));
    }


}


void LoginDialog::mousePressEvent(QMouseEvent* event)
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

void LoginDialog::mouseMoveEvent(QMouseEvent* event)
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

void LoginDialog::mouseReleaseEvent(QMouseEvent* event)
{
    m_bDragging = false;
    QWidget::mouseReleaseEvent(event);
}


