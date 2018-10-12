#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QLabel>
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
    void Slot_CommunicationDisplay_FromMainWin(const QString &str);
    void Slot_RecordMenuText_FromRecordText(QPoint);

public:
    void Set_StatusText(int count, int state);
    void Set_NamePix(int count, int state);
    void Set_RecordLabel(int count);
    void Set_NamePixFlicker(int count, int state);

private:
    void Creat_TopToolBar();
    void Creat_LeftToolBar();
    void Creat_MasterDisAre();
    void Creat_SlaveDisAre();
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

    QToolBar    *Left_Tool_Bar;
    QWidget     *Space[4];

    QAction     *Master_Action;
    QAction     *Slave_Action;
    QAction     *Connect_Action;

    QGroupBox   *Top_Group_Box;
    QPixmap     NamePix_Pixmap[3];
    QString     StatusText_Str[4];
    QLabel      *NameLabel[NumTestRow];
    QLineEdit   *NameText[NumTestRow];
    QLabel      *NamePix[NumTestRow];
    QLabel      *StatusText[NumTestRow];
    QGridLayout *Top_Box_Layout;

    QGroupBox   *Bottom_Group_Box;

    QGroupBox   *Right_Group_Box;
    QPixmap      Pixmap[11];
    QLabel      *Record_Label;
    QMenu       *Record_Menu;
    QAction     *Record_Clear;
    QAction     *Record_SelectAll;
    QTextEdit   *Record_Text;
    QVBoxLayout *Right_Box_Layout;

    QGridLayout *Grid_Layout;

    QString      DM_Port;
    QString      DP_Port;
    bool         Testing_State;
    bool         DM_State;
    bool         DP_State;

};

#endif // CONSOLEWINDOW_H
