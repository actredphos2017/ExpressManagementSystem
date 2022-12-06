//
// Created by sakunoakarinn on 22-12-5.
//

#include <QLabel>
#include <utility>
#include "PickupQuickTag.h"

PickupQuickTag::PickupQuickTag(QString  sender, QString  receiver, const QString& pickCode, QGroupBox *parent) :
    QGroupBox(parent),
    sender(std::move(sender)),
    receiver(std::move(receiver)),
    pickCode(pickCode)
{
    auto widgetSize = QSize(350, 80);
    setMaximumSize(widgetSize);
    setMinimumSize(widgetSize);
    setStyleSheet("border-radius: 12px; border-style: 2px black; background-color: white; padding: 4px 4px");
    auto pickCodeLabel = new QLabel(pickCode, this);

    auto labelFont = pickCodeLabel->font();
    labelFont.setBold(true);
    labelFont.setPixelSize(40);
    pickCodeLabel->setFont(labelFont);

    pickCodeLabel->setStyleSheet("background-color: transparent");
    pickCodeLabel->setAlignment(Qt::AlignCenter);
    pickCodeLabel->move(130, 20);
    pickCodeLabel->setMaximumSize(200, 40);
    pickCodeLabel->show();
}

void PickupQuickTag::circleAndText(QPoint loc, const QString& text, QColor* colors, const QString& name){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPoint shadowStartLoc(loc.x() + 2, loc.y() + 2);
    QRadialGradient shadowEffect(shadowStartLoc, 15);
    shadowEffect.setColorAt(0.5, QColor(0,0,0,255));
    shadowEffect.setColorAt(1.0, QColor(255,255,255,0));
    QPainterPath shadowPath;
    shadowPath.addEllipse(QRect(QPoint(shadowStartLoc.x() + 15, shadowStartLoc.y() + 15), QPoint(shadowStartLoc.x() - 15, shadowStartLoc.y() - 15)));
    painter.fillPath(shadowPath, shadowEffect);

    QPen pen;

    QPainterPath path;
    path.addEllipse(QRect(QPoint(loc.x() + 10, loc.y() + 10), QPoint(loc.x() - 10, loc.y() - 10)));

    pen.setColor(colors[0]);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawPath(path);

    painter.fillPath(path, QBrush(colors[1]));

    pen.setColor("white");
    painter.setPen(pen);
    painter.drawText(loc.x() - 7,loc.y() + 6,text);

    pen.setColor("black");
    painter.setPen(pen);
    painter.drawText(loc.x() + 20,loc.y() + 6,name);
}

void PickupQuickTag::paintEvent(QPaintEvent *e) {
    QGroupBox::paintEvent(e);

    QPainter backgroundDrawer(this);

    int startLoc = 200;
    QLinearGradient linearEffect(QPoint(maximumWidth() - startLoc, 0), QPoint(maximumWidth(), 0));
    linearEffect.setColorAt(0.0, QColor("white"));
    linearEffect.setColorAt(1.0, QColor(98, 160, 234));//"#4169e1"

    QPainterPath clipPath(QPoint(12,0));
    clipPath.lineTo(maximumWidth() - 12, 0);
    clipPath.arcTo(QRect(QPoint(maximumWidth() - 24, 0),QPoint(maximumWidth(), 24)), 90, -90);
    clipPath.lineTo(maximumWidth(), maximumHeight() - 12);
    clipPath.arcTo(QRect(QPoint(maximumWidth(), maximumHeight()), QPoint(maximumWidth() - 24, maximumHeight() - 24)), 180, -90);
    clipPath.lineTo(maximumWidth() - 12, maximumHeight());
    clipPath.arcTo(QRect(QPoint(0,maximumHeight()), QPoint(24,maximumHeight() - 24)),90, 90);
    clipPath.lineTo(0, 12);
    clipPath.arcTo(QRect(QPoint(0, 0), QPoint(24, 24)), 180, -90);
    backgroundDrawer.setClipPath(clipPath);

    backgroundDrawer.setRenderHint(QPainter::Antialiasing);
    backgroundDrawer.drawPixmap(-50, -5, QPixmap(":/res/expressBox.jpeg").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    backgroundDrawer.fillRect(QRect(QPoint(maximumWidth() - startLoc, 0), QPoint(maximumWidth(), maximumHeight())), linearEffect);

    QColor sendColorMap[2] = {"#ff6100","#ff8000"};
    QColor receiveColorMap[2] = {"#191970","#4169e1"};
    circleAndText(QPoint(52, 25),
                  "发",
                  sendColorMap,
                  sender);
    circleAndText(QPoint(52, 55),
                  "收",
                  receiveColorMap,
                  receiver);
}