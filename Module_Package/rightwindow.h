#ifndef RIGHTWINDOW_H
#define RIGHTWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QLabel>




class RightWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RightWindow(QWidget *parent = 0);
    ~RightWindow();

private:
    QToolBar *Tool_Bar;

};

#endif // RIGHTWINDOW_H
