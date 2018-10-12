#include "mainwindow.h"

extern bool     AT_Com_ReqType(ModuleDeal *module_deal, uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_ReadID(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfTx(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);

extern void     AT_Com_RspType(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RspID(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建菜单栏
    Creat_MenuBar();


    //创建工具栏
    Creat_ToolBar();


    //创建中心窗体
    Creat_CentralWidget();


    //创建定时器
    Creat_User_Timer();


    //设置窗体属性
    Set_WidgetAttributes();


    //初始化参数
    Init_Window_Para();
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
    connect(&search_dialog, &SearchDialog::Signal_CancelClose, this, &MainWindow::Close_SearchDialog);


    //定义串口对话框
    Serial_Dialog = new SerialDialog();

    //定义左窗体
    left_window  = new LeftWindow();
    left_window->resize(330, 100);
    left_window->setMinimumWidth(250);


    //定义右窗体
    right_window = new RightWindow();
    right_window->setMinimumWidth(250);
    connect(this, &MainWindow::Signal_ModuleStateChange_ToConsoleWin, right_window->Console_Window, &ConsoleWindow::Slot_ModuleStateChange_FromMainWin);
    connect(right_window->Console_Window, &ConsoleWindow::Signal_StartStopTest_ToMainWin, this, &MainWindow::Slot_StartStopTest_FromConsoleWin);


    //定义分割器
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(left_window);
    splitter->addWidget(right_window);
    splitter->setChildrenCollapsible(false);                                           //设置是否最小宽度高度限定
    splitter->setStretchFactor(1, 1);                                                  //设置拉伸:第一参数是 序号  ；第二个参数 大于1支持拉伸
    splitter->setHandleWidth(6);                                                       //设置宽度
    splitter->setStyleSheet("QSplitter::handle { background-color:rgb(215,215,215)}"); //设置颜色
    splitter->showMaximized();

    //设置布局
    this->setCentralWidget(splitter);
    this->setMinimumSize(800, 660);
    this->resize(1300, 600);
}



/*创建串口发送定时器------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Creat_User_Timer()
{
    SerialTx_Timer = new QTimer(this);

    connect(SerialTx_Timer, SIGNAL(timeout()), this, SLOT(Send_SerialMessage()));
    SerialTx_Timer->start(1);

    Test_Run_Timer = new QTimer(this);
    connect(Test_Run_Timer, SIGNAL(timeout()), this, SLOT(Slot_TestRunTimer()));
}



/*设置窗体属性----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Set_WidgetAttributes()
{
    this->setWindowTitle("N-CTU");
    this->setMinimumSize(800, 600);
}


/*初始化窗体参数--------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Init_Window_Para()
{
    Test_Run_State = NullState;

    DM_PortName = "";
    DP_PortName = "";
}




/*打开串口对话框选中串口后并进行相应的处理 槽函数------------------------------------------------------------------------------------------*/
void MainWindow::Open_SerialDialog()
{
    Serial_Dialog->SerivalDiscover();
    if (Serial_Dialog->exec() == QDialog::Accepted)
    {
        Open_Serial_Deal();
    }
}


/*串口数据接收相应处理 槽函数-----------------------------------------------------------------------------------*/
void MainWindow::Receive_SerialMessage(const QString &portname, unsigned char *rx_data, unsigned short rx_num)
{
    auto module_deal = Module_Deal_Hash.value(portname);
    Port_Receive_Deal(module_deal, rx_data, rx_num);
}



/*串口发送数据相应处理 槽函数-----------------------------------------------------------------------------------*/
void MainWindow::Send_SerialMessage()
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


/*删除模块对话框后进行相应处理 槽函数-----------------------------------------------------------------------------*/
void MainWindow::Close_ModuleWindow(const QString &portname)
{
    emit this->Signal_ModuleStateChange_ToConsoleWin(false, Module_Deal_Hash.value(portname)->moduleWindow->Text_Content[3], Module_Deal_Hash.value(portname)->moduleWindow->Node_Type);

    disconnect(Module_Deal_Hash.value(portname)->serialThread, &SerialThread::Communication_Text, right_window->Console_Window, &ConsoleWindow::Slot_CommunicationDisplay_FromMainWin);

    Module_Deal_Hash.value(portname)->serialThread->SerialClose();

    delete Module_Deal_Hash.value(portname)->serialThread;
    delete Module_Deal_Hash.value(portname)->serialtxrxPara;

    Module_Deal_Hash.remove(portname);
}



/*搜索窗口手动关闭进行相应处理 槽函数------------------------------------------------------------------------------*/
void MainWindow::Close_SearchDialog(const QString &portname)
{
    if (Module_Deal_Hash.contains(portname))
    {
        Module_Deal_Hash.value(portname)->serialtxrxPara->search_total_flag = 0x01;
    }
}


/*测试运行定时器 槽函数-----------------------------------------------------------------------------------------*/
void MainWindow::Slot_TestRunTimer()
{
    qDebug()<< "Test_Run_Num" << QString::number(Test_Run_Num);

    right_window->Console_Window->Set_RecordLabel(++Test_Run_Num);
}



/*射频测试处理 槽函数-------------------------------------------------------------------------------------------*/
void MainWindow::Slot_StartStopTest_FromConsoleWin(const bool &state, const QString &dmport, const QString &dpport)
{
    if (state)
    {
        DM_PortName = dmport;
        DP_PortName = dpport;

        Test_Run_State = ReadNodeID;
        Test_Run_Num   = 0;
        Test_Run_Timer->start(100);

        right_window->Console_Window->Set_StatusText(0, 1);

        auto temp_serialtxrxPara = Module_Deal_Hash.value(DM_PortName)->serialtxrxPara;
        temp_serialtxrxPara->func_type          = MODULE_READ_ID_FUN;
        temp_serialtxrxPara->frame_id           = 0x01;
        temp_serialtxrxPara->tx_num             = MODULE_READ_ID_NUM;
        temp_serialtxrxPara->tx_interval        = MODULE_TYPE_REQ_INTERVAL;
        temp_serialtxrxPara->tx_count           = 0x00;
        temp_serialtxrxPara->search_count       = 0x00;
        temp_serialtxrxPara->search_total_count = MODULE_TYPE_REQ_NUM;
        temp_serialtxrxPara->search_total_flag  = 0x00;


    }
    else
    {
        DM_PortName = "";
        DP_PortName = "";

        Test_Run_State = NullState;
        Test_Run_Num = 0;
        right_window->Console_Window->Set_RecordLabel(Test_Run_Num);
        Test_Run_Timer->stop();

        auto temp_serialtxrxPara = Module_Deal_Hash.value(dmport)->serialtxrxPara;
        temp_serialtxrxPara->func_type          = MODULE_REQ_NULL;
        temp_serialtxrxPara->frame_id           = 0x00;
        temp_serialtxrxPara->tx_num             = 0x00;
        temp_serialtxrxPara->tx_interval        = 0x00;
        temp_serialtxrxPara->tx_count           = 0x00;
        temp_serialtxrxPara->search_count       = 0x00;
        temp_serialtxrxPara->search_total_count = 0x00;
        temp_serialtxrxPara->search_total_flag  = 0x00;
    }
}




/*串口模块添处理--------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Open_Serial_Deal()
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

        connect(Module_Deal->moduleWindow, &ModuleWindow::Signal_ModuleWinClose, this, Close_ModuleWindow);


        //模块串口线程创建
        Module_Deal->serialThread = new SerialThread(this);
        connect(Module_Deal->serialThread, &SerialThread::SerialRxData, this, Receive_SerialMessage);


        //模块串口发送接收相关参数创建
        Module_Deal->serialtxrxPara = new SerialTxRxPara;
        Module_Deal->serialtxrxPara->func_type           = MODULE_REQ_NULL;
        Module_Deal->serialtxrxPara->frame_id            = 0x00;
        Module_Deal->serialtxrxPara->func_type           = 0x00;
        Module_Deal->serialtxrxPara->tx_interval         = 0x00;
        Module_Deal->serialtxrxPara->search_count        = 0x00;
        Module_Deal->serialtxrxPara->search_total_count  = 0x00;
        Module_Deal->serialtxrxPara->search_total_flag   = 0x00;


        //插入到hash中
        Module_Deal_Hash.insertMulti(Serial_Dialog->Serial_Port_Settings.portName, Module_Deal);


        //关联通讯显示消息和槽函数
        connect(Module_Deal->serialThread, &SerialThread::Communication_Text, right_window->Console_Window, &ConsoleWindow::Slot_CommunicationDisplay_FromMainWin);
    }


    //打开串口
    if (!Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->serialThread->SerialOpen(Serial_Dialog->Serial_Port_Settings))
    {
        //打开串口失败，从Qhash中删除
        disconnect(Module_Deal_Hash.value(Serial_Dialog->Serial_Port_Settings.portName)->serialThread, &SerialThread::Communication_Text, right_window->Console_Window, &ConsoleWindow::Slot_CommunicationDisplay_FromMainWin);
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
        temp_serialtxrxPara->search_count       = 0x00;
        temp_serialtxrxPara->search_total_count = MODULE_TYPE_REQ_NUM;
        temp_serialtxrxPara->search_total_flag  = 0x00;

        //显示搜索对话框
        search_dialog.Port_Name = Serial_Dialog->Serial_Port_Settings.portName;
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

        case MODULE_READ_ID_FUN:
            AT_Com_RspID(module_deal, rx_buf, rx_num);
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
                        module_deal->serialtxrxPara->search_count       = 0x00;
                        module_deal->serialtxrxPara->search_total_count = 0x01;
                        module_deal->serialtxrxPara->search_total_flag  = 0x00;

                        //设置module模块参数
                        module_deal->moduleWindow->ModuleInfo_Set();

                        //添加module window模块
                        emit this->Signal_ModuleStateChange_ToConsoleWin(true, module_deal->moduleWindow->Text_Content[3], module_deal->moduleWindow->Node_Type);
                        left_window->Add_SubWidget(Module_Deal_Hash);

                        return true;
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
                    if ((module_deal->serialtxrxPara->tx_count > module_deal->serialtxrxPara->tx_interval)
                         || (module_deal->serialtxrxPara->search_total_flag == 0x01))
                    {
                        if (module_deal->serialtxrxPara->search_total_flag == 0x00)
                        {
                            //发送搜索对话框关闭消息
                            emit search_dialog.Signal_DialogClose();

                            //告警提示
                            QMessageBox::critical(NULL, "Error discovering device",
                                                  module_deal->moduleWindow->Text_Content[3]+" > Read Module Failed: Module not valid                           ", QMessageBox::Ok);
                        }

                        //等待应答超时，关闭串口从Qhash中删除
                        disconnect(module_deal->serialThread, &SerialThread::Communication_Text, right_window->Console_Window, &ConsoleWindow::Slot_CommunicationDisplay_FromMainWin);
                        module_deal->serialThread->SerialClose();
                        delete module_deal->moduleWindow;
                        delete module_deal->serialThread;
                        delete module_deal->serialtxrxPara;
                        Module_Deal_Hash.remove(Serial_Dialog->Serial_Port_Settings.portName);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }

            //模块ID读取
            case MODULE_READ_ID_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        right_window->Console_Window->Set_NamePix(0, 1);
                        right_window->Console_Window->NameText[0]->setText(module_deal->moduleWindow->Text_Content[4]);

                        Test_Run_State = RfTransmit;
                        right_window->Console_Window->Set_StatusText(1, 1);

                        module_deal->serialtxrxPara->func_type          = MODULE_RF_TX_FUN;
                        module_deal->serialtxrxPara->frame_id           = module_deal->serialtxrxPara->frame_id;
                        module_deal->serialtxrxPara->tx_num             = MODULE_RF_TX_NUM;
                        module_deal->serialtxrxPara->tx_interval        = MODULE_RF_TX_INTERVAL;
                        module_deal->serialtxrxPara->tx_count           = 0x00;
                        module_deal->serialtxrxPara->search_count       = 0x00;
                        module_deal->serialtxrxPara->search_total_count = MODULE_RF_TX_NUM;
                        module_deal->serialtxrxPara->search_total_flag  = 0x00;

                        return true;
                    }
                    else
                    {
                        //发送请求命令
                        AT_Com_ReadID(module_deal, tx_buf, tx_num);
                        module_deal->serialThread->SerialTxData(tx_buf, tx_num);
                    }
                }
                else
                {
                    if ((module_deal->serialtxrxPara->tx_count > module_deal->serialtxrxPara->tx_interval)
                         || (module_deal->serialtxrxPara->search_total_flag == 0x01))
                    {
                        if (module_deal->serialtxrxPara->search_total_flag == 0x00)
                        {
                            //告警提示
                            QMessageBox::critical(NULL, "Error discovering device",
                                                  module_deal->moduleWindow->Text_Content[3]+" > Read Module Failed: Module not valid                           ", QMessageBox::Ok);
                        }

                        module_deal->serialtxrxPara->func_type          = MODULE_REQ_NULL;
                        module_deal->serialtxrxPara->tx_num             = 0x00;
                        module_deal->serialtxrxPara->tx_interval        = 0x00;
                        module_deal->serialtxrxPara->tx_count           = 0x00;
                        module_deal->serialtxrxPara->search_count       = 0x00;
                        module_deal->serialtxrxPara->search_total_count = 0x01;
                        module_deal->serialtxrxPara->search_total_flag  = 0x00;

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }

            //射频发送测试
            case MODULE_RF_TX_FUN:
            {
                if ((module_deal->serialtxrxPara->tx_count == 0)
                     || (module_deal->serialtxrxPara->tx_count > module_deal->serialtxrxPara->tx_interval))
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        right_window->Console_Window->Set_NamePix(1, 1);

                        Test_Run_State = RfReceive;
                        right_window->Console_Window->Set_StatusText(2, 1);

//                        module_deal->serialtxrxPara->func_type          = MODULE_RF_TX_FUN;
//                        module_deal->serialtxrxPara->frame_id           = module_deal->serialtxrxPara->frame_id;
//                        module_deal->serialtxrxPara->tx_num             = MODULE_RF_TX_NUM;
//                        module_deal->serialtxrxPara->tx_interval        = MODULE_TYPE_REQ_INTERVAL;
//                        module_deal->serialtxrxPara->tx_count           = 0x00;
//                        module_deal->serialtxrxPara->search_count       = 0x00;
//                        module_deal->serialtxrxPara->search_total_count = MODULE_TYPE_REQ_NUM;
//                        module_deal->serialtxrxPara->search_total_flag  = 0x00;
                    }
                    else
                    {
                        //发送请求命令
                        module_deal->serialtxrxPara->tx_count = 0;
                        AT_Com_RfTx(module_deal, tx_buf, tx_num);
                        module_deal->serialThread->SerialTxData(tx_buf, tx_num);
                    }
                }
                else
                {
                    if ((module_deal->serialtxrxPara->tx_count > module_deal->serialtxrxPara->tx_interval)
                         || (module_deal->serialtxrxPara->search_total_flag == 0x01))
                    {
                        if (module_deal->serialtxrxPara->search_total_flag == 0x00)
                        {
                            //告警提示
                            QMessageBox::critical(NULL, "Error discovering device",
                                                  module_deal->moduleWindow->Text_Content[3]+" > Read Module Failed: Module not valid                           ", QMessageBox::Ok);
                        }

                        module_deal->serialtxrxPara->func_type          = MODULE_REQ_NULL;
                        module_deal->serialtxrxPara->tx_num             = 0x00;
                        module_deal->serialtxrxPara->tx_interval        = 0x00;
                        module_deal->serialtxrxPara->tx_count           = 0x00;
                        module_deal->serialtxrxPara->search_count       = 0x00;
                        module_deal->serialtxrxPara->search_total_count = 0x01;
                        module_deal->serialtxrxPara->search_total_flag  = 0x00;

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

