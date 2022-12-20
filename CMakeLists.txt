cmake_minimum_required(VERSION 3.22.1)
project(ExpressManagementSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/sakuno/Qt/6.4.1/gcc_64")
set(FULL_DIR_TO_CPP_SQL_CONNECTOR /home/sakuno/RequiredLibrarys/mysql-connector-c++-8.0.31-linux-glibc2.27-x86-64bit)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(
        ExpressManagementSystem 
        main.cpp
        GlobalAttribute.h
        DataVisit/DatabaseStatus.cpp
        DataVisit/DatabaseStatus.h
        DataVisit/DatabaseInfo.cpp
        DataVisit/DatabaseInfo.h
        BussinessLogic/OrderInfo.cpp
        BussinessLogic/OrderInfo.h
        BussinessLogic/AccountInfo.cpp
        BussinessLogic/AccountInfo.h
        VisualWindows/LoginDialog.cpp
        VisualWindows/LoginDialog.h
        VisualWindows/LoginDialog.ui
        VisualWindows/DatabaseOption.cpp
        VisualWindows/DatabaseOption.h
        VisualWindows/RegisterDialog.cpp
        VisualWindows/RegisterDialog.h
        VisualWindows/RegisterDialog.ui
        VisualWindows/mainWindows/MenuForWaiter.cpp
        VisualWindows/mainWindows/MenuForWaiter.h
        VisualWindows/mainWindows/MenuForWaiter.ui
        VisualWindows/mainWindows/MenuForCustomer.cpp
        VisualWindows/mainWindows/MenuForCustomer.h
        VisualWindows/mainWindows/MenuForCustomer.ui
        VisualWindows/userObjects/ClickableLabel.h
        VisualWindows/PermissionGetDialog.cpp
        VisualWindows/PermissionGetDialog.h
        res.qrc
        VisualWindows/userObjects/PickupQuickTag.cpp
        VisualWindows/userObjects/PickupQuickTag.h
        SakunoFunctions.cpp SakunoFunctions.h
        VisualWindows/userObjects/CircleProgressBar.cpp
        VisualWindows/userObjects/CircleProgressBar.h
        VisualWindows/mainWindows/WaiterExtraWindows/WaiterExpressEditWindow.cpp VisualWindows/mainWindows/WaiterExtraWindows/WaiterExpressEditWindow.h VisualWindows/mainWindows/WaiterExtraWindows/WaiterExpressEditWindow.ui VisualWindows/mainWindows/WaiterExtraWindows/ExpressEdit.cpp VisualWindows/mainWindows/WaiterExtraWindows/ExpressEdit.h VisualWindows/mainWindows/WaiterExtraWindows/AccountEditWindow.cpp VisualWindows/mainWindows/WaiterExtraWindows/AccountEditWindow.h VisualWindows/mainWindows/WaiterExtraWindows/AccountEditWindow.ui VisualWindows/mainWindows/WaiterExtraWindows/AccountEdit.cpp VisualWindows/mainWindows/WaiterExtraWindows/AccountEdit.h)

target_link_libraries(ExpressManagementSystem
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ${FULL_DIR_TO_CPP_SQL_CONNECTOR}/lib64/libmysqlcppconn.so
        )

target_include_directories(ExpressManagementSystem PRIVATE ${FULL_DIR_TO_CPP_SQL_CONNECTOR}/include/jdbc)
