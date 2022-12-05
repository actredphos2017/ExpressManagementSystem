//
// Created by sakunoakarinn on 22-12-5.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_PICKUPQUICKTAG_H
#define EXPRESSMANAGEMENTSYSTEM_PICKUPQUICKTAG_H

#include <QtGui>
#include <QtCore>
#include <QGroupBox>

class PickupQuickTag : public QGroupBox {

    Q_OBJECT

private:

    QString sender;
    QString receiver;
    QString pickCode;

    void circleAndText(QPoint loc, const QString &text, QColor *colors, const QString& name);

public:

    PickupQuickTag(const QString& sender, const QString& receiver, const QString& pickCode, QGroupBox* parent = nullptr);

protected:

    void paintEvent(QPaintEvent* e) override;

public slots:

signals:

    };


#endif //EXPRESSMANAGEMENTSYSTEM_PICKUPQUICKTAG_H
