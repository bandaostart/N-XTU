#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QMessageBox>
#include "leftwindow.h"
#include "rightwindow.h"
#include "serialdialog.h"
#include "serialthread.h"
#include "modulewindow.h"




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QToolBar       *Tool_Bar;
    QMenuBar       *Menu_Bar;

    LeftWindow     *left_window;
    RightWindow    *right_window;
    QSplitter      *splitter;

    SerialDialog   *Serial_Dialog;
    QHash<QString, ModuleDeal *>   Module_Deal_Hash;


private:
    void paintEvent(QPaintEvent *event) override;

    void Creat_MenuBar();
    void Creat_ToolBar();
    void Creat_CentralWidget();


private slots:
    void Open_SerialDialog();
    void Delete_SerialPort(const QString &portname);
    void Application_Exit();


};


#endif // MAINWINDOW_H
