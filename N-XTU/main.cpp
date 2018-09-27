#include "mainwindow.h"
#include <QApplication>

#include "searchdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
//    w.show();

    SearchDialog w;
    w.show();

    return a.exec();
}
