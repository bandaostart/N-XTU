#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "leftwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    QSplitter    *splitter;
    LeftWindow   *left_window;
    LeftWindow   *right_window;

};

#endif // MAINWINDOW_H
