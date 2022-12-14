//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "../GlobalAttribute.h"

#include <QDialog>
#include <QMouseEvent>
#include <QRect>
#include <QGroupBox>

#include "DatabaseOption.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog() override;

    QVector<QWidget*> dragSpaces;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void setShadow(QWidget *qw, int radius);
    void setBlur(QWidget *qw, int radius);

private:
    Ui::LoginDialog *ui;

    DatabaseOption  databaseConfigInterface;
    bool m_bDragging;
    QPoint m_poStartPosition;
    QPoint m_poFramePosition;

    void initItem();
    void initConnect();

signals:
    void switchToDatabaseOption();
    void pushDatabaseConfBtn();
    void pushRegisterBtn();
    void checkSaveDBInfo();
    void customerLoginSuccess();
    void waiterLoginSuccess();

public slots:
    void comeBack();
    void toRegister();
    void toConfigDatabase();
    void signIn();
    void checkResult();
    void checkSave();
    void init();
};

#endif // LOGINDIALOG_H
