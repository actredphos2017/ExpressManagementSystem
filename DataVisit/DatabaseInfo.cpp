//
// Created by sakunoakarinn on 22-11-29.
//
#include "../GlobalAttribute.h"

#include "DatabaseInfo.h"

#include <utility>

using namespace std;

void DatabaseInfo::write(ostream &os) const {
    os << "$DatabaseInfo" << endl;
    os << "HostName " << hostName << endl;
    os << "UserName " << userName << endl;
    os << "Password " << password << endl;
}

bool DatabaseInfo::read(istream &is) {
    string checkStr;
    is >> checkStr;
    if(checkStr != "$DatabaseInfo"){
#if SAKUNO_DEBUG_MODE
        qDebug() << "Database Infomation Read failed!";
#endif
        return false;
    }
    map<string, string> info;
    string first, second;
    while(!is.eof()){
        is >> first >> second;
        info[first] = second;
    }
#if SAKUNO_DEBUG_MODE
    for(const auto& it : info)
        qDebug() << it.first.c_str() << ' ' << it.second.c_str();
#endif
    auto infoPush = [](
            map<string, string>& inf,
            const string& str,
            string& edit) -> void {
        if (inf.find(str) != inf.end())
            edit = inf[str];
        else
            edit = "";
    };
    infoPush(info, "HostName", hostName);
    infoPush(info, "UserName", userName);
    infoPush(info, "Password", password);
#if SAKUNO_DEBUG_MODE
    qDebug() << hostName.c_str() << ' ' << userName.c_str() << ' ' << password.c_str();
#endif
    return true;
}

DatabaseInfo::DatabaseInfo(istream &is) {
    read(is);
}

DatabaseInfo::DatabaseInfo(string hostName,
                           string userName,
                           string password,
                           string connectName = "New Connection"):
    connectName(std::move(connectName)),
    hostName(std::move(hostName)),
    userName(std::move(userName)),
    password(std::move(password)){}

void DatabaseInfo::read(string hName,
                        string uName,
                        string pWord,
                        string cName = "New Connection") {
    connectName = std::move(cName);
    hostName = std::move(hName);
    userName = std::move(uName);
    password = std::move(pWord);
}
