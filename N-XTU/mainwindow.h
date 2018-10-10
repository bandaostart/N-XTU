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
#include <QThread>
#include "leftwindow.h"
#include "rightwindow.h"
#include "serialdialog.h"
#include "serialthread.h"
#include "modulewindow.h"
#include "protocol.h"
#include "searchdialog.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QToolBar       *Tool_Bar;
    QMenuBar       *Menu_Bar;

    SearchDialog   search_dialog;
    LeftWindow     *left_window;
    RightWindow    *right_window;
    QSplitter      *splitter;


    SerialDialog   *Serial_Dialog;
    QHash<QString, ModuleDeal *>   Module_Deal_Hash;

    QTimer         *SerialTx_Timer;

    enum {ReadNodeID = 0, RfTransmit, RfReceive, CurrentTransmit, CurrentReceive, CurrentSleep, CrystalOsc};
    unsigned char  *Test_Run_State;



private:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void Creat_MenuBar();
    void Creat_ToolBar();
    void Creat_CentralWidget();
    void Creat_SerialTxTimer();
    void Set_WidgetAttributes();

    void Add_ModuleWindow_Deal();

    bool Port_Send_Deal(ModuleDeal *module_deal);
    void Port_Receive_Deal(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);


private slots:
    void Open_SerialDialog();
    void Close_ModuleWindow(const QString &portname);
    void Receive_SerialMessage(const QString &portname,  unsigned char *rx_data,  unsigned short rx_num);
    void Send_SerialMessage();
    void Close_SearchDialog(const QString &portname);

    void Radio_Test_Deal(const bool &state);

    void Application_Exit();


};


#endif // MAINWINDOW_H
