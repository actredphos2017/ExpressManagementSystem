//
//  Create by sakunoakarinn on 22-12-01
//

#ifndef __GLOBAL_ATTRIBUTE_H__
#define __GLOBAL_ATTRIBUTE_H__

#include "SakunoFunctions.h"

#include "DataVisit/DatabaseInfo.h"
#include "DataVisit/DatabaseStatus.h"

#include "BussinessLogic/AccountInfo.h"
#include "BussinessLogic/OrderInfo.h"

#include <sstream>
#include <QDebug>

#define DB_INFO_FILENAME ".dbInfo"
#define PROGRAM_DATA_SAVE_DIR "/.ExpressManagementSystemSavement/"

#define SAKUNO_DEBUG_MODE true

using namespace std;

namespace Sakuno{
    extern DatabaseInfo* dbInfo;
    extern bool haveDBInfo;
    extern DatabaseStatus* databaseEntrance;
    extern bool connectSuccess;
    extern AccountInfo* onlineAccount;
} // namespace Sakuno

#endif // __GLOBAL_ATTRIBUTE_H__