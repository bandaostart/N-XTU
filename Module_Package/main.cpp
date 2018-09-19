#include "mainwindow.h"
#include <QApplication>

#include "consolewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    ConsoleWindow w;
    w.show();

    return a.exec();
}
