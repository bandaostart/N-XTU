#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
    QPalette    color_pal;
    QColor      color;

private slots:
    void on_colorButton_clicked();
    void on_pushButton_clicked();

    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
