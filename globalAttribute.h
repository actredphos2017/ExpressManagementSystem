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

class globalAttribute{
public:
    static databaseStatus* databaseEntrance;
    static accountInfo* onlineAccount;
};

databaseStatus* globalAttribute::databaseEntrance = new databaseStatus;
accountInfo*    globalAttribute::onlineAccount = null;

} // namespace Sakuno

#endif // __GLOBAL_ATTRIBUTE_H__