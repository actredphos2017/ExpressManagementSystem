//
// Created by sakunoakarinn on 22-11-29.
//

#include "AccountInfo.h"

void AccountInfo::setCustomerAccount(const string &pn,
                                     const string &pw) {
    accountType = Customer;
    userName = "";
    phoneNumber = pn;
    password = pw;
}

void AccountInfo::setCustomerAccount(const string &un,
                                     const string &pn,
                                     const string &pw) {
    accountType = Customer;
    userName = un;
    phoneNumber = pn;
    password = pw;
}

void AccountInfo::setWaiterAccount(const string &un,
                                   const string &pw) {
    accountType = Waiter;
    userName = un;
    phoneNumber = "";
    password = pw;
}

void AccountInfo::setWaiterAccount(const string &un,
                                   const string &pn,
                                   const string &pw) {
    accountType = Waiter;
    userName = un;
    phoneNumber = pn;
    password = pw;
}

bool AccountInfo::operator==(const AccountInfo &account) {
    return (userName == account.userName && phoneNumber == account.phoneNumber);
}

AccountGroup *selectAccounts(const AccountGroup& oldAccount, bool ifSearch, const string& str){
    if(!ifSearch)
        return new AccountGroup(oldAccount);
    auto res = new AccountGroup;
    bool conform;
    for(const auto& it : oldAccount){
        conform =
                it.phoneNumber.find(str) != string::npos ||
                it.userName.find(str) != string::npos;
        if(conform)
            res->push_back(AccountInfo(it));
    }
    return res;
}

AccountGroup *typeAccounts(const AccountGroup& oldAccount, bool ifSearch, AccountType type){
    if(!ifSearch)
        return new AccountGroup(oldAccount);
    auto res = new AccountGroup;
    bool conform;
    for(const auto& it : oldAccount)
        if(it.accountType == type)
            res->push_back(AccountInfo(it));
    return res;
}