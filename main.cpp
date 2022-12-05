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
    DatabaseOption  databaseConfigInterface;
    RegisterDialog  registerInterface;
    PermissionGetDialog authenticateInterface;
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

        QObject::connect(
                &registerInterface,
                SIGNAL(toAuthenticate()),
                &authenticateInterface,
                SLOT(toAuthenticate())
        ); //连接注册界面与认证界面

        QObject::connect(
                &authenticateInterface,
                SIGNAL(comeBack()),
                &registerInterface,
                SLOT(comeBack())
        ); //连接注册界面与认证界面

        QObject::connect (
                &registerInterface,
                SIGNAL(pushBackBtn()),
                &loginInterface,
                SLOT(comeBack())
        ); //返回登录界面

        QObject::connect (
                &loginInterface,
                SIGNAL(pushDatabaseConfBtn()),
                &databaseConfigInterface,
                SLOT(toConfigDatabase())
        ); //连接登录界面与数据库配置界面

        QObject::connect (
                &databaseConfigInterface,
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
    }

    //初始化窗体数据传递
    {
        QObject::connect (
                &loginInterface,
                SIGNAL(checkSaveDBInfo()),
                &databaseConfigInterface,
                SLOT(checkSave())
        );
        QObject::connect(
                &databaseConfigInterface,
                SIGNAL(checkFinish()),
                &loginInterface,
                SLOT(checkResult())
        );
        QObject::connect(
                &authenticateInterface,
                SIGNAL(getPermissionCode(string, string)),
                &registerInterface,
                SLOT(authenticateSuccess(string, string))
        );
    }

    //loginInterface.init();
    customerMainMenu.show();
    return QApplication::exec();
}
