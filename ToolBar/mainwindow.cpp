#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setFixedSize(680,552);

    Tool_Bar    = new ToolBar();
    Tool_Bar->setStyleSheet("QToolBar{border-width:0;border-style:outset}");
    addToolBar(Tool_Bar);


    listView = new QListView(this);
    listView->setObjectName(QStringLiteral("listView"));
    listView->move(0,48);

    listView2 = new QListView(this);
    listView2->setObjectName(QStringLiteral("listView"));
    listView2->move(0,100);


    centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("QWidget{border-width:0;border-style:outset}");


    splitter = new QSplitter(Qt::Horizontal, centralWidget);
    splitter->addWidget(listView);
    splitter->addWidget(listView2);

    splitter->setChildrenCollapsible(false);                                        //设置是否最小宽度高度限定
    //Splitter->setMinimumHeight(200);                                              //不起作用

    splitter->setStretchFactor(1, 1);                                                //设置拉伸:第一参数是 序号  ；第二个参数 大于1支持拉伸
    splitter->setHandleWidth(4);                                                     //设置宽度
    splitter->setStyleSheet("QSplitter::handle { background-color:rgb(0,144,216) }");//设置颜色


    horizontalLayout = new QHBoxLayout(centralWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->addWidget(splitter);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}


void MainWindow::paintEvent(QPaintEvent *event	)
{
        Q_UNUSED(event);

        QBrush   brush;
        QPen     pen;
        QPainter painter(this);

        pen.setStyle(Qt::SolidLine);
        pen.setColor(QColor(0,144,216));

        brush.setColor(QColor(0,144,216));
        brush.setStyle(Qt::SolidPattern);

        painter.setPen(pen);
        painter.setBrush(brush);

        painter.drawRect(120, Tool_Bar->height(), this->width(),centralWidget->pos().y()-Tool_Bar->height());
}
