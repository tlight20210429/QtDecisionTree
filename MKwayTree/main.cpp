#include "mainwindow.h"
#include "filedeal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<ValueDef>("ValueDef");
    qRegisterMetaType<ValueDef>("ValueDef&");
    MainWindow w;
    w.show();
    return a.exec();
}
