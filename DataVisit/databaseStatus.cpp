//
// Created by sakunoakarinn on 22-11-29.
//

#include "databaseStatus.h"
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

bool databaseStatus::available() {
    if(dbCon == nullptr)
        return false;
    return !dbCon->isClosed();
}

bool databaseStatus::connect(const databaseInfo &dbi, ostream &errorOs) {
    dbDri = new mysql::MySQL_Driver;
    try{
        dbCon = dbDri->connect(dbi.hostName,
                               dbi.userName,
                               dbi.password);
    }catch(exception& e){
        errorOs << "连接失败！请检查数据库信息。";
        return false;
    }
    dbSta = dbCon->createStatement();
    return true;
}

bool databaseStatus::insertOrder(const orderGroup &og, ostream &errorOs) {
    auto it = og.begin();
    try {
        while (it != og.end()) {

            dbPreSta = dbCon->prepareStatement("insert into orderInfo values (?,?,?,?,?,?,?,?,?,?,?,?,?)");

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

            Sakuno::close(dbPreSta);

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

orderGroup* databaseStatus::selectOrder(const string& condition, ostream &errorOs) {
    orderInfo* oi;
    dbSta = dbCon->createStatement();
    try{
        dbRes = condition.empty() ?
                dbSta->executeQuery("select * from orderInfo") :
                dbSta->executeQuery("select * from orderInfo where " + condition);
    }catch(exception& e){
        errorOs << "订单信息查找错误! 请查找语法!";
        Sakuno::close(dbRes);
        return new orderGroup;
    }
    auto res = new orderGroup;
    while(dbRes->next()){
        res->push_back(orderInfo(
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
    Sakuno::close(dbRes);
    return res;
}

bool databaseStatus::updateOrder(const string& condition, const string& change, ostream &errorOs) {
    try{
        dbPreSta = dbCon->prepareStatement("update orderInfo set " + change + " where " + condition);
        dbPreSta->executeQuery();
    }catch(exception& e){
        errorOs << "订单关系数据更新错误! 请检查条件与改变表达式!";
        Sakuno::close(dbPreSta);
        dbCon->reconnect();
        return false;
    }
    Sakuno::close(dbPreSta);
    dbCon->commit();
    return true;
}

bool databaseStatus::insertAccount(const accountGroup &ag, ostream &errorOs) {
    auto it = ag.begin();
    try {
        while (it != ag.end()) {

            dbPreSta = dbCon->prepareStatement("insert into account values (?,?,?,?)");

            dbPreSta->setBoolean(1  , it->accountType == Waiter);
            dbPreSta->setString (2  , it->userName);
            dbPreSta->setString (3  , it->phoneNumber);
            dbPreSta->setString (4  , it->password);

            dbPreSta->executeUpdate();

            Sakuno::close(dbPreSta);

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

accountGroup *databaseStatus::selectAccount(const string& condition, ostream &errorOs) {
    orderInfo* oi;
    dbSta = dbCon->createStatement();
    try{
        dbRes = condition.empty() ?
                dbSta->executeQuery("select * from account") :
                dbSta->executeQuery("select * from account where " + condition);
    }catch(exception& e){
        errorOs << "订单信息查找错误! 请查找语法!";
        Sakuno::close(dbRes);
        return new accountGroup;
    }
    auto res = new accountGroup;
    while(dbRes->next()){
        accountInfo accoInfo;
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
    Sakuno::close(dbRes);
    return res;
}

bool databaseStatus::updateAccount(const string& condition, const string& change, ostream &errorOs) {
    try{
        dbPreSta = dbCon->prepareStatement("update account set " + change + " where " + condition);
        dbPreSta->executeQuery();
    }catch(exception& e){
        errorOs << "用户关系数据更新错误! 请检查条件与改变表达式!";
        Sakuno::close(dbPreSta);
        dbCon->reconnect();
        return false;
    }
    Sakuno::close(dbPreSta);
    dbCon->commit();
    return true;
}
