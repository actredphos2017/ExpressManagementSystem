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

    void setShadow(QWidget *qw);
    void setBlur(QWidget *qw);

private:
    Ui::LoginDialog *ui;

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

public slots:
    void toRegister();
    void toConfigDatabase();
    void comeBack();
    void signIn();
    void checkResult();
    void checkSave();
    void init();
};

#endif // LOGINDIALOG_H
