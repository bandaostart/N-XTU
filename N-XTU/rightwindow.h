#ifndef RIGHTWINDOW_H
#define RIGHTWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QLabel>
#include <QSplitter>
#include "consolewindow.h"
#include "updatawindow.h"




class RightWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RightWindow(QWidget *parent = 0);
    ~RightWindow();
    void     Window_Choose(unsigned char num);

public:
    QToolBar      *Tool_Bar;
    QLabel        *Device_Pixmap;
    QLabel        *Device_Text;

    QSplitter     *splitter;
    ConsoleWindow *Console_Window;
    UpdataWindow  *Updata_Window;

};

#endif // RIGHTWINDOW_H
