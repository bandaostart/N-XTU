#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    //创建菜单栏
    Creat_MenuBar();

    //创建工具栏
    Creat_ToolBar();


    //mainwindow
    this->setMinimumSize(800, 600);
}

MainWindow::~MainWindow()
{

}





/*创建菜单栏-----------------------------------------------------------------------------------------------------*/
void MainWindow::Creat_MenuBar()
{
    QAction *Add_Action     = new QAction(QIcon(":/image/add_module.png"), tr("Add Radio Module"), this);
    QAction *Search_Action  = new QAction(QIcon(":/image/discover_modules.png"), tr("Discover Radio Modules"), this);

    Add_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_A));
    Search_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_D));

    Menu_Bar        = new QMenuBar(this);
    QMenu *NxtuMenu = Menu_Bar->addMenu("&N-XTU");
    NxtuMenu->addAction(Add_Action);
    NxtuMenu->addAction(Search_Action);

    connect(Add_Action, &QAction::triggered, this, &MainWindow::AddSerialPort);
    this->setMenuBar(Menu_Bar);
}


/*创建工具栏----------------------------------------------------------------------------------------------------*/
void MainWindow::Creat_ToolBar()
{
    QAction *Add_Action     = new QAction(QIcon(":/image/add.png"), tr("Add Radio Module"), this);
    QAction *Search_Action  = new QAction(QIcon(":/image/search.png"), tr("Discover Radio Modules"), this);

    Tool_Bar = new QToolBar(this);
    Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");
    Tool_Bar->setMovable(false);
    Tool_Bar->setIconSize(QSize(48,48));
    Tool_Bar->addAction(Add_Action);
    Tool_Bar->addAction(Search_Action);

    connect(Add_Action, &QAction::triggered, this, &MainWindow::AddSerialPort);
    this->addToolBar(Tool_Bar);
}



