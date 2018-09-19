#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QSplitter>
#include "leftwindow.h"
#include "rightwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QToolBar     *tool_bar;
    LeftWindow   *left_window;
    RightWindow  *right_window;
    QSplitter    *splitter;

};

#endif // MAINWINDOW_H
