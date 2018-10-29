#include "mainwindow.h"

extern bool     AT_Com_ReqType(ModuleDeal *module_deal, uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_ReadID(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfTx(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfTxCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfRxCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfGPIO(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfOSC(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfSleepCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
extern bool     AT_Com_RfStateInit(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);

extern void     AT_Com_RspType(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RspID(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern uint8_t  AT_Com_RspRfTx(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num, Rf_Rx_Tx_Para &rtx_para);
extern void     AT_Com_RspRfTxCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RspRfRxCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RxAmmeter(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RspRfGPIO(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RspRfOSC(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RspRfSleepCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
extern void     AT_Com_RspRfStateInit(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);

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


    //初始化EXCEL
    Init_Excel();


    //初始化参数
    Init_Window_Para();
}

MainWindow::~MainWindow()
{
//    delete Serial_Dialog;
//    delete Excel;
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
    QAction *Add_Action      = new QAction(QIcon(":/image/add.png"), tr("Add Radio Module"), this);
    QAction *Search_Action   = new QAction(QIcon(":/image/search.png"), tr("Discover Radio Modules"), this);
    QWidget *Space1           = new QWidget(this);
    Space1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QAction *Config_Action   = new QAction(QIcon(":/image/config_perspective_selected.png"), tr("Updata working mode"), this);
    QWidget *Space2           = new QWidget(this);
    Space2->setMinimumWidth(20);
    Space2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QAction *Console_Action   = new QAction(QIcon(":/image/console_perspective_selected.png"), tr("Console working mode"), this);
    QWidget *Space3           = new QWidget(this);
    Space3->setMinimumWidth(20);
    Space3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QAction *Network_Action   = new QAction(QIcon(":/image/network_perspective_selected.png"), tr("Network working mode"), this);
    QWidget *Space4           = new QWidget(this);
    Space4->setMinimumWidth(20);
    Space4->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    Tool_Bar = new QToolBar(this);
    Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");
    Tool_Bar->setMovable(false);
    Tool_Bar->setIconSize(QSize(48,48));
    Tool_Bar->addAction(Add_Action);
    Tool_Bar->addAction(Search_Action);
    Tool_Bar->addWidget(Space1);
    Tool_Bar->addAction(Console_Action);
    Tool_Bar->addWidget(Space2);
    Tool_Bar->addAction(Config_Action);
    Tool_Bar->addWidget(Space3);
    Tool_Bar->addAction(Network_Action);
    Tool_Bar->addWidget(Space4);

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
    connect(&right_window->Console_Window->Para_Dialog, &ParaConfigDialog::Signal_Para_ToManWin, this, &MainWindow::Slot_Para_FromParaDlg);

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


/*初始化Excel---------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Init_Excel()
{
    QDate       Current_Time;
    QDir        Dir;
    QFileInfo   FileInfo;
    QString     WorkPath;
    QAxObject   *Font;

    /*---------------------------------------------------------------------------------*/
    /*有时间的话使用开源代码   qtxlsx                                                      */
    /*                                                                                 */
    /*---------------------------------------------------------------------------------*/
    //创建对象
    Excel = new QAxObject(this);


    //连接Excel控件
    Excel->setControl("Excel.Application");


    //设置窗体是否显示 true: 显示 false：不显示
    Excel->setProperty("Visible", true);

    //此处是无奈之举，当“Visible”设置为false时候，excel报错,只能把excel最小化
    Excel->setProperty("WindowState", "xlMinimized");

    //不显示任何警告信息，如果为true 那么关闭的时候回出现“文件保存”等类似信息
    Excel->setProperty("DisplayAlerts", false);

    //获取工作薄集合
    WorkBooks = Excel->querySubObject("WorkBooks");

    //获取当前时间
    Current_Time = QDate::currentDate();
    //获取工作路径
    WorkPath = Dir.currentPath();
    WorkPath +="/";
    WorkPath += (QString("%1").arg(Current_Time.year(),  4, 10, QLatin1Char('0')).toUpper()+"-");
    WorkPath += (QString("%1").arg(Current_Time.month(), 2, 10, QLatin1Char('0')).toUpper()+"-");
    WorkPath += (QString("%1").arg(Current_Time.day(),   2, 10, QLatin1Char('0')).toUpper());
    WorkPath += ".xlsx";

    //打开工作薄 如果存在打开如果不存新建
    FileInfo.setFile(WorkPath);
    if (FileInfo.isFile())
    {
        //打开工作薄
        WorkBook = WorkBooks->querySubObject("Open(const QString&)", WorkPath);

        //获取所有的Sheets
        WorkSheets = WorkBook->querySubObject("Sheets");

        //获取第一个Sheet
        WorkSheet = WorkSheets->querySubObject("Item(int)",1);
    }
    else
    {
        WorkBooks->dynamicCall("Add"); // 新建一个工作簿
        WorkBook = Excel->querySubObject("ActiveWorkBook"); // 获取当前工作簿

        //获取所有的Sheets
        WorkSheets = WorkBook->querySubObject("Sheets");

        //获取第一个Sheet
        WorkSheet = WorkSheets->querySubObject("Item(int)",1);

        //设置单元格标题
        QAxObject *Cell;
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 1);
        Cell->dynamicCall("SetValue(conts QVariant&)", "STATUS");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 2);
        Cell->dynamicCall("SetValue(conts QVariant&)", "NOID_ID");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 3);
        Cell->dynamicCall("SetValue(conts QVariant&)", "TX_RSSI");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 4);
        Cell->dynamicCall("SetValue(conts QVariant&)", "TX_PER");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 5);
        Cell->dynamicCall("SetValue(conts QVariant&)", "RX_RSSI");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 6);
        Cell->dynamicCall("SetValue(conts QVariant&)", "RX_PER");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 7);
        Cell->dynamicCall("SetValue(conts QVariant&)", "TX_CURRENT");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 8);
        Cell->dynamicCall("SetValue(conts QVariant&)", "RX_CURRENT");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 9);
        Cell->dynamicCall("SetValue(conts QVariant&)", "SLEEP_CURRENT");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 10);
        Cell->dynamicCall("SetValue(conts QVariant&)", "GPIO");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 11);
        Cell->dynamicCall("SetValue(conts QVariant&)", "OSC");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 12);
        Cell->dynamicCall("SetValue(conts QVariant&)", "FAIL_BITS");
        Cell = WorkSheet->querySubObject("Cells(int, int)", 1, 13);
        Cell->dynamicCall("SetValue(conts QVariant&)", "TIME");

        //设置自适应宽度
        QAxObject *autoFitRange = WorkSheet->querySubObject("Columns(A:M)");
        autoFitRange->dynamicCall("AutoFit");

        //设置字体居中
        autoFitRange->setProperty("HorizontalAlignment",-4108);

        autoFitRange = WorkSheet->querySubObject("Rows(1)");
        Font = autoFitRange->querySubObject("Font");
        Font->setProperty("Bold", true);                             //设置单元格字体加粗

        //保存文件
        WorkBook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(WorkPath));
    }


//    //读取Excel表格数据并显示
//    QAxObject *UsedRange = WorkSheet->querySubObject("UsedRange");
//    WorkRow              = UsedRange->querySubObject("Rows");
//    WorkColumn           = UsedRange->querySubObject("Columns");
//    StartRow             = UsedRange->property("Row").toInt();
//    StartColumn          = UsedRange->property("Column").toInt();
//    AllRowsNum           = WorkRow->property("Count").toInt();
//    AllColumnsNum        = WorkRow->property("Count").toInt();
//    for (unsigned int num=StartRow+1; num<=AllRowsNum; num++)
//    {
//        Cell_1 = WorkSheet->querySubObject("Cells(int, int)", num, 2);
//        Cell_2 = WorkSheet->querySubObject("Cells(int, int)", num, 13);

//        temp_str1 = Cell_1->dynamicCall("Value()").toString();
//        temp_str2 = Cell_2->dynamicCall("Value()").toString();

//        this->right_window->Console_Window->Set_ExcelNodeIdShow((num-1), temp_str1, temp_str2);
//    }


    //关闭文件
    //WorkBook->dynamicCall("Close(Boolean)", false);     //关闭文件
    //Excel->dynamicCall("Quit(void)");                   //关闭exce

    //delete Excel;
}


/*初始化窗体参数--------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Init_Window_Para()
{
    Test_Run_State = NullState;

    DM_PortName = "";
    DP_PortName = "";

    DMP_RtxPara.rssi = 0;
    DMP_RtxPara.rx_num = 0;
    DMP_RtxPara.tx_num = 0;

    right_window->Console_Window->Para_Dialog.Read_Para(ParaDataMin, ParaDataMax, NumParaRow);

    setAttribute(Qt::WA_DeleteOnClose);
}


/*Excel 节点校准保存----------------------------------------------------------------------------------------------------------------*/
void MainWindow::Excel_Node_Save(Excel_Save_Para &excel_save_para)
{
    QDateTime current_time;
    QAxObject *Cell;
    QAxObject* Font;
    QString temp_id = "";
    unsigned int  num = 0;


    //获取Sheet范围,获取起始行，起始列，总行数，总列数
    QAxObject *UsedRange = WorkSheet->querySubObject("UsedRange");
    WorkRow              = UsedRange->querySubObject("Rows");
    WorkColumn           = UsedRange->querySubObject("Columns");
    StartRow             = UsedRange->property("Row").toInt();
    StartColumn          = UsedRange->property("Column").toInt();
    AllRowsNum           = WorkRow->property("Count").toInt();
    AllColumnsNum        = WorkRow->property("Count").toInt();


    //整体测试状态
    if (excel_save_para.fail_bits == 0x0000)
    {
        excel_save_para.status      = true;
        excel_save_para.status_str  = "PASS";
        excel_save_para.fail_bits  |= ((0) << 0);
    }
    else
    {
        excel_save_para.status      = false;
        excel_save_para.status_str      = "FAIL";
        excel_save_para.fail_bits  |= ((1) << 0);
    }
    excel_save_para.fial_bits_str = "0x";
    excel_save_para.fial_bits_str += QString("%1").arg(excel_save_para.fail_bits, 4, 16, QLatin1Char('0')).toUpper();


    //写入时间
    current_time = QDateTime::currentDateTime();
    excel_save_para.time = current_time.toString("yyyy-MM-dd hh:mm:ss");


    //Text Edit窗体显示
    this->right_window->Console_Window->Set_ExcelNodeIdShow(excel_save_para.status_str, excel_save_para.noid_id, excel_save_para.time);
    emit this->right_window->Console_Window->Start_Action->trigger();

    //判断节点是否存在
    for (num=StartRow+1; num<=AllRowsNum; num++)
    {
        Cell = WorkSheet->querySubObject("Cells(int, int)", num, 2);
        temp_id = Cell->dynamicCall("Value()").toString();
        if (temp_id == excel_save_para.noid_id)
        {
            break;
        }
    }


    //添加节点
    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 1);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 0)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.status_str);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 2);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 1)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.noid_id);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 3);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 2)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.tx_rssi);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 4);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 3)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->setProperty("NumberFormatLocal", "0.0%");
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.tx_per);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 5);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 4)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.rx_rssi);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 6);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 5)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->setProperty("NumberFormatLocal", "0.0%");
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.rx_per);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 7);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 6)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.tx_current);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 8);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 7)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.rx_current);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 9);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 8)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.sleep_current);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 10);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 9)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.gpio);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 11);
    Font = Cell->querySubObject("Font");
    if ((excel_save_para.fail_bits & (1 << 10)) != 0)
    {
        Font->setProperty("Color", QColor(255, 0, 0));
    }
    else
    {
        Font->setProperty("Color", QColor(0, 0, 0));
    }
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.osc);



    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 12);
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.fial_bits_str);


    Cell = WorkSheet->querySubObject("Cells(int, int)", num, 13);
    Cell->setProperty("NumberFormatLocal", "yyyy/mm/dd hh:mm:ss");
    Cell->dynamicCall("SetValue(conts QVariant&)", excel_save_para.time);


    //设置自适应宽度
    QAxObject *autoFitRange = WorkSheet->querySubObject("Columns(A:M)");
    autoFitRange->dynamicCall("AutoFit");

    //设置字体居中
    autoFitRange->setProperty("HorizontalAlignment",-4108);

    //保存
    WorkBook->dynamicCall("Save()");
}








/*Hash配置-------------------------------------------------------------------------------------------------------------------------*/
void MainWindow::Hash_Set_Deal(QString portname, uint8_t type_fun, uint8_t type_para)
{
    auto module = Module_Deal_Hash.begin();
    while (module != Module_Deal_Hash.end())
    {
        if ((module.key() == portname))
        {
            auto temp_serialtxrxPara = module.value()->serialtxrxPara;
            switch(type_fun)
            {
                case MODULE_REQ_NULL:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_REQ_NULL;
                    temp_serialtxrxPara->tx_func_type       = MODULE_REQ_NULL;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x00;
                        temp_serialtxrxPara->tx_num             = 0x00;
                        temp_serialtxrxPara->tx_interval        = 0x00;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = 0x00;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_TYPE_REQ_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_TYPE_REQ_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_TYPE_REQ_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_TYPE_REQ_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_TYPE_REQ_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_TYPE_REQ_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_TYPE_REQ_REF_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_TYPE_REQ_REF_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_TYPE_REQ_REF_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_TYPE_REQ_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_TYPE_REQ_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_TYPE_REQ_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_READ_ID_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_READ_ID_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_READ_ID_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_READ_ID_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_READ_ID_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_READ_ID_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_RF_TX_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_RF_TX_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_RF_TX_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_RF_TX_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_RF_TX_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_RF_TX_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_RF_RX_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_RF_RX_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_RF_RX_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_RF_RX_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_RF_RX_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_RF_RX_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_CURRENT_TX_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_CURRENT_TX_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_CURRENT_TX_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_CURRENT_TX_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_CURRENT_TX_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_CURRENT_TX_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_CURRENT_RX_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_CURRENT_RX_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_CURRENT_RX_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_CURRENT_RX_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_CURRENT_RX_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_CURRENT_RX_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_GPIO_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_GPIO_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_GPIO_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_GPIO_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_GPIO_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_GPIO_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }


                case MODULE_OSC_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_OSC_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_OSC_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_OSC_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_OSC_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_OSC_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_CURRENT_SLEEP_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_CURRENT_SLEEP_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_CURRENT_SLEEP_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_CURRENT_SLEEP_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_CURRENT_SLEEP_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_CURRENT_SLEEP_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_RF_STATE_INIT_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_RF_STATE_INIT_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_RF_STATE_INIT_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = MODULE_RF_STATE_INIT_NUM;
                        temp_serialtxrxPara->tx_interval        = MODULE_RF_STATE_INIT_INTERVAL;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = MODULE_RF_STATE_INIT_NUM;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }

                case MODULE_AMMETER_RX_FUN:
                {
                    temp_serialtxrxPara->rx_func_type       = MODULE_AMMETER_RX_FUN;
                    temp_serialtxrxPara->tx_func_type       = MODULE_AMMETER_RX_FUN;
                    if (type_para == 0)
                    {
                        temp_serialtxrxPara->frame_id           = 0x01;
                        temp_serialtxrxPara->tx_num             = 0x01;
                        temp_serialtxrxPara->tx_interval        = 0x00;
                        temp_serialtxrxPara->tx_count           = 0x00;
                        temp_serialtxrxPara->search_count       = 0x00;
                        temp_serialtxrxPara->search_total_count = 0x00;
                        temp_serialtxrxPara->search_total_flag  = 0x00;
                    }

                    break;
                }
            }
        }
        ++module;
    }
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

    disconnect(Module_Deal_Hash.value(portname)->moduleWindow, &ModuleWindow::Signal_ModuleWinClose, this, Close_ModuleWindow);
    disconnect(Module_Deal_Hash.value(portname)->moduleWindow, &ModuleWindow::Signal_MousePress, this, MousePress_ModuleWindow);

    delete Module_Deal_Hash.value(portname)->serialThread;
    delete Module_Deal_Hash.value(portname)->serialtxrxPara;

    Module_Deal_Hash.remove(portname);
}


/*模块对话框鼠标单击事件相应处理 槽函数-------------------------------------------------------------------------*/
void MainWindow::MousePress_ModuleWindow(const QString &portname, const QString &moduletype)
{
    if (moduletype != "DA")
    {
        if ((Module_Deal_Hash.value(portname)->serialtxrxPara->rx_func_type == MODULE_REQ_NULL) &&
            (Module_Deal_Hash.value(portname)->serialtxrxPara->tx_func_type == MODULE_REQ_NULL))
        {
            DMPA_PortName = portname;

            Module_Deal_Hash.value(portname)->moduleWindow->ModuleInfo_Clear();

            //请求模块相关信息
            this->Hash_Set_Deal(portname, MODULE_TYPE_REQ_REF_FUN, 0);

            //显示搜索对话框
            search_dialog.Port_Name = portname;
            search_dialog.show();
        }
    }
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

    right_window->Console_Window->Set_RecordLabel(++Test_Run_Num);

    switch (Test_Run_State)
    {
        case RfTransmit:
        case RfReceive:
        {
            QString str = "";
            int num = (Test_Run_Num % 5);
            str =  "RSSI:###";
            str += "  PER:#####";
            str += "  TX:";
            str += QString::number(DMP_RtxPara.tx_num);
            str += "  RX:";
            for (int i=0; i<num; i++)
            {
                str += "*";
            }
            right_window->Console_Window->NameText[Test_Run_State-1]->setText(str);

            break;
        }

        case CurrentTransmit:
        case CurrentReceive:
        case CurrentSleep:
        case GPIO:
        case CrystalOsc:
        {
            QString str = "";
            int num = (Test_Run_Num % 5);
            for (int i=0; i<num; i++)
            {
                str += "*";
            }
            right_window->Console_Window->NameText[Test_Run_State-1]->setText(str);

            break;
        }
    }
}


/*参数获取 槽函数----------------------------------------------------------------------------------------------*/
void MainWindow::Slot_Para_FromParaDlg(const float *paradatamin, const float *paradatamax, int num)
{
    for (int i=0; i<num; i++)
    {
        ParaDataMin[i] = paradatamin[i];
        ParaDataMax[i] = paradatamax[i];
    }
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

        this->Hash_Set_Deal(DM_PortName, MODULE_READ_ID_FUN, 0);


        Excel_SavePara.status          = false;
        Excel_SavePara.fail_bits       = 0x0000;
        Excel_SavePara.status_str      = "";
        Excel_SavePara.noid_id         = "";
        Excel_SavePara.tx_rssi         = "";
        Excel_SavePara.tx_per          = "";
        Excel_SavePara.rx_rssi         = "";
        Excel_SavePara.rx_per          = "";
        Excel_SavePara.tx_current      = "";
        Excel_SavePara.rx_current      = "";
        Excel_SavePara.sleep_current   = "";
        Excel_SavePara.gpio            = "";
        Excel_SavePara.osc             = "";
        Excel_SavePara.fial_bits_str   = "";
        Excel_SavePara.time            = "";
    }
    else
    {
        Test_Run_State = NullState;
        Test_Run_Num = 0;
        right_window->Console_Window->Set_RecordLabel(Test_Run_Num);
        Test_Run_Timer->stop();

        this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
        this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

        DM_PortName = "";
        DP_PortName = "";
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
        connect(Module_Deal->moduleWindow, &ModuleWindow::Signal_MousePress, this, MousePress_ModuleWindow);


        //模块串口线程创建
        Module_Deal->serialThread = new SerialThread(this);
        connect(Module_Deal->serialThread, &SerialThread::SerialRxData, this, Receive_SerialMessage);


        //模块串口发送接收相关参数创建
        Module_Deal->serialtxrxPara = new SerialTxRxPara;
        Module_Deal->serialtxrxPara->rx_func_type        = MODULE_REQ_NULL;
        Module_Deal->serialtxrxPara->tx_func_type        = MODULE_REQ_NULL;
        Module_Deal->serialtxrxPara->frame_id            = 0x00;
        Module_Deal->serialtxrxPara->tx_num              = 0x00;
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
        //获取串口名字
        DMPA_PortName = Serial_Dialog->Serial_Port_Settings.portName;

        //请求模块相关信息
        this->Hash_Set_Deal(Serial_Dialog->Serial_Port_Settings.portName, MODULE_TYPE_REQ_FUN, 0);

        //显示搜索对话框
        search_dialog.Port_Name = Serial_Dialog->Serial_Port_Settings.portName;
        search_dialog.show();
    }
}



/*串口接收处理--------------------------------------------------------------------------------------------------------------*/
void MainWindow::Port_Receive_Deal(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t   deal_type = 0;

    auto para = module_deal->serialtxrxPara;

    switch (para->rx_func_type)
    {
        case MODULE_TYPE_REQ_FUN:
            AT_Com_RspType(module_deal, rx_buf, rx_num);
        break;

        case MODULE_TYPE_REQ_REF_FUN:
            AT_Com_RspType(module_deal, rx_buf, rx_num);
        break;

        case MODULE_AMMETER_RX_FUN:
            AT_Com_RxAmmeter(module_deal, rx_buf, rx_num);
        break;

        case MODULE_READ_ID_FUN:
            AT_Com_RspID(module_deal, rx_buf, rx_num);
        break;

        case MODULE_RF_TX_FUN:
        {
            deal_type = AT_Com_RspRfTx(module_deal, rx_buf, rx_num, DMP_RtxPara);
            switch (deal_type)
            {
                case 1:
                    this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 1);
                    this->Hash_Set_Deal(DM_PortName, MODULE_RF_TX_FUN, 1);
                    Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->frame_id =Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->frame_id;
                    Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_num   =Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_num;
                    Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_count =Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_count;
                break;

                case 2:
                break;

                case 3:
                    this->Hash_Set_Deal(DP_PortName, MODULE_RF_TX_FUN, 1);
                    this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 1);
                    Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->frame_id =Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->frame_id;
                    Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_num   =Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_num;
                    Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_count =Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_count;
                break;

                case 4:
                break;
            }

            break;
        }

        case MODULE_RF_RX_FUN:
        {
            deal_type = AT_Com_RspRfTx(module_deal, rx_buf, rx_num, DMP_RtxPara);
            switch (deal_type)
            {
                case 1:
                    this->Hash_Set_Deal(DP_PortName, MODULE_RF_RX_FUN, 1);
                    this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 1);
                    Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->frame_id =Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->frame_id;
                    Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_num   =Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_num;
                    Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_count =Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_count;
                break;

                case 2:
                break;

                case 3:
                    this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 1);
                    this->Hash_Set_Deal(DM_PortName, MODULE_RF_RX_FUN, 1);
                    Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->frame_id =Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->frame_id;
                    Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_num   =Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_num;
                    Module_Deal_Hash.value(DM_PortName)->serialtxrxPara->tx_count =Module_Deal_Hash.value(DP_PortName)->serialtxrxPara->tx_count;
                break;

                case 4:
                break;
            }

            break;
        }

        case MODULE_CURRENT_TX_FUN:
            AT_Com_RspRfTxCurrent(module_deal, rx_buf, rx_num);
        break;

        case MODULE_CURRENT_RX_FUN:
            AT_Com_RspRfRxCurrent(module_deal, rx_buf, rx_num);
        break;

        case  MODULE_GPIO_FUN:
            AT_Com_RspRfGPIO(module_deal, rx_buf, rx_num);
        break;

        case  MODULE_OSC_FUN:
            AT_Com_RspRfOSC(module_deal, rx_buf, rx_num);
        break;

        case  MODULE_CURRENT_SLEEP_FUN:
            AT_Com_RspRfSleepCurrent(module_deal, rx_buf, rx_num);
        break;

        case  MODULE_RF_STATE_INIT_FUN:
            AT_Com_RspRfStateInit(module_deal, rx_buf, rx_num);
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
    QString  str = "";

    func_type = module_deal->serialtxrxPara->tx_func_type;
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
                        if (module_deal->moduleWindow->Node_Type == "DA")
                        {
                            this->Hash_Set_Deal(DMPA_PortName, MODULE_AMMETER_RX_FUN, 0);
                        }
                        else
                        {
                            this->Hash_Set_Deal(DMPA_PortName, MODULE_REQ_NULL, 0);
                        }

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
                        disconnect(module_deal->moduleWindow, &ModuleWindow::Signal_ModuleWinClose, this, Close_ModuleWindow);
                        disconnect(module_deal->moduleWindow, &ModuleWindow::Signal_MousePress, this, MousePress_ModuleWindow);

                        delete module_deal->moduleWindow;
                        delete module_deal->serialThread;
                        delete module_deal->serialtxrxPara;
                        Module_Deal_Hash.remove(Serial_Dialog->Serial_Port_Settings.portName);

                        this->Hash_Set_Deal(DMPA_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }

            //模块类型数据更新
            case MODULE_TYPE_REQ_REF_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        //关闭搜索显示对话框
                        emit search_dialog.Signal_DialogClose();

                        this->Hash_Set_Deal(DMPA_PortName, MODULE_REQ_NULL, 0);

                        //设置module模块参数
                        module_deal->moduleWindow->ModuleInfo_Set();

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

                        this->Hash_Set_Deal(DMPA_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }


            //电流表电流接收处理
            case MODULE_AMMETER_RX_FUN:
            {
                if (module_deal->serialtxrxPara->tx_num == 0x00)
                {
                    DMP_RtxPara.count++;
                    DMP_RtxPara.rx_current    = module_deal->moduleWindow->Ammeter_Data;
                    DMP_RtxPara.tx_current    = module_deal->moduleWindow->Ammeter_Data;
                    DMP_RtxPara.sleep_current = module_deal->moduleWindow->Ammeter_Data;

                    right_window->Console_Window->Set_AmmeterData(module_deal->moduleWindow->Ammeter_Text);
                    module_deal->serialtxrxPara->tx_num = 0x01;
                }

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

                        this->Hash_Set_Deal(DM_PortName, MODULE_RF_TX_FUN, 0);
                        this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 1);

                        this->Hash_Set_Deal(DP_PortName, MODULE_RF_TX_FUN, 0);


                        //excel para: node_id
                        Excel_SavePara.noid_id     = module_deal->moduleWindow->Text_Content[4];
                        Excel_SavePara.fail_bits  |= ((0) << 1);

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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }


            //射频发送测试
            case MODULE_RF_TX_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        //console window相关设置
                        Test_Run_State = RfReceive;
                        right_window->Console_Window->Set_StatusText(2, 1);

                        //显示测试结果
                        {
                            str = "RSSI:";
                            str += QString::number(DMP_RtxPara.rssi);

                            str += "  PER:";
                            float rx_count = DMP_RtxPara.rx_num, tx_count = DMP_RtxPara.tx_num;

                            DMP_RtxPara.per = rx_count/tx_count;
                            DMP_RtxPara.per *= 100;
                            str += QString("%1").arg(DMP_RtxPara.per, 0, 'f',1);
                            str += "%";

                            str += "  TX:";
                            str += QString::number(DMP_RtxPara.tx_num);

                            str += "  RX:";
                            str += QString::number(DMP_RtxPara.rx_num);

                            right_window->Console_Window->NameText[1]->setText(str);
                        }

                        //下一步进行接收测试
                        this->Hash_Set_Deal(DM_PortName, MODULE_RF_RX_FUN, 0);

                        this->Hash_Set_Deal(DP_PortName, MODULE_RF_RX_FUN, 0);
                        this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 1);


                        //excel para: tx_rssi tx_per
                        Excel_SavePara.tx_rssi     = QString::number(DMP_RtxPara.rssi);
                        if ((DMP_RtxPara.rssi > ParaDataMax[1]) || (DMP_RtxPara.rssi < ParaDataMin[1]))
                        {  
                            Excel_SavePara.fail_bits  |= ((1) << 2);
                        }
                        else
                        {
                            Excel_SavePara.fail_bits  |= ((0) << 2);
                        }


                        Excel_SavePara.tx_per      = QString::number(DMP_RtxPara.per);
                        Excel_SavePara.tx_per     += "%";
                        if ((DMP_RtxPara.per < ParaDataMin[0]))
                        {
                            Excel_SavePara.fail_bits  |= ((1) << 3);
                        }
                        else
                        {
                            Excel_SavePara.fail_bits  |= ((0) << 3);
                        }

                        if ((Excel_SavePara.fail_bits & ((1) << 2)) || (Excel_SavePara.fail_bits & ((1) << 3)))
                        {
                            right_window->Console_Window->Set_NamePix(1, 2);
                        }
                        else
                        {
                            right_window->Console_Window->Set_NamePix(1, 1);
                        }


                        return true;
                    }
                    else
                    {
                        //发送请求命令
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }

            //射频接收测试
            case MODULE_RF_RX_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        //console window相关设置
                        Test_Run_State = CurrentTransmit;
                        right_window->Console_Window->Set_StatusText(3, 1);

                        //显示测试结果
                        {
                            str = "RSSI:";
                            str += QString::number(DMP_RtxPara.rssi);

                            str += "  PER:";
                            float rx_count = DMP_RtxPara.rx_num, tx_count = DMP_RtxPara.tx_num;

                            DMP_RtxPara.per = rx_count/tx_count;
                            DMP_RtxPara.per *= 100;
                            str += QString("%1").arg(DMP_RtxPara.per,0,'f',1);
                            str += "%";

                            str += "  TX:";
                            str += QString::number(DMP_RtxPara.tx_num);

                            str += "  RX:";
                            str += QString::number(DMP_RtxPara.rx_num);

                            right_window->Console_Window->NameText[2]->setText(str);
                        }

                        //下一步进行接收测试
                        DMP_RtxPara.count = 0;
                        this->Hash_Set_Deal(DM_PortName, MODULE_CURRENT_TX_FUN, 0);
                        this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);


                        //excel para: rx_rssi rx_per
                        Excel_SavePara.rx_rssi     = QString::number(DMP_RtxPara.rssi);
                        if ((DMP_RtxPara.rssi > ParaDataMax[3]) || (DMP_RtxPara.rssi < ParaDataMin[3]))
                        {
                            Excel_SavePara.fail_bits  |= ((1) << 4);
                        }
                        else
                        {
                            Excel_SavePara.fail_bits  |= ((0) << 4);
                        }

                        Excel_SavePara.rx_per      = QString::number(DMP_RtxPara.per);
                        Excel_SavePara.rx_per     += "%";
                        if ((DMP_RtxPara.per < ParaDataMin[2]))
                        {
                            Excel_SavePara.fail_bits  |= ((1) << 5);
                        }
                        else
                        {
                            Excel_SavePara.fail_bits  |= ((0) << 5);
                        }

                        if ((Excel_SavePara.fail_bits & ((1) << 4)) || (Excel_SavePara.fail_bits & ((1) << 5)))
                        {
                            right_window->Console_Window->Set_NamePix(2, 2);
                        }
                        else
                        {
                            right_window->Console_Window->Set_NamePix(2, 1);
                        }

                        return true;
                    }
                    else
                    {
                        //发送请求命令
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }


            //射频发送电流测试
            case MODULE_CURRENT_TX_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        if (DMP_RtxPara.count >= 8)
                        {
                            //console window相关设置
                            Test_Run_State = CurrentReceive;
                            right_window->Console_Window->Set_StatusText(4, 1);

                            {
                                str = QString("%1").arg(DMP_RtxPara.tx_current, 0, 'f', 3);
                                str += " mA";
                                right_window->Console_Window->NameText[3]->setText(str);
                            }

                            //下一步进行接收测试
                            DMP_RtxPara.count = 0;
                            this->Hash_Set_Deal(DM_PortName, MODULE_CURRENT_RX_FUN, 0);
                            this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                            //excel para: tx_current
                            Excel_SavePara.tx_current  = str;
                            if ((DMP_RtxPara.tx_current > ParaDataMax[4]) || (DMP_RtxPara.tx_current < ParaDataMin[4]))
                            {
                                Excel_SavePara.fail_bits  |= ((1) << 6);
                                right_window->Console_Window->Set_NamePix(3, 2);
                            }
                            else
                            {
                                Excel_SavePara.fail_bits  |= ((0) << 6);
                                right_window->Console_Window->Set_NamePix(3, 1);
                            }
                        }

                        return true;
                    }
                    else
                    {
                        //发送请求命令
                        AT_Com_RfTxCurrent(module_deal, tx_buf, tx_num);
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }

            //射频接收电流测试
            case MODULE_CURRENT_RX_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        if (DMP_RtxPara.count >= 5)
                        {
                            //console window相关设置
                            Test_Run_State = CurrentSleep;
                            right_window->Console_Window->Set_StatusText(5, 1);

                            {
                                str = QString("%1").arg(DMP_RtxPara.rx_current, 0, 'f', 3);
                                str += " mA";
                                right_window->Console_Window->NameText[4]->setText(str);
                            }

                            //下一步进行接收测试
                            DMP_RtxPara.count = 0;
                            this->Hash_Set_Deal(DM_PortName, MODULE_CURRENT_SLEEP_FUN, 0);
                            this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                            //excel para: rx_current
                            Excel_SavePara.rx_current  = str;
                            if ((DMP_RtxPara.rx_current > ParaDataMax[5]) || (DMP_RtxPara.rx_current < ParaDataMin[5]))
                            {
                                Excel_SavePara.fail_bits  |= ((1) << 7);
                                right_window->Console_Window->Set_NamePix(4, 2);
                            }
                            else
                            {
                                Excel_SavePara.fail_bits  |= ((0) << 7);
                                right_window->Console_Window->Set_NamePix(4, 1);
                            }
                        }

                        return true;
                    }
                    else
                    {
                        //发送请求命令
                        AT_Com_RfRxCurrent(module_deal, tx_buf, tx_num);
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }


            //休眠测试
            case MODULE_CURRENT_SLEEP_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        if (DMP_RtxPara.count >= 5)
                        {
                            //console window相关设置
                            Test_Run_State = GPIO;
                            right_window->Console_Window->Set_StatusText(6, 1);

                            {
                                str = QString("%1").arg(DMP_RtxPara.sleep_current, 0, 'f', 3);
                                str += " mA";
                                right_window->Console_Window->NameText[5]->setText(str);
                            }

                            //下一步进行接收测试
                            this->Hash_Set_Deal(DM_PortName, MODULE_RF_STATE_INIT_FUN, 0);
                            this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);


                            //excel para: sleep_current
                            Excel_SavePara.sleep_current  = str;
                            if ((DMP_RtxPara.sleep_current > ParaDataMax[6]) || (DMP_RtxPara.sleep_current < ParaDataMin[6]))
                            {
                                Excel_SavePara.fail_bits  |= ((1) << 8);
                                right_window->Console_Window->Set_NamePix(5, 2);
                            }
                            else
                            {
                                Excel_SavePara.fail_bits  |= ((0) << 8);
                                right_window->Console_Window->Set_NamePix(5, 1);
                            }
                        }

                        return true;
                    }
                    else
                    {
                        //发送请求命令
                        AT_Com_RfSleepCurrent(module_deal, tx_buf, tx_num);
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }


            //射频状态初始
            case MODULE_RF_STATE_INIT_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        //console window相关设置
                        Test_Run_State = GPIO;

                        //下一步进行接收测试
                        this->Hash_Set_Deal(DM_PortName, MODULE_GPIO_FUN, 0);
                        this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return true;
                    }
                    else
                    {
                        //发送请求命令
                        AT_Com_RfStateInit(module_deal, tx_buf, tx_num);
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }

            //GPIO测试
            case MODULE_GPIO_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        //console window相关设置
                        right_window->Console_Window->Set_NamePix(6, 1);
                        Test_Run_State = CrystalOsc;
                        right_window->Console_Window->Set_StatusText(7, 1);

                        right_window->Console_Window->NameText[6]->setText("OK");

                        //下一步进行接收测试
                        this->Hash_Set_Deal(DM_PortName, MODULE_OSC_FUN, 0);
                        this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        //excel para: gpio
                        Excel_SavePara.gpio  = "OK";
                        Excel_SavePara.fail_bits  |= ((0) << 9);

                        return true;
                    }
                    else
                    {
                        //发送请求命令
                        AT_Com_RfGPIO(module_deal, tx_buf, tx_num);
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

                        return false;
                    }
                }
                module_deal->serialtxrxPara->tx_count++;

                break;
            }

            //晶振测试
            case MODULE_OSC_FUN:
            {
                if (module_deal->serialtxrxPara->tx_count == 0)
                {
                    if (module_deal->serialtxrxPara->tx_num == 0)
                    {
                        //console window相关设置
                        right_window->Console_Window->Set_NamePix(7, 1);
                        Test_Run_State = NullState;
                        right_window->Console_Window->Set_StatusText(7, 2);
                        right_window->Console_Window->NameText[7]->setText("OK");


                        //下一步进行接收测试
                        DMP_RtxPara.count = 0;
                        this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);


                        //excel para: osc
                        Excel_SavePara.osc  = "OK";
                        Excel_SavePara.fail_bits  |= ((0) << 10);
                        //写入excel表格
                        Excel_Node_Save(Excel_SavePara);


                        return true;
                    }
                    else
                    {
                        //发送请求命令
                        AT_Com_RfOSC(module_deal, tx_buf, tx_num);
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

                        emit this->right_window->Console_Window->Start_Action->trigger();
                        //this->Hash_Set_Deal(DM_PortName, MODULE_REQ_NULL, 0);
                        //this->Hash_Set_Deal(DP_PortName, MODULE_REQ_NULL, 0);

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

    delete Serial_Dialog;

    //excel关闭
//    WorkBook->dynamicCall("Save()");
    WorkBook->dynamicCall("Close(Boolean)", false);     //关闭文件
    Excel->dynamicCall("Quit(void)");                   //关闭exce
    delete Excel;

    exit(0);
}

