//
// Created by sakunoakarinn on 22-12-6.
//

#include "SakunoFunctions.h"

string Sakuno::toVarchar(const string& old){
    return (string)"\'" + old + '\'';
}

bool Sakuno::isNumber(const char& c){
    return c >= '0' && c <= '9';
}

bool Sakuno::isLetter(const char& c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

string Sakuno::getFileName(const string& fullDirName){
    stringstream ss;
    for(const char& it : fullDirName){
        ss << it;
        if(it == '/' || it == '\\')
            ss.clear();
    }
    return ss.str();
}

string Sakuno::getFileType(const string& fullDirName){
    string fileName = getFileName(fullDirName);
    bool isContent = false;
    stringstream ss;
    for(const char& it : fileName){
        if(isContent)
            ss << it;
        if(it == '.'){
            isContent = true;
            ss.clear();
        }
    }
    return ss.str();
}

int Sakuno::toInt(const string &old) {
    int res = 0;
    for(auto it : old){
        res *= 10;
        res += (int) it - '0';
    }
    return res;
}

Sakuno::Time::Time(const string& sqlOutputDateTime) {
    year = Sakuno::toInt(sqlOutputDateTime.substr(0, 4));
    month = Sakuno::toInt(sqlOutputDateTime.substr(5, 2));
    mDay = Sakuno::toInt(sqlOutputDateTime.substr(8, 2));
    hour = Sakuno::toInt(sqlOutputDateTime.substr(11, 2));
    min = Sakuno::toInt(sqlOutputDateTime.substr(14, 2));
    second = Sakuno::toInt(sqlOutputDateTime.substr(17, 2));
}

string Sakuno::Time::s_date() {
    return to_string(month) + "月" + to_string(mDay) + "日";
}

string Sakuno::Time::s_time() {
    return to_string(hour) + ':' + to_string(min) + ':' + to_string(second);
}

string Sakuno::Time::baseTime() {
    stringstream resSs;
    resSs << year << '-' << month << '-' << mDay << ' ' << hour << ':' << min << ':' << second;
    return resSs.str();
}

string Sakuno::Time::sqlTime() {
    stringstream resSs;
    resSs << '\'' << year << '-' << month << '-' << mDay << ' ' << hour << ':' << min << ':' << second << '\'';
    return resSs.str();
}

Sakuno::Time Sakuno::Time::subDays(int days) {
    QDate date(year, month, mDay);
    date.addDays(days*(-1));
    Sakuno::Time time = *this;
    time.year = date.year();
    time.month = date.month();
    time.mDay = date.day();
    return time;
}

Sakuno::Time::Time(const QDateTime &dateTime):
    year(dateTime.date().year()),
    month(dateTime.date().month()),
    mDay(dateTime.date().day()),
    hour(dateTime.time().hour()),
    min(dateTime.time().minute()),
    second(dateTime.time().second()){}