#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include "leftwindow.h"
#include "rightwindow.h"
#include "serialdialog.h"
#include "serialthread.h"
#include "modulewindow.h"
#include "protocol.h"



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

    QTimer         *SerialTx_Timer;


private:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void Creat_MenuBar();
    void Creat_ToolBar();
    void Creat_CentralWidget();
    void Creat_SerialTxTimer();
    void Set_WidgetAttributes();

    void Add_Module_Deal();

    bool Port_Send_Deal(ModuleDeal *module_deal);
    void Port_Receive_Deal(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);


private slots:
    void Open_SerialDialog();
    void Delete_SerialPort(const QString &portname);
    void Receive_SerialPort(const QString &portname,  unsigned char *rx_data,  unsigned short rx_num);
    void Send_SerialPort();

    void Application_Exit();


};


#endif // MAINWINDOW_H
