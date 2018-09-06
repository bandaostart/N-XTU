#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>

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


    Splitter = new QSplitter(Qt::Horizontal);
    Splitter->addWidget(Treeview);
    Splitter->setStretchFactor(1,4);


    RightSplitter = new QSplitter(Qt::Vertical, Splitter);
    RightSplitter->addWidget(Listview);
    RightSplitter->addWidget(Textedit);
    RightSplitter->setStretchFactor(4, 1);


    ui->mdiArea->addSubWindow(Splitter, Qt::WindowFullScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}
