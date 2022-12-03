//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_REGISTERDIALOG_H
#define EXPRESSMANAGEMENTSYSTEM_REGISTERDIALOG_H

#include "../GlobalAttribute.h"

#include <QDialog>
#include <QLineEdit>
#include <QLayout>
#include <QRadioButton>
#include <QPushButton>

class RegisterDialog : public QDialog{
    Q_OBJECT

private:

    void initItem();
    void initConnect();
public:
    RegisterDialog();
};


#endif //EXPRESSMANAGEMENTSYSTEM_REGISTERDIALOG_H
