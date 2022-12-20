//
//  Create by sakunoakarinn on 22-12-01
//

#include "DataVisit/DatabaseInfo.h"
#include "DataVisit/DatabaseStatus.h"

#include "BussinessLogic/AccountInfo.h"
#include "BussinessLogic/OrderInfo.h"


namespace Sakuno{
    DatabaseInfo* dbInfo = new DatabaseInfo;
    bool haveDBInfo = false;
    DatabaseStatus* databaseEntrance = new DatabaseStatus;
    bool connectSuccess = new AccountInfo;
    AccountInfo* onlineAccount = nullptr;
}

#include <QApplication>
#include "VisualWindows/LoginDialog.h"
#include "VisualWindows/RegisterDialog.h"
#include "VisualWindows/DatabaseOption.h"
#include "VisualWindows/PermissionGetDialog.h"
#include "VisualWindows/mainWindows/MenuForCustomer.h"
#include "VisualWindows/mainWindows/MenuForWaiter.h"

using namespace Qt;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LoginDialog     loginInterface;

    RegisterDialog  registerInterface;
    MenuForCustomer customerMainMenu;
    MenuForWaiter   waiterMainMenu;

    //初始化全局变量
    {
        Sakuno::dbInfo = new DatabaseInfo;
        Sakuno::haveDBInfo = false;
        Sakuno::databaseEntrance = new DatabaseStatus;
        Sakuno::connectSuccess = false;
        Sakuno::onlineAccount = new AccountInfo;
    }

    //初始化窗口呼出连接
    {
        QObject::connect (
                &loginInterface,
                SIGNAL(pushRegisterBtn()),
                &registerInterface,
                SLOT(toRegister())
        ); //连接登录界面与注册界面

        QObject::connect (
                &registerInterface,
                SIGNAL(pushBackBtn()),
                &loginInterface,
                SLOT(comeBack())
        ); //返回登录界面

        QObject::connect (
                &loginInterface,
                SIGNAL(customerLoginSuccess()),
                &customerMainMenu,
                SLOT(loginSuccess())
        ); //用户登录成功

        QObject::connect (
                &loginInterface,
                SIGNAL(waiterLoginSuccess()),
                &waiterMainMenu,
                SLOT(loginSuccess())
        ); //服务员登录成功

        QObject::connect (
                waiterMainMenu.settingWin,
                SIGNAL(toLeave()),
                &loginInterface,
                SLOT(comeback())
        );
        QObject::connect (
                customerMainMenu.settingWin,
                SIGNAL(toLeave()),
                &loginInterface,
                SLOT(comeback())
        );
    }

    loginInterface.init();
    //customerMainMenu.show();
    return QApplication::exec();
}
