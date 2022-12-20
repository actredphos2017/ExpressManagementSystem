//
// Created by sakunoakarinn on 22-12-6.
//
#ifndef EXPRESSMANAGEMENTSYSTEM_SAKUNOFUNCTIONS_H
#define EXPRESSMANAGEMENTSYSTEM_SAKUNOFUNCTIONS_H

#include <string>
#include <sstream>
#include <iostream>
#include <QDateTime>

using namespace std;

namespace Sakuno {

    struct Time{
        Time() = default;
        explicit Time(const string &sqlOutputDateTime);
        explicit Time(const QDateTime& dateTime);

        int year{};
        int month{};
        int mDay{};
        int hour{};
        int min{};
        int second{};

        string baseTime();
        string sqlTime();
        string s_date();
        string s_time();
        Time subDays(int days);
    };

    int toInt(const string& old);
    string toVarchar(const string& old);
    bool isNumber(const char& c);
    bool isLetter(const char& c);
    string getFileName(const string& fullDirName);
    string getFileType(const string& fullDirName);
}


#endif //EXPRESSMANAGEMENTSYSTEM_SAKUNOFUNCTIONS_H
