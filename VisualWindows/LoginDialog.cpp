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
    initItem();
    initConnect();
    setWindowFlags(Qt::FramelessWindowHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setBlur(QWidget* qw, int radius){
    auto* blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(radius);
    qw->setGraphicsEffect(blurEffect);
}

void LoginDialog::setShadow(QWidget *qw, int radius) {
    auto* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(QColor("black"));
    shadowEffect->setBlurRadius(radius);

    qw->setGraphicsEffect(shadowEffect);
}
void LoginDialog::initItem() {
    setShadow(ui->connectCheckGroup, 12);
    setShadow(ui->loginBtn, 12);
    setShadow(ui->MainSpace, 12);
    setShadow(ui->picture, 12);
    setShadow(ui->cancelBtn, 12);

    setBlur(ui->backGround, 64);

    dragSpaces.push_back(ui->backGround);

    ui->userNameEdit->setPlaceholderText(tr("用户名/手机号"));
    ui->passwordEdit->setPlaceholderText(tr("密码"));
}

void LoginDialog::initConnect() {
    connect(ui->databaseOptionEntrance,
            SIGNAL(clicked()),
            this,
            SLOT(toConfigDatabase())
    ); //数据库配置

    connect(ui->cancelBtn,
            SIGNAL(clicked()),
            this,
            SLOT(close())
    ); //退出

    connect(ui->registerBtn,
            SIGNAL(clicked()),
            this,
            SLOT(toRegister())
    ); //注册

    connect(ui->loginBtn,
            SIGNAL(clicked()),
            this,
            SLOT(signIn())
    ); //登录

    connect(ui->databaseConnectRetry,
            SIGNAL(clicked()),
            this,
            SLOT(checkSave())
    );

    connect(this,
            SIGNAL(pushDatabaseConfBtn()),
            &databaseConfigInterface,
            SLOT(toConfigDatabase())
    ); //连接登录界面与数据库配置界面

    connect(&databaseConfigInterface,
            SIGNAL(pushBackBtn()),
            this,
            SLOT(checkResult())
    ); //返回登录界面

    connect(ui->passwordEdit,
            SIGNAL(returnPressed()),
            this,
            SLOT(signIn()));

    connect(ui->userNameEdit,
            SIGNAL(returnPressed()),
            this,
            SLOT(signIn()));
    //回车键登录

    //信息传递
    connect (
            this,
            SIGNAL(checkSaveDBInfo()),
            &databaseConfigInterface,
            SLOT(checkSave())
    );
    connect(
            &databaseConfigInterface,
            SIGNAL(checkFinish()),
            this,
            SLOT(checkResult())
    );
}

void LoginDialog::toConfigDatabase(){
    emit pushDatabaseConfBtn();
}

void LoginDialog::toRegister(){
    this->hide();
    emit pushRegisterBtn();
}

void LoginDialog::signIn() {
    if(ui->userNameEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty()){
        QMessageBox::information(this, tr("提示"), tr("请填满信息框"));
        return;
    }
    stringstream errorSs;
    if(!Sakuno::databaseEntrance->loginAccount(ui->userNameEdit->text().toStdString(),
                                              ui->passwordEdit->text().toStdString(),
                                              errorSs)){
        QMessageBox::information(this, tr("提示"), tr(errorSs.str().c_str()));
        return;
    }
    if(Sakuno::onlineAccount->accountType == Customer)
        emit customerLoginSuccess();
    else
        emit waiterLoginSuccess();
    close();
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
        ui->databaseStatusTitle->setStyleSheet("color: red;font-size: 12px;");
        ui->databaseStatusTitle->setText(tr("未连接"));
        ui->databaseStatusInfo->setStyleSheet("color: red;font-size: 12px;");
        ui->databaseStatusInfo->setText(tr(""));
        QMessageBox::information(this,tr("提示"),tr("未连接到数据库！请重试或重新配置连接！"));
    }
    else{
        ui->databaseStatusTitle->setStyleSheet("color: green;font-size: 12px;");
        ui->databaseStatusTitle->setText(tr("已连接到"));
        ui->databaseStatusInfo->setStyleSheet("color: green;font-size: 12px;");
        ui->databaseStatusInfo->setText(tr(Sakuno::dbInfo->connectName.c_str()));
    }
}


void LoginDialog::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        for(auto it : dragSpaces){
            QRect rect = it->rect();
            rect.setBottom(rect.top() + 220);
            if (rect.contains(event->pos())){
                m_bDragging = true;
                m_poStartPosition = event->globalPos();
                m_poFramePosition = frameGeometry().topLeft();
                break;
            }
        }
    QWidget::mousePressEvent(event);
}

void LoginDialog::mouseMoveEvent(QMouseEvent* event){
    if (event->buttons() & Qt::LeftButton)
        if (m_bDragging){
            QPoint delta = event->globalPos() - m_poStartPosition;
            move(m_poFramePosition + delta);
        }
    QWidget::mouseMoveEvent(event);
}

void LoginDialog::mouseReleaseEvent(QMouseEvent* event){
    m_bDragging = false;
    QWidget::mouseReleaseEvent(event);
}

void LoginDialog::comeBack() {
    show();
}