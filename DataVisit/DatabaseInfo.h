//
// Created by sakunoakarinn on 22-11-29.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_DATABASEINFO_H
#define EXPRESSMANAGEMENTSYSTEM_DATABASEINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define DEFAULT_DATABASE_INFO_PATH "~/database.txt"

using namespace std;

class DatabaseInfo {
public:
    DatabaseInfo () = default;
    explicit DatabaseInfo (istream& is);
    DatabaseInfo (string, string, string, string);
    void read(string, string, string, string);
    bool read(istream& is);
    void write (ostream& os) const;
public:
    string connectName{"New Connect"};
    string hostName;
    string userName;
    string password;
    //string databaseName;
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASEINFO_H
