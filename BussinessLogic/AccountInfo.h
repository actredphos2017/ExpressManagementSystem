//
// Created by sakunoakarinn on 22-11-29.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_ACCOUNTINFO_H
#define EXPRESSMANAGEMENTSYSTEM_ACCOUNTINFO_H

#include <string>
#include <vector>

using namespace std;

typedef enum{Customer, Waiter} AccountType;

class AccountInfo {
public:
    AccountInfo () = default;
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

typedef vector<AccountInfo> accountGroup;

#endif //EXPRESSMANAGEMENTSYSTEM_ACCOUNTINFO_H
