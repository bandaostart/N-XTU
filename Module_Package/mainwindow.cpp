#include "mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   tool_bar =  new QToolBar(this);
   addToolBar(tool_bar);

   left_window  = new LeftWindow();
   right_window = new RightWindow();
   left_window->resize(350, 100);
   left_window->setMinimumWidth(250);
   right_window->setMinimumWidth(250);


   splitter = new QSplitter(Qt::Horizontal, this);
   splitter->addWidget(left_window);
   splitter->addWidget(right_window);
   splitter->setChildrenCollapsible(false);                                        //设置是否最小宽度高度限定
   splitter->setStretchFactor(1, 1);                                               //设置拉伸:第一参数是 序号  ；第二个参数 大于1支持拉伸
   splitter->setHandleWidth(4);                                                    //设置宽度
   splitter->setStyleSheet("QSplitter::handle { background-color: blue }");        //设置颜色
   splitter->showMaximized();

   this->setCentralWidget(splitter);

   this->setMinimumSize(800, 660);
   this->resize(1300, 600);
}

MainWindow::~MainWindow()
{

}
