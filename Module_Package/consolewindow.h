#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
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
    QTextEdit   *Record_Text;
    QVBoxLayout *Right_Box_Layout;

    QGridLayout *Grid_Layout;
};

#endif // CONSOLEWINDOW_H
