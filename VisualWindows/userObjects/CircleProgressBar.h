//
// Created by sakunoakarinn on 22-12-7.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_CIRCLEPROGRESSBAR_H
#define EXPRESSMANAGEMENTSYSTEM_CIRCLEPROGRESSBAR_H

#include <QGroupBox>

class CircleProgressBar : public QGroupBox{

    Q_OBJECT

private:
    unsigned numerator, denominator;

    CircleProgressBar(unsigned num, unsigned den, QGroupBox* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
};


#endif //EXPRESSMANAGEMENTSYSTEM_CIRCLEPROGRESSBAR_H
