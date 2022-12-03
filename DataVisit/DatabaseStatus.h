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

    bool insertAccount (const accountGroup& ag, ostream& errorOs);
    accountGroup* selectAccount (const string& condition, ostream &errorOs);
    bool updateAccount (const string& condition, const string& change, ostream &errorOs);

    bool insertOrder (const orderGroup& og, ostream &errorOs);
    orderGroup* selectOrder (const string& condition, ostream &errorOs);
    bool updateOrder (const string& condition, const string& change, ostream &errorOs);
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASESTATUS_H
