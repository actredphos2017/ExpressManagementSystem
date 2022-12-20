//
// Created by sakunoakarinn on 22-11-29.
//

#include "OrderInfo.h"

#include <utility>

OrderInfo::OrderInfo(string trackNumber,
                     string company,
                     string recipentName,
                     string recipentPhoneNum,
                     string recipentLocation,
                     int recipentPost,
                     string senderName,
                     string senderPhoneNum,
                     string senderLocation,
                     int senderPost,
                     float itemWeight,
                     string pickCode,
                     const string& warehousingTime,
                     bool hasBeenTaken):
    trackNumber(std::move(trackNumber)),
    company(std::move(company)),
    recipentName(std::move(recipentName)),
    recipentPhoneNum(std::move(recipentPhoneNum)),
    recipentLocation(std::move(recipentLocation)),
    recipentPost(recipentPost),
    senderName(std::move(senderName)),
    senderPhoneNum(std::move(senderPhoneNum)),
    senderLocation(std::move(senderLocation)),
    senderPost(senderPost),
    itemWeight(itemWeight),
    pickCode(std::move(pickCode)),
    warehousingTime(new Sakuno::Time(warehousingTime)),
    hasBeenTaken(hasBeenTaken){}

OrderGroup *selectOrder(const OrderGroup &oldOrders, bool search, const string& str){
    if(!search)
        return new OrderGroup(oldOrders);
    auto res = new OrderGroup;
    bool conform;
    for(const auto& it : oldOrders){
        conform =
                it.trackNumber.find(str)        != string::npos ||
                it.company.find(str)            != string::npos ||
                it.recipentName.find(str)       != string::npos ||
                it.recipentPhoneNum.find(str)   != string::npos ||
                it.recipentLocation.find(str)   != string::npos ||
                to_string(it.recipentPost).find(str)        != string::npos ||
                it.senderName.find(str)         != string::npos ||
                it.senderPhoneNum.find(str)     != string::npos ||
                it.senderLocation.find(str) != string::npos ||
                to_string(it.senderPost).find(str) != string::npos ||
                to_string(it.itemWeight).find(str) != string::npos ||
                it.pickCode.find(str) != string::npos ||
                it.warehousingTime->baseTime().find(str) != string::npos;
        if(conform)
            res->push_back(OrderInfo(it));
    }
    return res;
}

OrderGroup *typeOrder(const OrderGroup &oldOrders, bool ifSelect, bool hasBeenTaken){
    if(!ifSelect)
        return new OrderGroup(oldOrders);
    auto res = new OrderGroup;
    bool conform;
    for(const auto& it : oldOrders)
        if(it.hasBeenTaken == hasBeenTaken)
            res->push_back(OrderInfo(it));
    return res;
}