//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
#define EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>

class databaseOption : public QDialog {
    Q_OBJECT
private:
public:
    databaseOption(){
        auto layout = new QVBoxLayout;
        layout->addWidget(new QPushButton(tr("Hello World")));
        setLayout(layout);
    }
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
