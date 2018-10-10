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


class ConsoleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleWindow(QWidget *parent = 0);
    ~ConsoleWindow();

private:
    void paintEvent(QPaintEvent *event) override;

signals:
    void Signal_Testing_State(const bool &state);

public slots:
    void Start_RfTesting();
    void Communication_Display(const QString &str);
    void Record_MenuText(QPoint);

private:
    void Creat_TopToolBar();
    void Creat_LeftToolBar();
    void Creat_MasterDisAre();
    void Creat_SlaveDisAre();
    void Creat_RecordDisAre();
    void Creat_Layout();
    void Init_Para();



private:
    enum {NumTestRow = 8};

    QToolBar    *Top_Tool_Bar;
    QAction     *Start_Action;
    QAction     *Record_Action;

    QToolBar    *Left_Tool_Bar;
    QWidget     *Space[4];

    QAction     *Master_Action;
    QAction     *Slave_Action;
    QAction     *Connect_Action;

    QGroupBox   *Top_Group_Box;
    QLabel      *NameLabel[NumTestRow];
    QLineEdit   *NameText[NumTestRow];
    QLabel      *NamePix[NumTestRow];
    QLabel      *StatusText;
    QLabel      *StatusPix;
    QGridLayout *Top_Box_Layout;

    QGroupBox   *Bottom_Group_Box;

    QGroupBox   *Right_Group_Box;
    QLabel      *Record_Label;
    QMenu       *Record_Menu;
    QAction     *Record_Clear;
    QAction     *Record_SelectAll;
    QTextEdit   *Record_Text;
    QVBoxLayout *Right_Box_Layout;

    QGridLayout *Grid_Layout;

    bool         Testing_State;

};

#endif // CONSOLEWINDOW_H
