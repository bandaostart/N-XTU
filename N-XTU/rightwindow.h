#ifndef RIGHTWINDOW_H
#define RIGHTWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QLabel>
#include "consolewindow.h"




class RightWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RightWindow(QWidget *parent = 0);
    ~RightWindow();

public:
    QToolBar      *Tool_Bar;
    ConsoleWindow *Console_Window;

};

#endif // RIGHTWINDOW_H
