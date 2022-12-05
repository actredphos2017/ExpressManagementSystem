//
// Created by sakunoakarinn on 22-11-29.
//
#include "../GlobalAttribute.h"

#include "DatabaseStatus.h"
#include <sstream>

namespace Sakuno{
    template<class T>
    void close(T* item){
        if(item == nullptr)
            return;
        item->close();
        delete item;
    }
}

bool DatabaseStatus::available() {
    if(dbCon == nullptr)
        return false;
    return !dbCon->isClosed();
}

bool DatabaseStatus::connect(const DatabaseInfo &dbi, ostream &errorOs) {
    dbDri = new mysql::MySQL_Driver;
    try{
        dbCon = dbDri->connect(dbi.hostName,
                               dbi.userName,
                               dbi.password);
    }catch(exception& e){
        errorOs << "连接失败！请检查数据库信息。";
#if SAKUNO_DEBUG_MODE
        qDebug() << dbi.hostName.c_str() << dbi.userName.c_str() << dbi.password.c_str();
#endif
        Sakuno::close(dbCon);
        return false;
    }
    try{
        Statement* tempSM = dbCon->createStatement();
        ResultSet* tempRS = tempSM->executeQuery("show databases");
        bool hasTargetDatabase = false;
        while(tempRS->next())
            if(tempRS->getString(1).asStdString() == "ExpressManagementSystem"){
                hasTargetDatabase = true;
                break;
            }
        if(!hasTargetDatabase)
            throw(1);
        tempSM->execute("use ExpressManagementSystem");
        tempRS = tempSM->executeQuery("show tables");
        bool hasTargetTable[2] = {false, false};
        while(tempRS->next()){
            if(tempRS->getString(1).asStdString() == "account")
                hasTargetTable[0] = true;
            else if(tempRS->getString(1).asStdString() == "orderInfo")
                hasTargetTable[1] = true;
            qDebug() << tempRS->getString(1).asStdString().c_str();
        }
        if(!hasTargetTable[0] || !hasTargetTable[1])
            throw(2);
    }catch(int e){
        errorOs << "错误！该数据库不符合要求！";
#if SAKUNO_DEBUG_MODE
        qDebug() << e;
#endif
        Sakuno::close(dbCon);
        return false;
    }
    dbSta = dbCon->createStatement();
    return true;
}
/*
drop table if exists OrderInfo;
create table OrderInfo(
    trackNumber varchar(20) not null,
    company varchar(10) not null,
    recipentName varchar(10) not null,
    recipentPhoneNum varchar(15) not null,
    recipentLocation varchar(15) not null,
    recipentPost int,
    senderName varchar(10) not null,
    senderPhoneNum varchar(15) not null,
    senderLocation varchar(15) not null,
    senderPost int,
    itemWeight float,
    pickCode varchar(10),
    warehousingTime datetime default now(),
    hasBeenTaken boolean default true,
    primary key(trackNumber),
    index(pickCode)
)engine=InnoDB, charset=utf8;
 */

bool DatabaseStatus::insertOrder(const orderGroup &og, ostream &errorOs) {
    auto it = og.begin();
    try {
        while (it != og.end()) {

            dbPreSta = dbCon->prepareStatement("insert into OrderInfo ("
                                                    "trackNumber, "
                                                    "company, "
                                                    "recipentName, "
                                                    "recipentPhoneNum, "
                                                    "recipentLocation, "
                                                    "recipentPost, "
                                                    "senderName, "
                                                    "senderPhoneNum, "
                                                    "senderLocation, "
                                                    "senderPost, "
                                                    "itemWeight, "
                                                    "pickCode, "
                                                    "hasBeenTaken"
                                                    ") values (?,?,?,?,?,?,?,?,?,?,?,?,?)");

            dbPreSta->setString (1  , it->trackNumber);
            dbPreSta->setString (2  , it->company);
            dbPreSta->setString (3  , it->recipentName);
            dbPreSta->setString (4  , it->recipentPhoneNum);
            dbPreSta->setString (5  , it->recipentLocation);
            dbPreSta->setInt    (6  , it->recipentPost);
            dbPreSta->setString (7  , it->senderName);
            dbPreSta->setString (8  , it->senderPhoneNum);
            dbPreSta->setString (9  , it->senderLocation);
            dbPreSta->setInt    (10 , it->senderPost);
            dbPreSta->setDouble (11 , it->itemWeight);
            dbPreSta->setString (12 , it->pickCode);
            dbPreSta->setBoolean(13 , it->hasBeenTaken);

            dbPreSta->executeUpdate();

            //Sakuno::close(dbPreSta);

            it ++;
        }
    }catch(exception& e) {
        errorOs << "订单插入失败! 运单号重复!";
        dbCon->reconnect();
        return false;
    }
    dbCon->commit();
    return true;
}

orderGroup* DatabaseStatus::selectOrder(const string& condition, ostream &errorOs) {
    dbSta = dbCon->createStatement();
    try{
        dbRes = condition.empty() ?
                dbSta->executeQuery("select * from OrderInfo") :
                dbSta->executeQuery("select * from OrderInfo where " + condition);
    }catch(exception& e){
        errorOs << "订单信息查找错误! 请查找语法!";
        //Sakuno::close(dbRes);
        return new orderGroup;
    }
    auto res = new orderGroup;
    while(dbRes->next()){
        res->push_back(OrderInfo(
                dbRes->getString(1).asStdString(),
                dbRes->getString(2).asStdString(),
                dbRes->getString(3).asStdString(),
                dbRes->getString(4).asStdString(),
                dbRes->getString(5).asStdString(),
                dbRes->getInt(6),
                dbRes->getString(7).asStdString(),
                dbRes->getString(8).asStdString(),
                dbRes->getString(9).asStdString(),
                dbRes->getInt(10),
                (float)dbRes->getDouble(11),
                dbRes->getString(12).asStdString(),
                dbRes->getBoolean(13)
                ));
    }
    //Sakuno::close(dbRes);
    return res;
}

bool DatabaseStatus::updateOrder(const string& condition, const string& change, ostream &errorOs) {
    try{
        dbPreSta = dbCon->prepareStatement("update OrderInfo set " + change + " where " + condition);
        dbPreSta->executeQuery();
    }catch(exception& e){
        errorOs << "订单关系数据更新错误! 请检查条件与改变表达式!";
        //Sakuno::close(dbPreSta);
        dbCon->reconnect();
        return false;
    }
    //Sakuno::close(dbPreSta);
    dbCon->commit();
    return true;
}

bool DatabaseStatus::insertAccount(const accountGroup &ag, ostream &errorOs) {
    auto it = ag.begin();
    try {
        while (it != ag.end()) {

            dbPreSta = dbCon->prepareStatement("insert into account (isWaiter, userName, phoneNumber, password) values (?,?,?,?)");

            dbPreSta->setBoolean(1  , it->accountType == Waiter);
            dbPreSta->setString (2  , it->userName);
            dbPreSta->setString (3  , it->phoneNumber);
            dbPreSta->setString (4  , it->password);

            dbPreSta->executeUpdate();

            //Sakuno::close(dbPreSta);

            it ++;
        }
    }catch(exception& e) {
        errorOs << "用户插入失败! 用户名与电话重复!";
        dbCon->reconnect();
        return false;
    }
    dbCon->commit();
    return true;
}

accountGroup *DatabaseStatus::selectAccount(const string& condition, ostream &errorOs) {
    auto res = new accountGroup;
    dbSta = dbCon->createStatement();
    try{
        dbRes = condition.empty() ?
                dbSta->executeQuery("select * from account") :
                dbSta->executeQuery("select * from account where " + condition);
    }catch(exception& e){
        errorOs << "用户信息查找错误! 请查找语法!";
        //Sakuno::close(dbRes);
        return res;
    }
    while(dbRes->next()){
        AccountInfo accoInfo;
        if(dbRes->getBoolean(1))
            accoInfo.setWaiterAccount(dbRes->getString(2).asStdString(),
                                      dbRes->getString(3).asStdString(),
                                      dbRes->getString(4).asStdString());
        else
            accoInfo.setCustomerAccount(dbRes->getString(2).asStdString(),
                                        dbRes->getString(3).asStdString(),
                                        dbRes->getString(4).asStdString());
        res->push_back(accoInfo);
    }
    //Sakuno::close(dbRes);
    //Sakuno::close(dbSta);
    return res;
}

bool DatabaseStatus::updateAccount(const string& condition, const string& change, ostream &errorOs) {
    try{
        dbPreSta = dbCon->prepareStatement("update account set " + change + " where " + condition);
        dbPreSta->executeQuery();
    }catch(exception& e){
        errorOs << "用户关系数据更新错误! 请检查条件与改变表达式!";
        //Sakuno::close(dbPreSta);
        dbCon->reconnect();
        return false;
    }
    //Sakuno::close(dbPreSta);
    dbCon->commit();
    return true;
}


bool DatabaseStatus::existSameUserName(const string &userName) {
    return !selectAccount("userName = " + Sakuno::toVarchar(userName))->empty();
}

bool DatabaseStatus::existSamePhoneNum(const string &phoneNum) {
    return !selectAccount("phoneNumber = " + Sakuno::toVarchar((phoneNum)))->empty();
}

bool DatabaseStatus::registerUserAccount(const AccountInfo &accoInfo, ostream& errorOs) {
    if(accoInfo.accountType == Waiter){
        errorOs << "这是用于注册普通用户的函数！";
        return false;
    }

    if(!checkPrepareAccount(accoInfo, errorOs)){
        return false;
    }

    accountGroup ag;
    ag.push_back(accoInfo);
    return insertAccount(ag, errorOs);
}

bool DatabaseStatus::loginAccount(const string &userNameOrPhoneNum, const string &password, ostream &errorOs) {
    if(Sakuno::isNumber(userNameOrPhoneNum[0])){
        AccountInfo realInfo;
        try{
            realInfo = (*selectAccount("phoneNumber = " + Sakuno::toVarchar(userNameOrPhoneNum)))[0];
        }catch(exception& e){
            errorOs << "用户名不存在";
            return false;
        }
        if(password == realInfo.password){
            Sakuno::onlineAccount = new AccountInfo(realInfo);
            return true;
        }
    }else if(Sakuno::isLetter(userNameOrPhoneNum[0])){
        AccountInfo realInfo;
        try{
            realInfo = (*selectAccount("userName = " + Sakuno::toVarchar(userNameOrPhoneNum)))[0];
        }catch(exception& e){
            errorOs << "用户名不存在";
            return false;
        }
        if(password == realInfo.password){
            Sakuno::onlineAccount = new AccountInfo(realInfo);
            return true;
        }
    }else errorOs << "账户名不合法！";
    return false;
}

string DatabaseStatus::getPermissionCode(const AccountInfo &waiterInfo, ostream &errorOs) {
    if(waiterInfo.accountType != Waiter){
        errorOs << "该账户不为管理员";
        return "";
    }

    try{
        dbPreSta = dbCon->prepareStatement(
                "select permissionCode from account where (userName = ? or phoneNumber = ?) and password = ?"
                );
        dbPreSta->setString(1, waiterInfo.userName);
        dbPreSta->setString(2, waiterInfo.phoneNumber);
        dbPreSta->setString(3, waiterInfo.password);
        dbRes = dbPreSta->executeQuery();
    }catch(exception& e){
        errorOs << "输入值错误，请检查输入值";
        //Sakuno::close(dbRes);
        return "";
    }
    if(!dbRes->next()){
        errorOs << "管理员账户凭证错误";
        return "";
    }
    return dbRes->getString(1).asStdString();
    //Sakuno::close(dbRes);
    //Sakuno::close(dbSta);
}

bool DatabaseStatus::registerWaiterAccount(const AccountInfo &accoInfo, const string &permissionCode, ostream &errorOs) {
    if(accoInfo.accountType == Customer){
        errorOs << "这是用于注册管理员的函数！";
        return false;
    }
    if(selectAccount("permissionCode = " + Sakuno::toVarchar(permissionCode), errorOs)->empty()){
        errorOs << "认证码错误，可能提供认证的管理员已经注销账户";
        return false;
    }

    if(!checkPrepareAccount(accoInfo, errorOs)){
        return false;
    }

    accountGroup ag;
    ag.push_back(accoInfo);
    return insertAccount(ag, errorOs);
}

string DatabaseStatus::checkPermissionCode(const string& code, ostream &errorOs) {
    accountGroup* ag = selectAccount("permissionCode = " + Sakuno::toVarchar(code) , errorOs);
    return ag->empty() ? "" : (*ag)[0].userName;
}

bool DatabaseStatus::checkPrepareAccount(const AccountInfo &accoInfo, ostream &errorOs) {
    if(!Sakuno::isLetter(accoInfo.userName[0])){
        errorOs << "用户名不合法！";
        return false;
    }
    if(existSameUserName(accoInfo.userName)){
        errorOs << "数据库中已存在相同用户名的账户！";
        return false;
    }
    if(!Sakuno::isNumber(accoInfo.phoneNumber[0])){
        errorOs << "手机号不合法！";
        return false;
    }
    if(existSamePhoneNum(accoInfo.phoneNumber)){
        errorOs << "数据库中已存在相同手机号的账户！";
        return false;
    }
    return true;
}