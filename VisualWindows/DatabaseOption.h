//
// Created by sakunoakarinn on 22-11-30.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
#define EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H

#include "../GlobalAttribute.h"

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

class DatabaseOption : public QDialog {
    Q_OBJECT
private:
    QLabel* choosePathTitle{};
    QLabel* selectedFileTitle{};
    QLabel* connectStatusTitle{};
    QLabel* connectNameTitle{};
    QLabel* hostNameTitle{};
    QLabel* userNameTitle{};
    QLabel* passwordTitle{};

    QLabel* selectedFileName{};
    QLabel* connectStatusContent{};

    QLineEdit* connectNameLine{};
    QLineEdit* hostNameLine{};
    QLineEdit* userNameLine{};
    QLineEdit* passwordLine{};

    QRadioButton* fromFile{};
    QRadioButton* fromEnter{};

    QPushButton* selectFileBtn{};
    QPushButton* saveFile{};
    QPushButton* checkBtn{};
    QPushButton* backBtn{};

    QString filePath;

    void initItem();
    void initConnect();
    void createSave();
    void connectFailed();
public:
    DatabaseOption();
    void readSave();
signals:
    void pushBackBtn();
    void checkFinish();
public slots:
    void backToLogin();
    void toConfigDatabase();
    void saveToLocal();
    void switchToEnter(bool);
    void switchToFile(bool);
    void startChooseFile();
    void checkDatabase();
    void checkSave();
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
