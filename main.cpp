//
//  Create by sakunoakarinn on 22-12-01
//

#include <QApplication>
#include "VisualWindows/loginDialog.h"
#include "VisualWindows/registerDialog.h"
#include "VisualWindows/databaseOption.h"
#include "VisualWindows/mainWindows/menuForCustomer.h"
#include "VisualWindows/mainWindows/menuForWaiter.h"

using namespace Qt;

int main(int argc, char *argv[]) {

    auto databaseEntrance = new databaseStatus;
    
    accountInfo* onlineAccount{};

    QApplication a(argc, argv);

    loginDialog     loginInterface;
    databaseOption  databaseConfigInterface;
    registerDialog  registerInterface;
    menuForCustomer customerMainMenu;
    menuForWaiter   waiterMainMenu;

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
    
    loginInterface.show();

    return QApplication::exec();
}
