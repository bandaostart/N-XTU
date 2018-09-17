#ifndef LEFTWINDOW_H
#define LEFTWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QAction>

class LeftWindow : public QMainWindow
{
    Q_OBJECT

public:
    LeftWindow(QWidget *parent = 0);

    ~LeftWindow();

private:
    QMenu    *Tool_Menu;
    QToolBar *Tool_Bar;

};



#endif // LEFTWINDOW_H
