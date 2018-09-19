#ifndef MODULEWINDOW_H
#define MODULEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QToolBar>
#include <QAction>
#include <QHBoxLayout>
#include <QPainter>
#include <QCursor>
#include <QMouseEvent>
#include <QGroupBox>



class ModuleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleWindow(QWidget *parent = 0);
    ~ModuleWindow();

private:
    QLabel       *Label;
    QToolBar     *ToolBar;
    QHBoxLayout  *HboxLayout;

    QGroupBox    *GroupBox;
    QLabel       *Name;
    QLabel       *Name_Text;
    QLabel       *Function;
    QLabel       *Function_Text;
    QLabel       *Port;
    QLabel       *Port_Text;
    QLabel       *Mac;
    QLabel       *Mac_Text;

    int  PaintFlag;
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MODULEWINDOW_H
