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

signals:
    void Signal_ModuleStateChange_ToConsoleWin(bool add_delete, QString portname, QString noidtype);

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
    QTimer         *Test_Run_Timer;

    enum {NullState = 0, ReadNodeID, RfTransmit, RfReceive, CurrentTransmit, CurrentReceive, CurrentSleep, CrystalOsc};
    unsigned char  Test_Run_State;
    unsigned int   Test_Run_Num;

    QString        DM_PortName;
    QString        DP_PortName;
    int            Rf_Tx_Count;
    int            Rf_Rx_Count;
    int8_t         Rssi;
    int            Rssi_Sum;


private:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void Creat_MenuBar();
    void Creat_ToolBar();
    void Creat_CentralWidget();
    void Creat_User_Timer();
    void Set_WidgetAttributes();
    void Init_Window_Para();
    void Open_Serial_Deal();

    bool Port_Send_Deal(ModuleDeal *module_deal);
    void Port_Receive_Deal(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);


private slots:
    void Open_SerialDialog();
    void Close_ModuleWindow(const QString &portname);
    void Receive_SerialMessage(const QString &portname,  unsigned char *rx_data,  unsigned short rx_num);
    void Send_SerialMessage();
    void Close_SearchDialog(const QString &portname);
    void Slot_TestRunTimer();

    void Slot_StartStopTest_FromConsoleWin(const bool &state, const QString &dmport, const QString &dpport);

    void Application_Exit();


};


#endif // MAINWINDOW_H
