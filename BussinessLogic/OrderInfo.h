//
// Created by sakunoakarinn on 22-11-29.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_ORDERINFO_H
#define EXPRESSMANAGEMENTSYSTEM_ORDERINFO_H

#include <string>
#include <sstream>
#include <vector>
#include <QDebug>

using namespace std;

#include "../SakunoFunctions.h"

class OrderInfo {
public:
    OrderInfo () = default;
    OrderInfo (string trackNumber,
               string company,
               string recipentName,
               string recipentPhoneNum,
               string recipentLocation,
               int recipentPost,
               string senderName,
               string senderPhoneNum ,
               string senderLocation,
               int senderPost,
               float itemWeight,
               string pickCode,
               const string& warehousingTime,
               bool hasBeenTaken);
public:
    string trackNumber;
    string company;
    string recipentName;
    string recipentPhoneNum;
    string recipentLocation;
    int recipentPost{};
    string senderName;
    string senderPhoneNum;
    string senderLocation;
    int senderPost{};
    float itemWeight{};
    Sakuno::Time* warehousingTime;
    string pickCode;
    bool hasBeenTaken{};
};

typedef vector<OrderInfo> OrderGroup;

#endif //EXPRESSMANAGEMENTSYSTEM_ORDERINFO_H
