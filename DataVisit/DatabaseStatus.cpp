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
        errorOs << "错误！该数据库不符合要求！\n错误代码：" << e;
        Sakuno::close(dbCon);
        return false;
    }
    dbSta = dbCon->createStatement();
    return true;
}

bool DatabaseStatus::insertOrder(const OrderGroup &og, ostream &errorOs) {
    auto it = og.begin();
    stringstream prepareCommand;
    try {
        while (it != og.end()) {
            dbSta = dbCon->createStatement();

            prepareCommand << "insert into orderInfo values (";
            prepareCommand << Sakuno::toVarchar(it->trackNumber) << ", ";
            prepareCommand << Sakuno::toVarchar(it->company) << ", ";
            prepareCommand << Sakuno::toVarchar(it->recipentName) << ", ";
            prepareCommand << Sakuno::toVarchar(it->recipentPhoneNum) << ", ";
            prepareCommand << Sakuno::toVarchar(it->recipentLocation) << ", ";
            prepareCommand << it->recipentPost << ", ";
            prepareCommand << Sakuno::toVarchar(it->senderName) << ", ";
            prepareCommand << Sakuno::toVarchar(it->senderPhoneNum) << ", ";
            prepareCommand << Sakuno::toVarchar(it->senderLocation) << ", ";
            prepareCommand << it->senderPost << ", ";
            prepareCommand << it->itemWeight << ", ";
            prepareCommand << Sakuno::toVarchar(it->pickCode) << ", ";
            prepareCommand << it->warehousingTime->sqlTime() << ", ";
            prepareCommand << it->hasBeenTaken << ")";

            dbSta->execute(prepareCommand.str());

            it ++;
        }
    }catch(exception& e) {
        errorOs << prepareCommand.str() << endl;
        errorOs << "订单插入失败! 运单号重复或输入值错误!";
        dbCon->reconnect();
        return false;
    }
    dbCon->commit();
    return true;
}

bool DatabaseStatus::deleteOrder(const string &condition, ostream &errorOs) {
    if(condition.empty()){
        errorOs << "不带条件的删除是不安全的！";
        return false;
    }
    dbSta = dbCon->createStatement();
    try{
        dbSta->execute("delete from orderInfo where " + condition);
    }catch(exception& e){
        errorOs << "delete from orderInfo where " + condition << endl;
        errorOs << "删除失败，请检查语法！";
        return false;
    }
    dbCon->commit();
    return true;
}

OrderGroup* DatabaseStatus::selectOrder(const string& condition, ostream &errorOs) {
    qDebug() << ("select * from orderInfo where " + condition).c_str();
    dbSta = dbCon->createStatement();
    try{
        dbRes = condition.empty() ?
                dbSta->executeQuery("select * from orderInfo") :
                dbSta->executeQuery("select * from orderInfo where " + condition);
    }catch(exception& e){
        errorOs << "订单信息查找错误! 请查找语法!";
        return nullptr;
    }
    auto res = new OrderGroup;
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
                dbRes->getString(13).asStdString(),
                dbRes->getBoolean(14)
                ));
    }
    return res;
}

bool DatabaseStatus::updateOrder(const string& condition, const string& change, ostream &errorOs) {
    try{
        dbPreSta = dbCon->prepareStatement("update orderInfo set " + change + " where " + condition);
        dbPreSta->executeQuery();
    }catch(exception& e){
        errorOs << "update orderInfo set " + change + " where " + condition;
        errorOs << "订单关系数据更新错误! 请检查条件与改变表达式!";
        dbCon->reconnect();
        return false;
    }
    dbCon->commit();
    return true;
}

bool DatabaseStatus::insertAccount(const AccountGroup &ag, ostream &errorOs) {
    auto it = ag.begin();
    try {
        while (it != ag.end()) {

            dbPreSta = dbCon->prepareStatement("insert into account (isWaiter, userName, phoneNumber, password) values (?,?,?,?)");

            dbPreSta->setBoolean(1  , it->accountType == Waiter);
            dbPreSta->setString (2  , it->userName);
            dbPreSta->setString (3  , it->phoneNumber);
            dbPreSta->setString (4  , it->password);

            dbPreSta->executeUpdate();

            it ++;
        }
    }catch(exception& e) {
        errorOs << "用户插入失败! 输入值超出范围。";
        dbCon->reconnect();
        return false;
    }
    dbCon->commit();
    return true;
}

bool DatabaseStatus::deleteAccount(const string &condition, ostream &errorOs) {
    if(condition.empty()){
        errorOs << "不带条件的删除是不安全的！";
        return false;
    }
    dbSta = dbCon->createStatement();
    try{
        dbSta->execute("delete from account where " + condition);
    }catch(exception& e){
        errorOs << "delete from account where " + condition << endl;
        errorOs << "删除失败，请检查语法！";
        return false;
    }
    return true;
}

AccountGroup *DatabaseStatus::selectAccount(const string& condition, ostream &errorOs) {
    auto res = new AccountGroup;
    dbSta = dbCon->createStatement();
    try{
        dbRes = condition.empty() ?
                dbSta->executeQuery("select * from account") :
                dbSta->executeQuery("select * from account where " + condition);
    }catch(exception& e){
        errorOs << "用户信息查找错误! 请查找语法!";
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
    if(res->empty())
        errorOs << "暂无用户";
    return res;
}

bool DatabaseStatus::updateAccount(const string& condition, const string& change, ostream &errorOs) {
    try{
        dbPreSta = dbCon->prepareStatement("update account set " + change + " where " + condition);
        dbPreSta->executeQuery();
    }catch(exception& e){
        errorOs << "update account set " + change + " where " + condition << '\n';
        errorOs << "用户关系数据更新错误! 请检查条件与改变表达式!";
        dbCon->reconnect();
        return false;
    }
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

    AccountGroup ag;
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
        return "";
    }
    if(!dbRes->next()){
        errorOs << "管理员账户凭证错误";
        return "";
    }
    return dbRes->getString(1).asStdString();
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

    AccountGroup ag;
    ag.push_back(accoInfo);
    return insertAccount(ag, errorOs);
}

string DatabaseStatus::checkPermissionCode(const string& code, ostream &errorOs) {
    AccountGroup* ag = selectAccount("permissionCode = " + Sakuno::toVarchar(code) , errorOs);
    return ag->empty() ? "" : (*ag)[0].userName;
}

bool DatabaseStatus::checkPrepareAccount(const AccountInfo &accoInfo, ostream &errorOs, AccountInfo* oldAccount) {
    if (!accoInfo.userName.empty()) {
        if (!Sakuno::isLetter(accoInfo.userName[0])) {
            errorOs << "用户名不合法！";
            return false;
        }
        else if (existSameUserName(accoInfo.userName)) {
            if(oldAccount){
                if (accoInfo.userName != oldAccount->userName){
                    errorOs << "数据库中已存在相同用户名的账户！";
                    return false;
                }
            }else{
                errorOs << "数据库中已存在相同用户名的账户！";
                return false;
            }
        }
    }
    if(!accoInfo.phoneNumber.empty()) {
        if (!Sakuno::isNumber(accoInfo.phoneNumber[0])) {
            errorOs << "手机号不合法！";
            return false;
        }
        if (existSamePhoneNum(accoInfo.phoneNumber)) {
            if(oldAccount){
                if(accoInfo.phoneNumber != oldAccount->phoneNumber){
                    errorOs << "数据库中已存在相同手机号的账户！";
                    return false;
                }
            }else{
                errorOs << "数据库中已存在相同手机号的账户！";
                return false;
            }
        }
    }
    return true;
}

OrderGroup *DatabaseStatus::getCustomerOrders(const string &phoneNum, ostream &errorOs) {
    OrderGroup *res = selectOrder("recipentPhoneNum = " + Sakuno::toVarchar(phoneNum) + " or senderPhoneNum = " + Sakuno::toVarchar(phoneNum), errorOs);
    if(res != nullptr){
        if(res->empty())
            errorOs << "暂无包裹入库";
    }else
        res = new OrderGroup;
    return res;
}

OrderGroup *DatabaseStatus::getAllOrders(ostream &errorOs) {
    return selectOrder("true", errorOs);
}

OrderGroup *DatabaseStatus::getDayOrders(Sakuno::Time* day, ostream &errorOs) {
    stringstream prepareCondition;
    Sakuno::Time fromTime = *day;
    Sakuno::Time toTime = *day;
    fromTime.hour = fromTime.min = fromTime.second = 0;
    toTime.hour = 23;
    toTime.min = 59;
    toTime.second = 59;

    prepareCondition << "warehousingTime >= " << fromTime.sqlTime();
    prepareCondition << " and ";
    prepareCondition << "warehousingTime <= " << toTime.sqlTime();

    return selectOrder(prepareCondition.str()  , errorOs);
}

bool DatabaseStatus::setHasTaken(const OrderInfo &order, bool ifTaken, ostream &errorOs) {
    return updateOrder("trackNumber = " + order.trackNumber, "hasBeenTaken = " + to_string((int)ifTaken), errorOs);
}

OrderInfo *DatabaseStatus::getOrder(const string &trackNum, ostream &errorOs) {
    OrderGroup* resGroup = selectOrder("trackNumber = " + Sakuno::toVarchar(trackNum), errorOs);
    if(!resGroup)
        return nullptr;
    if(resGroup->empty()){
        errorOs << "指定快递不存在";
        return nullptr;
    }
    return &(*resGroup)[0];
}

bool DatabaseStatus::updateSingleOrder(const string &trackNum, const OrderInfo &newOrder, ostream &errorOs) {
    if(!getOrder(trackNum, errorOs))
        return false;
    stringstream changeInfo;
    changeInfo << "trackNumber = " + Sakuno::toVarchar(newOrder.trackNumber) + ", ";
    changeInfo << "company = " + Sakuno::toVarchar(newOrder.company) + ", ";
    changeInfo << "recipentName = " + Sakuno::toVarchar(newOrder.recipentName) + ", ";
    changeInfo << "recipentPhoneNum = " + Sakuno::toVarchar(newOrder.recipentPhoneNum) + ", ";
    changeInfo << "recipentLocation = " + Sakuno::toVarchar(newOrder.recipentLocation) + ", ";
    changeInfo << "recipentPost = " + Sakuno::toVarchar(to_string(newOrder.recipentPost)) + ", ";
    changeInfo << "senderName = " + Sakuno::toVarchar(newOrder.senderName) + ", ";
    changeInfo << "senderPhoneNum = " + Sakuno::toVarchar(newOrder.senderPhoneNum) + ", ";
    changeInfo << "senderLocation = " + Sakuno::toVarchar(newOrder.senderLocation) + ", ";
    changeInfo << "senderPost = " + Sakuno::toVarchar(to_string(newOrder.senderPost)) + ", ";
    changeInfo << "itemWeight = " + to_string(newOrder.itemWeight) + ", ";
    changeInfo << "pickCode = " + Sakuno::toVarchar(newOrder.pickCode) + ", ";
    changeInfo << "warehousingTime = " + newOrder.warehousingTime->sqlTime() + ", ";
    changeInfo << "hasBeenTaken = " + to_string((int)newOrder.hasBeenTaken);
    qDebug() << "ChangeInfo: " << changeInfo.str().c_str();
    if(!updateOrder("trackNumber = " + Sakuno::toVarchar(trackNum), changeInfo.str(), errorOs))
        return false;
    return true;
}

bool DatabaseStatus::deleteSingleOrder(const string &trackNum, ostream &errorOs) {
    if(!getOrder(trackNum, errorOs))
        return false;
    return deleteOrder("trackNumber = " + trackNum, errorOs);
}

vector<int> DatabaseStatus::warehousing_takenMap(Sakuno::Time *day, ostream &errorOs) {
    vector<int> res(4);
    auto dayOrder = getDayOrders(day, errorOs);
    auto allOrder = getAllOrders(errorOs);
    for(auto it : *dayOrder){
        res[1] ++;
        if(it.hasBeenTaken)
            res[0] ++;
    }
    for(auto it : *allOrder){
        res[3] ++;
        if(it.hasBeenTaken)
            res[2] ++;
    }
    return res;
}

OrderInfo *DatabaseStatus::getQuickOrder(const string &codeNum, ostream &errorOs) {
    OrderGroup* resGroup = selectOrder("pickCode = " + Sakuno::toVarchar(codeNum), errorOs);
    if(!resGroup)
        return nullptr;
    if(resGroup->empty()){
        errorOs << "指定快递不存在";
        return nullptr;
    }
    return &(*resGroup)[0];
}

AccountGroup* DatabaseStatus::getAllAccounts(ostream &errorOs) {
    return selectAccount("true", errorOs);
}

AccountInfo *DatabaseStatus::getAccount(const string &userName, const string &phoneNum, ostream &errorOs) {
    stringstream prepareCondition;
    if(!userName.empty())
        prepareCondition << "userName = " << Sakuno::toVarchar(userName);
    else
        prepareCondition << " true ";

    prepareCondition << " and ";

    if(!phoneNum.empty())
        prepareCondition << "phoneNumber = " << Sakuno::toVarchar(phoneNum);
    else
        prepareCondition << "true";

    AccountGroup* account = selectAccount(prepareCondition.str(), errorOs);
    if(account->empty() || account->size() > 1){
        errorOs << "查找错误！请检查输入值！";
        return nullptr;
    }
    return &(*account)[0];
}

bool DatabaseStatus::updateSingleAccount(const AccountInfo &oldInfo, const AccountInfo &newInfo, ostream &errorOs) {
    bool breakRootPower = oldInfo.userName == "root" && (newInfo.userName != "root" || newInfo.accountType != Waiter || !newInfo.phoneNumber.empty());
    if(breakRootPower){
        errorOs << "根管理员只能修改密码";
        return false;
    }

    stringstream prepareCondition, prepareChange;

    if(!oldInfo.userName.empty())
        prepareCondition << "userName = " << Sakuno::toVarchar(oldInfo.userName);
    else
        prepareCondition << " true ";

    prepareCondition << " and ";

    if(!oldInfo.phoneNumber.empty())
        prepareCondition << "phoneNumber = " << Sakuno::toVarchar(oldInfo.phoneNumber);
    else
        prepareCondition << "true";


    prepareChange << "password = " << Sakuno::toVarchar(newInfo.password);

    prepareChange << " , ";

    prepareChange << "isWaiter = " << (int)(newInfo.accountType == Waiter);

    prepareChange << " , ";

    if(!newInfo.userName.empty())
        prepareChange << "userName = " << Sakuno::toVarchar(newInfo.userName);
    else
        prepareChange << " true ";

    prepareChange << " , ";

    if(!newInfo.phoneNumber.empty())
        prepareChange << "phoneNumber = " << Sakuno::toVarchar(newInfo.phoneNumber);
    else
        prepareChange << "true";

    return updateAccount(prepareCondition.str(), prepareChange.str(), errorOs);
}
