//
// Created by sakunoakarinn on 22-11-29.
//

#ifndef EXPRESSMANAGEMENTSYSTEM_ORDERINFO_H
#define EXPRESSMANAGEMENTSYSTEM_ORDERINFO_H

#include <string>
#include <vector>

using namespace std;

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
               bool hasBeenTaken);
    OrderInfo& taken();
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
    string pickCode;
    bool hasBeenTaken{};
};

typedef vector<OrderInfo> orderGroup;

#endif //EXPRESSMANAGEMENTSYSTEM_ORDERINFO_H
