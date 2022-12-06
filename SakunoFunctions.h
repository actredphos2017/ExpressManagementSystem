//
// Created by sakunoakarinn on 22-12-6.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_SAKUNOFUNCTIONS_H
#define EXPRESSMANAGEMENTSYSTEM_SAKUNOFUNCTIONS_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace Sakuno {

    struct Time{
        explicit Time(const string &sqlOutputDateTime);

        int year{};
        int month{};
        int mDay{};
        int hour{};
        int min{};
        int second{};
    };

    int toInt(const string& old);
    string toVarchar(const string& old);
    bool isNumber(const char& c);
    bool isLetter(const char& c);
    string getFileName(const string& fullDirName);
    string getFileType(const string& fullDirName);
}


#endif //EXPRESSMANAGEMENTSYSTEM_SAKUNOFUNCTIONS_H
