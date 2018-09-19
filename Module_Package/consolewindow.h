#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
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
    QToolBar    *Tool_Bar;
    QAction     *Start_Action;
    QAction     *Record_Action;
    QLabel      *Connect_Label;

    QGroupBox   *Top_Group_Box;
    QGroupBox   *Bottom_Group_Box;
    QGroupBox   *Left_Group_Box;

    QGridLayout *Grid_Layout;



};

#endif // CONSOLEWINDOW_H
