#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    ui->setupUi(this);

    left_widget  = new QWidget();
    right_widget = new QWidget();
    left_widget->setMinimumWidth(100);
    right_widget->setMinimumWidth(100);


    /*splitter相当于一个widget-------------------------------------------*/
    Splitter = new QSplitter(Qt::Horizontal, this);
    Splitter->addWidget(left_widget);
    Splitter->addWidget(right_widget);
    Splitter->setChildrenCollapsible(false);                                        //设置是否最小宽度高度限定
    Splitter->setStretchFactor(1, 1);                                               //设置拉伸:第一参数是 序号  ；第二个参数 大于1支持拉伸
    Splitter->setHandleWidth(4);                                                    //设置宽度
    Splitter->setStyleSheet("QSplitter::handle { background-color: blue }");        //设置颜色
    Splitter->showMaximized();

    this->setCentralWidget(Splitter);


    this->setMinimumSize(954, 601);
}

MainWindow::~MainWindow()
{
    delete ui;
}
