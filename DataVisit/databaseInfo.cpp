//
// Created by sakunoakarinn on 22-11-29.
//

#include "databaseInfo.h"

void databaseInfo::write(ostream &os) {
    os << "$DatabaseInfo" << endl;
    os << "HostName " << hostName << endl;
    os << "UserName " << userName << endl;
    os << "Password " << password << endl;
    os << "Database " << databaseName << endl;
}

bool databaseInfo::read(istream &is) {
    string checkStr;
    is >> checkStr;
    if(checkStr != "$DatabaseInfo"){
        cout << "Database Infomation Read failed!" << endl;
        return false;
    }
    unordered_map<string, string> info;
    string first, second;
    while(!is.eof()){
        is >> first >> second;
        info[first] = second;
    }
    auto infoPush = [](
            unordered_map<string, string>& inf,
            const string& str,
            string& edit) -> void {
        if (inf.find(str) != inf.end())
            edit = inf["HostName"];
        else
            edit = "";
    };
    infoPush(info, "HostName", hostName);
    infoPush(info, "UserName", userName);
    infoPush(info, "Password", password);
    infoPush(info, "Database", databaseName);
}

databaseInfo::databaseInfo(istream &is) {
    read(is);
}

databaseInfo::databaseInfo(string hostName, string userName, string password, string databaseName):
    hostName(std::move(hostName)),
    userName(std::move(userName)),
    password(std::move(password)),
    databaseName(std::move(databaseName)){}

