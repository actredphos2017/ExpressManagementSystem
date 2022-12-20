//
// Created by sakuno on 22-12-20.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_RESETPASSWORD_H
#define EXPRESSMANAGEMENTSYSTEM_RESETPASSWORD_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QLayout>

#include "../../GlobalAttribute.h"

class ResetPassword : public QDialog{
Q_OBJECT

private:
    QLabel* oldPasswordTitle{};
    QLabel* newPasswordTitle{};
    QLabel* checkPasswordTitle{};

    QLineEdit* oldPasswordLine{};
    QLineEdit* newPasswordLine{};
    QLineEdit* checkPasswordLine{};

    QPushButton* yesBtn{};
    QPushButton* cancelBtn{};

    void initItem();
    void initConnect();
public:
    explicit ResetPassword(QWidget* parent = nullptr);

public slots:
    void toResetPassword();
    void prepareReset();
};


#endif //EXPRESSMANAGEMENTSYSTEM_RESETPASSWORD_H
