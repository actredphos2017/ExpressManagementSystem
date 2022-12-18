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
    void setCustomerAccount(const string &pn,
                            const string &pw);

    void setCustomerAccount(const string &un,
                            const string &pn,
                            const string &pw);

    void setWaiterAccount(const string &un,
                          const string &pw);

    void setWaiterAccount(const string &un,
                          const string &pn,
                          const string &pw);
public:
    AccountType accountType = Customer;
    string userName;
    string phoneNumber;
    string password;
};

typedef vector<AccountInfo> AccountGroup;

#endif //EXPRESSMANAGEMENTSYSTEM_ACCOUNTINFO_H
