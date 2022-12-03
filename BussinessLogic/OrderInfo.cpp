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
        hasBeenTaken(hasBeenTaken)
        {}

OrderInfo& OrderInfo::taken() {
    bool old = hasBeenTaken;
    hasBeenTaken = true;
    return *this;
}
