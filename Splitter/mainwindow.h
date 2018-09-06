#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QListView>
#include <QTextEdit>
#include <QTreeView>

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
    QSplitter *Splitter;
    QSplitter *RightSplitter;
    QListView *Listview;
    QTextEdit *Textedit;
    QTreeView *Treeview;
};

#endif // MAINWINDOW_H
