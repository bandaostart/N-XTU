#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidgetAction>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Serial_Dialog = new SerialDialog();

    creatActions();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::creatActions()
{
    const QIcon FaddIcon = QIcon::fromTheme("document-Add Radio Module", QIcon(":/image/add_module.png"));                 //左边是图片右边是文字
    const QIcon TaddIcon = QIcon::fromTheme("document-Add Radio Module", QIcon(":/image/add.png"));                        //左边是图片右边是文字

    const QIcon FsearchIcon = QIcon::fromTheme("document-Discover Radio Modules", QIcon(":/image/discover_modules.png"));  //左边是图片右边是文字
    const QIcon TsearchIcon = QIcon::fromTheme("document-Discover Radio Modules", QIcon(":/image/search.png"));            //左边是图片右边是文字



    QAction *FaddAct        = new QAction(FaddIcon, tr("&Add Radio Module"), this);
    FaddAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_A));
    QAction *FsearchAct     = new QAction(FsearchIcon, tr("&Discover Radio Modules"), this);
    FsearchAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_D));


    QAction *TaddAct        = new QAction(TaddIcon, tr("&Add Radio Module"), this);
    TaddAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_A));
    QAction *TsearchAct     = new QAction(TsearchIcon, tr("&Discover Radio Modules"), this);
    TsearchAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_D));




    //menuBar
    QMenu *NxtuMenu        = ui->menuBar->addMenu("&NXTU");
    NxtuMenu->addAction(FaddAct);
    NxtuMenu->addAction(FsearchAct);


    //toolBar
    ui->mainToolBar->setMovable(false);
    ui->mainToolBar->setIconSize(QSize(48,48));
    ui->mainToolBar->addAction(TaddAct);
    ui->mainToolBar->addAction(TsearchAct);




    //satustip
    FaddAct->setStatusTip(tr("Add Radio Module"));
    TaddAct->setStatusTip(tr("Add Radio Module"));
    FsearchAct->setStatusTip(tr("Discover Radio Modules"));
    TsearchAct->setStatusTip(tr("Discover Radio Modules"));

    connect(FaddAct, &QAction::triggered, this, &MainWindow::AddSerialPort);
    connect(TaddAct, &QAction::triggered, this, &MainWindow::AddSerialPort);



    //mainwindow
    this->setMinimumSize(800, 600);
}



void MainWindow::AddSerialPort()
{
    Serial_Dialog->exec();
}








