#include "mainwindow.h"

extern bool     AT_Com_ReqType(ModuleDeal *module_deal, uint8_t *tx_buf, uint16_t &tx_num);
extern void     AT_Com_RspType(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建菜单栏
    Creat_MenuBar();


    //创建工具栏
    Creat_ToolBar();


    //创建中心窗体
    Creat_CentralWidget();


    //创建串口发送定时器
    Creat_SerialTxTimer();


    //设置窗体属性
    Set_WidgetAttributes();
}

MainWindow::~MainWindow()
{
    delete Serial_Dialog;
}




/*创建菜单栏-----------------------------------------------------------------------------------------------------*/
void MainWindow::Creat_MenuBar()
{
    //创建action
    QAction *Add_Action         = new QAction(QIcon(":/image/add_module.png"), tr("Add Radio Module"), this);
    QAction *Search_Action      = new QAction(QIcon(":/image/discover_modules.png"), tr("Discover Radio Modules"), this);
    QAction *Preferences_Action = new QAction(QIcon(":/image/preferences.png"), tr("Preferences"), this);
    QAction *Exit_Action        = new QAction(QIcon(":/image/exit.png"), tr("Exit"), this);

    //设置action快捷键
    Add_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_A));
    Search_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_D));
    Preferences_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_P));
    Exit_Action->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_Q));

    //创建菜单栏
    Menu_Bar        = new QMenuBar(this);
    QMenu *NxtuMenu  = Menu_Bar->addMenu("&N-CTU");
    NxtuMenu->addAction(Add_Action);
    NxtuMenu->addAction(Search_Action);
    NxtuMenu->addAction(Preferences_Action);
    NxtuMenu->addAction(Exit_Action);

    //管理消息和槽函数
    connect(Add_Action,  &QAction::triggered, this, &MainWindow::Open_SerialDialog);
    connect(Exit_Action, &QAction::triggered, this, &MainWindow::Application_Exit);


    //添加菜单
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
    //创建搜索对话框
    //search_dialog  = new SearchDialog(this);


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



/*创建串口发送定时器------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Creat_SerialTxTimer()
{
    SerialTx_Timer = new QTimer(this);

    connect(SerialTx_Timer, SIGNAL(timeout()), this, SLOT(Send_SerialPort()));
    SerialTx_Timer->start(1);
}



/*设置窗体属性----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Set_WidgetAttributes()
{
    this->setWindowTitle("N-CTU");
    this->setMinimumSize(800, 600);
}




/*串口模块添处理--------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Add_Module_Deal()
{
    //判断hash表中是否已经存该串口
    if(!Module_Deal_Hash.contains(Serial_Dialog->Serial_Port_Settings.portName))
    {
        ModuleDeal *Module_Deal;
        Module_Deal = new ModuleDeal;


        //模块窗体创建
        QVector<QString> text;
        text.push_back("");
        text.push_back("");
        text.push_back("");
        text.push_back(Serial_Dialog->Serial_Port_Settings.portName);
        text.push_back(" ");
        Module_Deal->moduleWindow = new ModuleWindow(text, this);

        Module_Deal->moduleWindow->Text_Content[0] = "";
        Module_Deal->moduleWindow->Text_Content[1] = "";
        Module_Deal->moduleWindow->Text_Content[2] = "";
        Module_Deal->moduleWindow->Text_Content[3] = Serial_Dialog->Serial_Port_Settings.portName;
        Module_Deal->moduleWindow->Text_Content[4] = "";

        connect(Module_Deal->moduleWindow, &ModuleWindow::Signal_ModuleWinClose, this, Delete_SerialPort);


        //模块串口线程创建
        Module_Deal->serialThread = new SerialThread(this);
        connect(Module_Deal->serialThread, &SerialThread::SerialRxData, this, Receive_SerialPort);


        //模块串口发送接收相关参数创建
        Module_Deal->serialtxrxPara = new SerialTxRxPara;
        Module_Deal->serialtxrxPara->func_type           = MODULE_REQ_NULL;
        Module_Deal->serialtxrxPara->frame_id            = 0x00;
        Module_Deal->serialtxrxPara->func_type           = 0x00;
        Module_Deal->serialtxrxPara->tx_interval         = 0x00;
        Module_Deal->serialtxrxPara->search_count        = 0x01;
        Module_Deal->serialtxrxPara->search_total_count  = 0x01;


        //插入到hash中
        Module_Deal_Hash.insert(Serial_Dialog->Serial_Port_Settings.portName, Module_Deal);
    }


    //打开串口
    if (!Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->serialThread->SerialOpen(Serial_Dialog->Serial_Port_Settings))
    {
        //打开串口失败，从Qhash中删除
        delete Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->moduleWindow;
        delete Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->serialThread;
        delete Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->serialtxrxPara;
        Module_Deal_Hash.remove(Serial_Dialog->Serial_Port_Settings.portName);

        QMessageBox::critical(NULL, "Error discovering device",
                             Serial_Dialog->Serial_Port_Settings.portName +" > Port Open Failed: Port not valid                           ", QMessageBox::Ok);
    }
    else
    {
        //请求模块相关信息
        auto temp_serialtxrxPara = Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->serialtxrxPara;
        temp_serialtxrxPara->func_type          = MODULE_TYPE_REQ_FUN;
        temp_serialtxrxPara->frame_id           = 0x01;
        temp_serialtxrxPara->tx_num             = MODULE_TYPE_REQ_NUM;
        temp_serialtxrxPara->tx_interval        = MODULE_TYPE_REQ_INTERVAL;
        temp_serialtxrxPara->tx_count           = 0x00;
        temp_serialtxrxPara->search_count       = 0x01;
        temp_serialtxrxPara->search_total_count = MODULE_TYPE_REQ_NUM;

        //显示搜索对话框
        search_dialog.show();
    }
}



/*串口接收处理--------------------------------------------------------------------------------------------------------------*/
void MainWindow::Port_Receive_Deal(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    auto para = module_deal->serialtxrxPara;

    switch (para->func_type)
    {
        case MODULE_TYPE_REQ_FUN:
            AT_Com_RspType(module_deal, rx_buf, rx_num);
        break;

        default:
        break;
    }
}



/*串口发送处理-------------------------------------------------------------------------------------------------------------*/
bool MainWindow::Port_Send_Deal(ModuleDeal *module_deal)
{
    uint8_t  tx_buf[512] = {0}, func_type = 0xFF;
    uint16_t tx_num = 0;

    func_type = module_deal->serialtxrxPara->func_type;
    if (func_type != MODULE_REQ_NULL)
    {
        switch (func_type)
        {
            //模块类型获取
            case MODULE_TYPE_REQ_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        //关闭搜索显示对话框
                        emit search_dialog.Signal_DialogClose();

                        //左侧窗口添加模块对话框
                        module_deal->serialtxrxPara->func_type          = MODULE_REQ_NULL;
                        module_deal->serialtxrxPara->tx_num             = 0x00;
                        module_deal->serialtxrxPara->tx_interval        = 0x00;
                        module_deal->serialtxrxPara->tx_count           = 0x00;
                        module_deal->serialtxrxPara->search_count       = 0x01;
                        module_deal->serialtxrxPara->search_total_count = 0x01;

                        //设置module模块参数
                        module_deal->moduleWindow->ModuleInfo_Set();

                        //添加module window模块
                        left_window->Add_SubWidget(Module_Deal_Hash);
                    }
                    else
                    {
                        //设置搜索对话框进度条变动
                        search_dialog.Set_SearchDisplay(module_deal->serialtxrxPara->search_count, module_deal->serialtxrxPara->search_total_count);

                        //发送请求命令
                        AT_Com_ReqType(module_deal, tx_buf, tx_num);
                        module_deal->serialThread->SerialTxData(tx_buf, tx_num);
                    }
                }
                else
                {
                    if (module_deal->serialtxrxPara->tx_count > module_deal->serialtxrxPara->tx_interval)
                    {
                        //等待应答超时，关闭串口从Qhash中删除
                        module_deal->serialThread->SerialClose();
                        delete module_deal->moduleWindow;
                        delete module_deal->serialThread;
                        delete module_deal->serialtxrxPara;
                        Module_Deal_Hash.remove(Serial_Dialog->Serial_Port_Settings.portName);

                        //发送搜索对话框关闭消息
                        emit search_dialog.Signal_DialogClose();

                        //告警提示
                        QMessageBox::critical(NULL, "Error discovering device",
                                              module_deal->moduleWindow->Text_Content[3]+" > Read Module Failed: Module not valid                           ", QMessageBox::Ok);
                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }



            default:
                break;
        }
    }

    return true;
}








/*打开串口对话框选中串口后并进行相应的处理 槽函数------------------------------------------------------------------------------------------*/
void MainWindow::Open_SerialDialog()
{
    Serial_Dialog->SerivalDiscover();
    if (Serial_Dialog->exec() == QDialog::Accepted)
    {
        Add_Module_Deal();
    }
}




/*删除模块对话框后进行相应处理 槽函数-----------------------------------------------------------------------------*/
void MainWindow::Delete_SerialPort(const QString &portname)
{
    Module_Deal_Hash.value(portname)->serialThread->SerialClose();

    delete Module_Deal_Hash.value(portname)->serialThread;
    delete Module_Deal_Hash.value(portname)->serialtxrxPara;

    Module_Deal_Hash.remove(portname);
}



/*串口数据接收相应处理 槽函数-----------------------------------------------------------------------------------*/
void MainWindow::Receive_SerialPort(const QString &portname, unsigned char *rx_data, unsigned short rx_num)
{
    auto module_deal = Module_Deal_Hash.value(portname);
    Port_Receive_Deal(module_deal, rx_data, rx_num);
}



/*串口发送数据相应处理 槽函数-----------------------------------------------------------------------------------*/
void MainWindow::Send_SerialPort()
{
    auto module = Module_Deal_Hash.begin();
    while(module != Module_Deal_Hash.end())
    {
        if (!Port_Send_Deal(module.value()))
        {
            break;
        }
        ++module;
    }
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



/*关闭事件重写----------------------------------------------------------------------------------------------*/
void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    exit(0);
}

