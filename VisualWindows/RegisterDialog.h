#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "../GlobalAttribute.h"

#include <QDialog>
#include <QMouseEvent>

#include "PermissionGetDialog.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:

    Ui::RegisterDialog *ui;

    PermissionGetDialog authenticateInterface;

    bool haveAsked = false;
    string permissionCode;

    bool m_bDragging;
    QPoint m_poStartPosition;
    QPoint m_poFramePosition;

    QVector<QWidget*> dragSpaces;

    void initItem();
    void initConnect();
    void setShadow(QWidget *qw, int radius);
    void setBlur(QWidget *qw, int radius);

signals:
    void pushBackBtn();
    void toAuthenticate();


public slots:
    void toRegister();
    void goToAuthenticate();
    void backToLogin();
    void beginRegister();
    void switchToWaiterType();
    void switchToCustomerType();
    void authenticateSuccess(string userName, string permCode);
};

#endif // REGISTERDIALOG_H
