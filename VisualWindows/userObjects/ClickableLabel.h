//
// Created by sakunoakarinn on 22-12-1.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_CLICKABLELABEL_H
#define EXPRESSMANAGEMENTSYSTEM_CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class ClickableLabel : public QLabel {
Q_OBJECT
public:
    explicit ClickableLabel(const QString& qs):
        QLabel(qs){}
signals:
    void clicked();
private:
    void mouseReleaseEvent(QMouseEvent* ev) override{
        if(ev != nullptr && ev->button() == Qt::LeftButton)
            emit clicked();
    }
    void enterEvent(QEvent*){
        setCursor(QCursor(Qt::PointingHandCursor));
    }
    void leaveEvent(QEvent*) override{
        setCursor(QCursor(Qt::ArrowCursor));
    }
};


#endif //EXPRESSMANAGEMENTSYSTEM_CLICKABLELABEL_H
