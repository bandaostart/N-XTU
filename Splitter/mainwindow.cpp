#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Listview = new QListView();
    Treeview = new QTreeView();
    Textedit = new QTextEdit();

    QStringList num;
    num<<QString("ListView");
    QStringListModel *model = new QStringListModel(num);
    Listview->setModel(model);


    num.clear();
    num<<QString("TreeView");
    QStringListModel *model1 = new QStringListModel(num);
    Treeview->setModel(model1);

    Textedit->setText("TextEdit");

    /*splitter相当于一个widget-------------------------------------------*/
    Splitter = new QSplitter(Qt::Horizontal);
    Splitter->addWidget(Treeview);



    RightSplitter = new QSplitter(Qt::Vertical, Splitter);
    RightSplitter->addWidget(Listview);
    RightSplitter->addWidget(Textedit);


    Splitter->setChildrenCollapsible(false);                                        //设置是否最小宽度高度限定
    RightSplitter->setChildrenCollapsible(false);
    //Splitter->setMinimumHeight(200);                                              //不起作用


    Splitter->setStretchFactor(1, 1);                                               //设置拉伸:第一参数是 序号  ；第二个参数 大于1支持拉伸
    Splitter->setHandleWidth(2);                                                    //设置宽度
    Splitter->setStyleSheet("QSplitter::handle { background-color: blue }");        //设置颜色


    ui->mdiArea->addSubWindow(Splitter,Qt::FramelessWindowHint);
    Splitter->showMaximized();


    this->setMinimumSize(954, 601);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionDialog_triggered()
{
    Dialog dialog;

    dialog.exec();
}
