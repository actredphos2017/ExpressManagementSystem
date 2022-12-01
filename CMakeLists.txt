cmake_minimum_required(VERSION 3.23)
project(ExpressManagementSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/Qt/6.4.1/gcc_64")
set(FULL_DIR_TO_CPP_SQL_CONNECTOR /home/sakunoakarinn/ProjectLibrarys/mysql-connector-c++-8.0.31-64)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(ExpressManagementSystem main.cpp DataVisit/databaseStatus.cpp DataVisit/databaseStatus.h DataVisit/databaseInfo.cpp DataVisit/databaseInfo.h BussinessLogic/orderInfo.cpp BussinessLogic/orderInfo.h BussinessLogic/accountInfo.cpp BussinessLogic/accountInfo.h VisualWindows/loginDialog.cpp VisualWindows/loginDialog.h VisualWindows/databaseOption.cpp VisualWindows/databaseOption.h VisualWindows/registerDialog.cpp VisualWindows/registerDialog.h VisualWindows/mainWindows/menuForWaiter.cpp VisualWindows/mainWindows/menuForWaiter.h VisualWindows/mainWindows/menuForCustomer.cpp VisualWindows/mainWindows/menuForCustomer.h VisualWindows/userObjects/ClickableLabel.h)
target_link_libraries(ExpressManagementSystem
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ${FULL_DIR_TO_CPP_SQL_CONNECTOR}/lib64/libmysqlcppconn.so
        )

target_include_directories(ExpressManagementSystem PRIVATE ${FULL_DIR_TO_CPP_SQL_CONNECTOR}/include/jdbc)