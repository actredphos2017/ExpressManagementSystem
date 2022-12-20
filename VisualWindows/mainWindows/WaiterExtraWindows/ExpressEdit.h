//
// Created by sakuno on 22-12-18.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_EXPRESSEDIT_H
#define EXPRESSMANAGEMENTSYSTEM_EXPRESSEDIT_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QDateTimeEdit>

#include "../../../GlobalAttribute.h"

class ExpressEdit : public QDialog {
Q_OBJECT

public:
    explicit ExpressEdit(QWidget *parent = nullptr);

    ~ExpressEdit() override;

private:

    QLabel* trackNumTitle;
    QLabel* compTitle;
    QLabel* reciNameTitle;
    QLabel* reciPhoneNumTitle;
    QLabel* reciLocTitle;
    QLabel* reciPostTitle;
    QLabel* sendNameTitle;
    QLabel* sendPhoneNumTitle;
    QLabel* sendLocTitle;
    QLabel* sendPostTitle;
    QLabel* itemWeightTitle;
    QLabel* pickCodeTitle;
    QLabel* warehousingTimeTitle;

    QLineEdit* trackNumLine;
    QLineEdit* compLine;
    QLineEdit* reciNameLine;
    QLineEdit* reciPhoneNumLine;
    QLineEdit* reciLocLine;
    QLineEdit* reciPostLine;
    QLineEdit* sendNameLine;
    QLineEdit* sendPhoneNumLine;
    QLineEdit* sendLocLine;
    QLineEdit* sendPostLine;
    QDoubleSpinBox* itemWeightBox;
    QLineEdit* pickCodeLine;
    QDateTimeEdit* warehousingTimeEdit;

    QCheckBox* ifTakenBox;
    QPushButton* yesBtn;

    void initItem();
    void initConnect();

protected:
    void closeEvent(QCloseEvent* event) override;

public slots:
    void editOrder(OrderInfo* order);
    void addOrder();
    void pushOkButton();

signals:
    void doneEdit(OrderInfo*);
    void closeWindow();
};


#endif //EXPRESSMANAGEMENTSYSTEM_EXPRESSEDIT_H
