//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
#define EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H

#include "../globalAttribute.h"

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

class databaseOption : public QDialog {
    Q_OBJECT
private:
    QLabel* choosePathTitle;
    QRadioButton* fromFile;
    QPushButton* chooseFileBtn;
    QRadioButton* fromEnter;
    QLabel* connectStatusTitle;
    QLabel* connectStatusContent;
    QLabel* connectNameTitle;
    QLineEdit* connectNameLine;
    QLabel* hostNameTitle;
    QLineEdit* hostNameLine;
    QLabel* userNameTitle;
    QLineEdit* userNameLine;
    QLabel* passwordTitle;
    QLineEdit* passwordLine;
    QPushButton* checkBtn;
    QPushButton* backBtn;

    void iniItem();
public:
    databaseOption();
signals:
    void pushBackBtn();
public slots:
    void toConfigDatabase();
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
