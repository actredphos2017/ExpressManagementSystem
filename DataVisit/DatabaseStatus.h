//
// Created by sakunoakarinn on 22-11-29.
// 该类用于访问数据库
//

#ifndef EXPRESSMANAGEMENTSYSTEM_DATABASESTATUS_H
#define EXPRESSMANAGEMENTSYSTEM_DATABASESTATUS_H

#include <iostream>

#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/resultset.h"
#include "mysql_connection.h"
#include "mysql_driver.h"

#include "DatabaseInfo.h"
#include "../BussinessLogic/OrderInfo.h"
#include "../BussinessLogic/AccountInfo.h"

using namespace std;
using namespace sql;

class DatabaseStatus {
private:
    Driver              *dbDri{};
    Connection          *dbCon{};
    Statement           *dbSta{};
    PreparedStatement   *dbPreSta{};
    ResultSet           *dbRes{};
public:
    DatabaseStatus () = default;
    bool connect(const DatabaseInfo& dbi, ostream& errorOs = cout);
    bool available ();

    bool insertAccount (const AccountGroup& ag, ostream& errorOs = cout);
    bool deleteAccount (const string& condition, ostream &errorOs = cout);
    bool updateAccount (const string& condition, const string& change, ostream &errorOs = cout);
    AccountGroup* selectAccount (const string& condition, ostream &errorOs = cout);

    bool insertOrder (const OrderGroup& og, ostream &errorOs = cout);
    bool deleteOrder (const string& condition, ostream &errorOs = cout);
    bool updateOrder (const string& condition, const string& change, ostream &errorOs = cout);
    OrderGroup* selectOrder (const string& condition, ostream &errorOs = cout);


    string getPermissionCode(const AccountInfo& waiterInfo, ostream &errorOs = cout);
    string checkPermissionCode(const string& code, ostream &errorOs = cout);

    bool checkPrepareAccount(const AccountInfo &accoInfo, ostream &errorOs = cout);
    bool registerWaiterAccount(const AccountInfo& accoInfo, const string& permissionCode, ostream& errorOs = cout);

    bool existSameUserName(const string& userName);
    bool existSamePhoneNum(const string& phoneNum);
    bool registerUserAccount(const AccountInfo& accoInfo, ostream& errorOs = cout);
    bool loginAccount(const string& userNameOrPhoneNum, const string& password, ostream& errorOs = cout);

    OrderGroup* getCustomerOrders (const string& phoneNum, ostream& errorOs = cout);
    OrderGroup* getAllOrders (ostream& errorOs = cout);
    OrderGroup* getDayOrders(Sakuno::Time *day, ostream &errorOs = cout);
    OrderInfo* getOrder(const string& trackNum, ostream& errorOs = cout);
    bool deleteSingleOrder(const string& trackNum, ostream& errorOs = cout);
    bool updateSingleOrder(const string& trackNum, const OrderInfo& newOrder, ostream& errorOs = cout);
    bool setHasTaken(const OrderInfo& order, bool ifTaken, ostream& errorOs = cout);

};

#endif //EXPRESSMANAGEMENTSYSTEM_DATABASESTATUS_H