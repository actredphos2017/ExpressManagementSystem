//
// Created by sakunoakarinn on 22-11-29.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_ACCOUNTINFO_H
#define EXPRESSMANAGEMENTSYSTEM_ACCOUNTINFO_H

#include <string>

using namespace std;

typedef enum{Customer, Waiter} AccountType;

class accountInfo {
public:
    accountInfo () = default;
    void setCustomerAccount(const string &, const string &);
    void setCustomerAccount(const string &, const string &, const string &);
    void setWaiterAccount(const string &, const string &);
    void setWaiterAccount(const string &, const string &, const string &);
public:
    AccountType accountType = Customer;
    string userName;
    string phoneNumber;
    string password;
};


#endif //EXPRESSMANAGEMENTSYSTEM_ACCOUNTINFO_H
