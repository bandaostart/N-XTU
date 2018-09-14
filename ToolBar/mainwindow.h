#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolbar.h"
#include <QDockWidget>
#include <QTextEdit>
#include <QListWidget>
#include <QHBoxLayout>
#include <QSplitter>
#include <QHBoxLayout>
#include <QPainter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void paintEvent(QPaintEvent *event) override;

private:
    ToolBar     *Tool_Bar;
    QWidget     *centralWidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QSplitter   *splitter;
    QWidget     *widget;
    QListView   *listView;
    QListView   *listView2;
};

#endif // MAINWINDOW_H
