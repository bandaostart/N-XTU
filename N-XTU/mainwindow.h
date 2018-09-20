#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QToolBar   *Tool_Bar;
    QMenuBar   *Menu_Bar;

private:
    void Creat_MenuBar();
    void Creat_ToolBar();

};

#endif // MAINWINDOW_H
