#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::MainWindow *ui;

    QAxObject    *Excel;
    QAxObject    *WorkBooks;
    QAxObject    *WorkBook;
    QAxObject    *WorkSheets;
    QAxObject    *WorkSheet;
    QAxObject    *WorkRow;
    QAxObject    *WorkColumn;

    unsigned int StartRow;
    unsigned int StartColumn;
    unsigned int AllRowsNum;
    unsigned int AllColumnsNum;
};

#endif // MAINWINDOW_H
