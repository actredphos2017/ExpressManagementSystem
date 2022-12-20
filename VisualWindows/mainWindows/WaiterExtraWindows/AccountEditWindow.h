//
// Created by sakuno on 22-12-19.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_ACCOUNTEDITWINDOW_H
#define EXPRESSMANAGEMENTSYSTEM_ACCOUNTEDITWINDOW_H

#include <QDialog>

#include "../../../GlobalAttribute.h"
#include "AccountEdit.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AccountEditWindow; }
QT_END_NAMESPACE

class AccountEditWindow : public QDialog {
Q_OBJECT

public:
    explicit AccountEditWindow(QWidget *parent = nullptr);

    ~AccountEditWindow() override;

private:
    Ui::AccountEditWindow *ui;

    AccountEdit* editWin;

    AccountGroup* viewAccount;
    AccountInfo* editTargetAccount = nullptr;

    void initItem();
    void initConnect();

public slots:
    void fleshData();
    void toManageAccount();
    void prepareEditAccount();
    void finishEdit(AccountInfo * newInfo);
    void deleteAccount();

signals:
    void editAccount(AccountInfo *);
};


#endif //EXPRESSMANAGEMENTSYSTEM_ACCOUNTEDITWINDOW_H
