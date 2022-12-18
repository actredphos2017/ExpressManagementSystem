//
// Created by sakunoakarinn on 22-12-7.
//

#include "CircleProgressBar.h"

#include <QPainter>
#include <QPen>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

#define BAR_SIZE 160
#define BAR_PAD_SIZE 20

#define LABEL_WSIZE 100
#define LABEL_HSIZE 50

CircleProgressBar::CircleProgressBar(unsigned int num, unsigned int den, QGroupBox *parent) :
    QGroupBox(parent), numerator(num), denominator(den){
    setStyleSheet("border: outsize; background-color: transparent");
    setMaximumSize(BAR_SIZE, BAR_SIZE);
    setMinimumSize(BAR_SIZE, BAR_SIZE);

    numLabel = new QLabel(tr(std::to_string(numerator).c_str()), this);

    auto tempPalette = numLabel->palette();
    tempPalette.setColor(QPalette::WindowText, QColor(255, 163, 72));
    numLabel->setPalette(tempPalette);
    auto tempFont = numLabel->font();
    tempFont.setBold(true);
    tempFont.setPixelSize(20);
    numLabel->setFont(tempFont);

    numLabel->setMinimumSize(LABEL_WSIZE, LABEL_HSIZE);
    numLabel->setMaximumSize(LABEL_WSIZE, LABEL_HSIZE);
    numLabel->setStyleSheet("background-color: transparent");
    numLabel->move(QPoint(BAR_SIZE/2-LABEL_WSIZE, BAR_SIZE/2-LABEL_HSIZE/2));
    numLabel->setAlignment(Qt::AlignBottom);
    numLabel->setAlignment(Qt::AlignRight);


    denLabel = new QLabel(tr(std::to_string(denominator).c_str()), this);

    tempPalette = denLabel->palette();
    tempPalette.setColor(QPalette::WindowText, QColor(255, 163, 72));
    denLabel->setPalette(tempPalette);
    tempFont = denLabel->font();
    tempFont.setBold(true);
    tempFont.setPixelSize(16);
    denLabel->setFont(tempFont);

    denLabel->setMinimumSize(LABEL_WSIZE, LABEL_HSIZE);
    denLabel->setMaximumSize(LABEL_WSIZE, LABEL_HSIZE);
    denLabel->setStyleSheet("background-color: transparent");
    denLabel->move(QPoint(BAR_SIZE/2, BAR_SIZE/2));
    denLabel->setAlignment(Qt::AlignLeft);
    denLabel->setAlignment(Qt::AlignTop);
}

void CircleProgressBar::paintEvent(QPaintEvent *event) {
    setStyleSheet("background-color: white; border-radius: 12px; border: 2px black;");
    QGroupBox::paintEvent(event);

    QRect circleSpace(BAR_PAD_SIZE, BAR_PAD_SIZE, BAR_SIZE - 2 * BAR_PAD_SIZE, BAR_SIZE - 2 * BAR_PAD_SIZE);
    QPainter painter(this);
    QPen pen;
    QPainterPath frontPath(QPoint(BAR_SIZE / 2, BAR_PAD_SIZE));
    QPainterPath backgroundPath(QPoint(BAR_SIZE / 2, BAR_PAD_SIZE));
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setWidth(10);
    backgroundPath.arcTo(circleSpace, 90, 360);
    frontPath.arcTo(circleSpace, 90, (360.0 * numerator / denominator));

    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.drawPath(backgroundPath);

    pen.setColor(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.drawPath(frontPath);

    pen.setColor(QColor(255, 163, 72));
    pen.setWidth(3);
    painter.setPen(pen);

    painter.drawLine(QPoint(BAR_SIZE/2+(BAR_SIZE-BAR_PAD_SIZE)/6, BAR_SIZE/2-(BAR_SIZE-BAR_PAD_SIZE)/6),
                     QPoint(BAR_SIZE/2-(BAR_SIZE-BAR_PAD_SIZE)/6, BAR_SIZE/2+(BAR_SIZE-BAR_PAD_SIZE)/6));

    numLabel->show();
}

void CircleProgressBar::updateData(unsigned int num, unsigned int den){
    numerator = num;
    denominator = den;
    numLabel->setText(std::to_string(num).c_str());
    denLabel->setText(std::to_string(den).c_str());
    update();
}