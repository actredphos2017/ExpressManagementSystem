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

#include "databaseInfo.h"
#include "../BussinessLogical/orderInfo.h"

using namespace std;
using namespace sql;

class databaseStatus {
private:
    Driver *dbDri;
    Connection *dbCon;
    Statement *dbSta;
    PreparedStatement *dbPreSta;
    ResultSet *dbRes;
public:
    databaseStatus ();
    databaseStatus (const databaseInfo& dbi);
    bool connect(const databaseInfo& dbi);
    bool available ();
    void insertOrder (const orderGroup& og);
    orderGroup& selectOrder (string condition);
};


#endif //EXPRESSMANAGEMENTSYSTEM_DATABASESTATUS_H
