#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSplitter>
#include <QListView>
#include <QWidget>
#include <QDockWidget>
#include <QPushButton>
#include <QTreeView>
#include <QTextEdit>
#include <QToolBar>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:

    QWidget *left_widget;
    QWidget *right_widget;

    QSplitter *Splitter;



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
