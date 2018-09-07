#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    creatActions();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::creatActions()
{
    const QIcon searchIcon = QIcon::fromTheme("document-Add Radio Module", QIcon(":/image/add_toolbar.png"));        //左边是图片右边是文字
    QAction *newAct        = new QAction(searchIcon, tr("&Add Radio Module"), this);
    newAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_A));


    //menuBar
    QMenu *fileMenu        = ui->menuBar->addMenu("&NXTU");
    fileMenu->addAction(newAct);

    //toolBar
    ui->mainToolBar->addAction(newAct);
    ui->mainToolBar->setMinimumHeight(64);


    //
    newAct->setStatusTip(tr("Add Radio Module"));
}





