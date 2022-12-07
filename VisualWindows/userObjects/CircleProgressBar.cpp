//
// Created by sakunoakarinn on 22-12-7.
//

#include "CircleProgressBar.h"

CircleProgressBar::CircleProgressBar(unsigned int num, unsigned int den, QGroupBox *parent) :
    QGroupBox(parent), numerator(num), denominator(den){
    setStyleSheet("border: outsize");
    setMaximumSize(120, 120);
    setMinimumSize(120, 120);
}



void CircleProgressBar::paintEvent(QPaintEvent *event) {

}