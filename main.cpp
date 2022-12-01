#include <QApplication>
#include "VisualWindows/loginDialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    loginDialog programEntrance;
    programEntrance.show();
    return QApplication::exec();
}
