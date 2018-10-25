#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QLCDNumber>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenu>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>


class ConsoleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleWindow(QWidget *parent = 0);
    ~ConsoleWindow();

private:
    void paintEvent(QPaintEvent *event) override;

signals:
    void Signal_StartStopTest_ToMainWin(const bool &state, const QString &dmport, const QString &dpport);

public slots:
    void Slot_ModuleStateChange_FromMainWin(bool add_delete, QString portname, QString noidtype);

    void Slot_StartStopTest_FromStartAction();
    void Slot_RefreshText_FromRefreshAction();
    void Slot_CommunicationDisplay_FromMainWin(const QString &portname, const QString &str);
    void Slot_RecordMenuText_FromRecordText(QPoint);

public:
    void Set_StatusText(int count, int state);
    void Set_NamePix(int count, int state);
    void Set_RecordLabel(int count);
    void Set_NamePixFlicker(int count, int state);
    void Set_AmmeterData(QString &str);

    void Set_ExcelNodeIdShow(const QString &status, const QString &node_id, const QString &time);

private:
    void Creat_TopToolBar();
    void Creat_LeftToolBar();
    void Creat_MasterDisAre();
    void Creat_SlaveDisAre();
    void Creat_AmmeterAra();
    void Creat_RecordDisAre();
    void Creat_Layout();
    void Init_Para();





public:
    enum {NumTestRow = 8};

    QFont font;

    QToolBar    *Top_Tool_Bar;
    QAction     *Start_Action;
    QAction     *Record_Action;
    QAction     *Refresh_Action;
    QAction     *UpdataFw_Action;
    QWidget     *Top_Space;

    QToolBar    *Left_Tool_Bar;
    QWidget     *Space[4];

    QAction     *Master_Action;
    QAction     *Slave_Action;
    QAction     *Connect_Action;
//    QAction     *Connect_Action_1;
//    QAction     *Ammeter_Action;

    QGroupBox   *Top_Group_Box;
    QPixmap     NamePix_Pixmap[3];
    QString     StatusText_Str[4];
    QLabel      *NameLabel[NumTestRow];
    QLineEdit   *NameText[NumTestRow];
    QLabel      *NamePix[NumTestRow];
    QLabel      *StatusText[NumTestRow];
    QGridLayout *Top_Box_Layout;

    QTextEdit   *NodeId_Text;
    QGroupBox   *Bottom_Group_Box;
    QVBoxLayout *Bottom_Box_Layout;
//    QGroupBox   *Ammeter_Group_Box;

    QGroupBox   *Right_Group_Box;
    QPixmap      Record_Pixmap[11];
    QPixmap      Updata_Pixmap[7];
    QLabel      *Record_Label;
    QLabel      *Updata_Label;
    QLCDNumber  *Ammeter_LCD;
    QLabel      *Ammeter_Label;
    QMenu       *Record_Menu;
    QAction     *Record_Clear;
    QAction     *Record_SelectAll;
    QTextEdit   *Record_Text;
    QVBoxLayout *Right_Box_Layout;


    QGridLayout *Grid_Layout;


    QString      DM_Port;
    QString      DP_Port;
    QString      DA_Port;
    bool         Testing_State;
    bool         DM_State;
    bool         DP_State;
    bool         DA_State;

};

#endif // CONSOLEWINDOW_H
