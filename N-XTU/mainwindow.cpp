#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建菜单栏
    Creat_MenuBar();

    //创建工具栏
    Creat_ToolBar();

    //创建中心窗体
    Creat_CentralWidget();

    //mainwindow
    this->setMinimumSize(800, 600);
}

MainWindow::~MainWindow()
{
    delete Serial_Dialog;
}





/*创建菜单栏-----------------------------------------------------------------------------------------------------*/
void MainWindow::Creat_MenuBar()
{
    QAction *Add_Action         = new QAction(QIcon(":/image/add_module.png"), tr("Add Radio Module"), this);
    QAction *Search_Action      = new QAction(QIcon(":/image/discover_modules.png"), tr("Discover Radio Modules"), this);
    QAction *Preferences_Action = new QAction(QIcon(":/image/preferences.png"), tr("Preferences"), this);
    QAction *Exit_Action        = new QAction(QIcon(":/image/exit.png"), tr("Exit"), this);

    Add_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_A));
    Search_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_D));
    Preferences_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_P));
    Exit_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_Q));

    Menu_Bar        = new QMenuBar(this);

    QMenu *NxtuMenu  = Menu_Bar->addMenu("&N-XTU");
    NxtuMenu->addAction(Add_Action);
    NxtuMenu->addAction(Search_Action);
    NxtuMenu->addAction(Preferences_Action);
    NxtuMenu->addAction(Exit_Action);

    connect(Add_Action,  &QAction::triggered, this, &MainWindow::Open_SerialDialog);
    connect(Exit_Action, &QAction::triggered, this, &MainWindow::Application_Exit);

    this->setMenuBar(Menu_Bar);

    setAttribute(Qt::WA_AlwaysShowToolTips) ;
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

    connect(Add_Action, &QAction::triggered, this, &MainWindow::Open_SerialDialog);
    this->addToolBar(Tool_Bar);
}



/*创建主窗体---------------------------------------------------------------------------------------------------*/
void MainWindow::Creat_CentralWidget()
{
    //定义串口对话框
    Serial_Dialog = new SerialDialog();

    //定义左窗体
    left_window  = new LeftWindow();
    left_window->resize(350, 100);
    left_window->setMinimumWidth(250);

    //定义右窗体
    right_window = new RightWindow();
    right_window->setMinimumWidth(250);

    //定义分割器
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(left_window);
    splitter->addWidget(right_window);
    splitter->setChildrenCollapsible(false);                                           //设置是否最小宽度高度限定
    splitter->setStretchFactor(1, 1);                                                  //设置拉伸:第一参数是 序号  ；第二个参数 大于1支持拉伸
    splitter->setHandleWidth(4);                                                       //设置宽度
    splitter->setStyleSheet("QSplitter::handle { background-color:rgb(215,215,215)}"); //设置颜色
    splitter->showMaximized();

    //设置布局
    this->setCentralWidget(splitter);
    this->setMinimumSize(800, 660);
    this->resize(1300, 600);
}







/*打开串口对话框 槽函数------------------------------------------------------------------------------------------*/
void MainWindow::Open_SerialDialog()
{
    Serial_Dialog->SerivalDiscover();
    if (Serial_Dialog->exec() == QDialog::Accepted)
    {
        if(!Module_Deal_Hash.contains(Serial_Dialog->Serial_Port_Settings.portName))
        {
            ModuleDeal *Module_Deal;

            Module_Deal = new ModuleDeal;

            QVector<QString> text;
            text.push_back("DP");
            text.push_back("Master");
            text.push_back("Zigbee Master API");
            text.push_back(Serial_Dialog->Serial_Port_Settings.portName);
            text.push_back(" ");
            Module_Deal->moduleWindow = new ModuleWindow(text, this);
            connect(Module_Deal->moduleWindow, &ModuleWindow::Signal_ModuleWinClose, this, Delete_SerialPort);


            Module_Deal->serialThread = new SerialThread(this);

            Module_Deal_Hash.insert(Serial_Dialog->Serial_Port_Settings.portName, Module_Deal);
        }


        if (!Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->serialThread->SerialOpen(Serial_Dialog->Serial_Port_Settings))
        {
            Module_Deal_Hash.remove(Serial_Dialog->Serial_Port_Settings.portName);
            QMessageBox::critical(NULL, "Error discovering device",
                                  "COM > serOpenPort failed:Port not valid                           ", QMessageBox::Ok);
        }
        else
        {
            left_window->Add_SubWidget(Module_Deal_Hash);
        }
    }
}


/*删除串口--------------------------------------------------------------------------------------------------*/
void MainWindow::Delete_SerialPort(const QString &portname)
{
    Module_Deal_Hash.value(portname)->serialThread->SerialClose();
    Module_Deal_Hash.remove(portname);
}





/*关闭对话框 槽函数--------------------------------------------------------------------------------------------*/
void MainWindow::Application_Exit()
{
    close();
}




/*绘图事件重写-------------------------------------------------------------------------------------------------*/
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QBrush   brush;
    QPen     pen;
    QPainter painter(this);

    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(215,215,215));

    brush.setColor(QColor(215,215,215));
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(Tool_Bar->x(), Tool_Bar->y(), Tool_Bar->width(), Tool_Bar->height());
}


