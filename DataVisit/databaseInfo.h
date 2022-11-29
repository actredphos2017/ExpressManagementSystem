//
// Created by sakunoakarinn on 22-11-29.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_DATABASEINFO_H
#define EXPRESSMANAGEMENTSYSTEM_DATABASEINFO_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class databaseInfo {
private:
    string hostName;
    string userName;
    string password;
    string databaseName;
public:
    databaseInfo ();
    databaseInfo (istream& is);
    databaseInfo (string, string, string, string);
    void setHostName (string);
    void setUserName (string);
    void setPassword (string);
    void setDatabaseName (string);
    string getHostName ();
    string getUserName ();
    string getPassword ();
    string getDatabaseName ();
    bool haveRealWrite (ostream& os);
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASEINFO_H
