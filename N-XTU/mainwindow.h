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
#include <QAxObject>
#include <QDir>
#include <QFileInfo>
#include <QDate>
#include <QDateTime>
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

    enum {NullState = 0,  ReadNodeID, RfTransmit, RfReceive, CurrentTransmit, CurrentReceive, CurrentSleep, GPIO, CrystalOsc, StateInit};
    unsigned char  Test_Run_State;
    unsigned int   Test_Run_Num;

    QString         DMPA_PortName;
    QString         DM_PortName;
    QString         DP_PortName;
    Rf_Rx_Tx_Para   DMP_RtxPara;
    Excel_Save_Para Excel_SavePara;


    QAxObject    *Excel;
    QAxObject    *WorkBooks;
    QAxObject    *WorkBook;
    QAxObject    *WorkSheets;
    QAxObject    *WorkSheet;
    QAxObject    *WorkRow;
    QAxObject    *WorkColumn;
    unsigned int StartRow;
    unsigned int StartColumn;
    unsigned int AllRowsNum;
    unsigned int AllColumnsNum;


private:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void Creat_MenuBar();
    void Creat_ToolBar();
    void Creat_CentralWidget();
    void Creat_User_Timer();
    void Set_WidgetAttributes();
    void Init_Excel();
    void Init_Window_Para();
    void Open_Serial_Deal();

    bool Port_Send_Deal(ModuleDeal *module_deal);
    void Port_Receive_Deal(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);

    void Hash_Set_Deal(QString portname, uint8_t type_fun, uint8_t type_para);

    void Excel_Node_Save(Excel_Save_Para &excel_save_para);


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
