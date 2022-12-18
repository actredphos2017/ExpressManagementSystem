//
// Created by sakunoakarinn on 22-12-7.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_CIRCLEPROGRESSBAR_H
#define EXPRESSMANAGEMENTSYSTEM_CIRCLEPROGRESSBAR_H

#include <QGroupBox>
#include <QLabel>

class CircleProgressBar : public QGroupBox{

    Q_OBJECT

private:
    unsigned numerator, denominator;

    QLabel* numLabel;
    QLabel* denLabel;
public:
    CircleProgressBar(unsigned num, unsigned den, QGroupBox* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;

    void updateData(unsigned int num, unsigned int den);
};


#endif //EXPRESSMANAGEMENTSYSTEM_CIRCLEPROGRESSBAR_H
