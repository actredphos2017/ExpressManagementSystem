//
//  Create by sakunoakarinn on 22-12-01
//

#ifndef __GLOBAL_ATTRIBUTE_H__
#define __GLOBAL_ATTRIBUTE_H__

#include "DataVisit/DatabaseInfo.h"
#include "DataVisit/DatabaseStatus.h"

#include "BussinessLogic/AccountInfo.h"
#include "BussinessLogic/OrderInfo.h"

#include <sstream>
#include <QDebug>

#define DB_INFO_FILENAME ".dbInfo"
#define PROGRAM_DATA_SAVE_DIR "/.ExpressManagementSystemSavement/" //从用户根目录开始

#define SAKUNO_DEBUG_MODE true

using namespace std;

namespace Sakuno{
    extern DatabaseInfo* dbInfo;
    extern bool haveDBInfo;
    extern DatabaseStatus* databaseEntrance;
    extern bool connectSuccess;
    extern AccountInfo* onlineAccount;

    static string getFileName(const string& fullDirName){
        stringstream ss;
        for(const char& it : fullDirName){
            ss << it;
            if(it == '/' || it == '\\')
                ss.clear();
        }
        return ss.str();
    }

    static string getFileType(const string& fullDirName){
        string fileName = getFileName(fullDirName);
        bool isContent = false;
        stringstream ss;
        for(const char& it : fileName){
            if(isContent)
                ss << it;
            if(it == '.'){
                isContent = true;
                ss.clear();
            }
        }
        return ss.str();
    }
} // namespace Sakuno

#endif // __GLOBAL_ATTRIBUTE_H__