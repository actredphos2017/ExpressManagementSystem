//
// Created by sakunoakarinn on 22-11-29.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
#define EXPRESSMANAGEMENTSYSTEM_DATABASEINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#define DEFAULT_DATABASE_INFO_PATH "~/database.txt"

using namespace std;

class databaseOption {
public:
    databaseOption () = default;
    explicit databaseOption (istream& is);
    databaseOption (string, string, string, string);
    bool read(istream& is);
    void write (ostream& os) const;
public:
    string hostName;
    string userName;
    string password;
    string databaseName;
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASEOPTION_H
