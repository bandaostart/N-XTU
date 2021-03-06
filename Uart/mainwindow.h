#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "serialdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    SerialDialog                    Serial_Dialog;

    void creatActions();

private slots:
    void AddSerialPort();

private:
    Ui::MainWindow *ui;


};



#endif // MAINWINDOW_H
