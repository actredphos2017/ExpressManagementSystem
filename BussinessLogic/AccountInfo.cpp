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