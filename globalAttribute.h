//
//  Create by sakunoakarinn on 22-12-01
//

#ifndef __GLOBAL_ATTRIBUTE_H__
#define __GLOBAL_ATTRIBUTE_H__

#include "DataVisit/databaseInfo.h"
#include "DataVisit/databaseStatus.h"

#include "BussinessLogic/accountInfo.h"
#include "BussinessLogic/orderInfo.h"

namespace Sakuno{
    static databaseStatus* databaseEntrance = new databaseStatus;
    static accountInfo* onlineAccount = nullptr;;
} // namespace Sakuno

#endif // __GLOBAL_ATTRIBUTE_H__