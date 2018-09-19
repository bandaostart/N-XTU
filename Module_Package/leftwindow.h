#ifndef LEFTWINDOW_H
#define LEFTWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "modulewindow.h"

class LeftWindow : public QMainWindow
{
    Q_OBJECT

public:
    LeftWindow(QWidget *parent = 0);

    ~LeftWindow();

private:
    QToolBar    *Tool_Bar;
    QAction     *Find_Action;
    QMenu       *Tool_Menu;
    QAction     *Clear_Action;
    QVBoxLayout *Vbox_Layout;

    ModuleWindow *Moduel_Widget;
    QWidget      *Central_Widget;
    QSpacerItem  *verticalSpacer;
};



#endif // LEFTWINDOW_H
