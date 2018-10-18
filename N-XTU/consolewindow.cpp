#include "consolewindow.h"


ConsoleWindow::ConsoleWindow(QWidget *parent) :
    QWidget(parent)
{
    //创建上侧工具栏
    Creat_TopToolBar();

    //创建左侧工具栏
    Creat_LeftToolBar();

    //创建主显示区域
    Creat_MasterDisAre();

    //创建从显示区域
    Creat_SlaveDisAre();

    //创建记录显示区域
    Creat_RecordDisAre();

    //创建布局区域
    Creat_Layout();

    //参数初始化
    Init_Para();
}


ConsoleWindow::~ConsoleWindow()
{

}




/*创建上侧工具栏------------------------------------------------------------------------------*/
void ConsoleWindow::Creat_TopToolBar()
{
    Top_Tool_Bar = new QToolBar(this);
    Top_Tool_Bar->setIconSize(QSize(48, 48));
    Top_Tool_Bar->setMovable(false);
    Top_Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");

    Start_Action   = new QAction(QIcon(":/image/network_start.png"), tr("Start radio test"), this);
    Record_Action  = new QAction(QIcon(":/image/console_record_start.png"), tr("Start recording the console session"), this);
    Refresh_Action = new QAction(QIcon(":/image/read_settings.png"), tr("Refresh Test Text"), this);
    Top_Tool_Bar->addAction(Start_Action);
    Top_Tool_Bar->addAction(Record_Action);
    Top_Tool_Bar->addAction(Refresh_Action);


    connect(Start_Action, &QAction::triggered, this, &ConsoleWindow::Slot_StartStopTest_FromStartAction);
    connect(Refresh_Action, &QAction::triggered, this, &ConsoleWindow::Slot_RefreshText_FromRefreshAction);
}




/*创建左侧工具栏-----------------------------------------------------------------------------*/
void ConsoleWindow::Creat_LeftToolBar()
{
    Left_Tool_Bar = new QToolBar(this);
    Left_Tool_Bar->setOrientation( Qt::Vertical);
    Left_Tool_Bar->setIconSize(QSize(48, 48));
    Left_Tool_Bar->setMovable(false);
    Left_Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");

    for (int i=0; i<4; i++)
    {
        Space[i] = new QWidget(this);
        Space[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    Master_Action   = new QAction(QIcon(":/image/xbee_digimesh_48.png"), tr("Master"), this);
    Connect_Action  = new QAction(QIcon(":/image/connect.png"), tr(""), this);
    Slave_Action    = new QAction(QIcon(":/image/xbee_digipoint_48.png"), tr("Slave"), this);

    Left_Tool_Bar->addWidget(Space[0]);
    Left_Tool_Bar->addAction(Master_Action);
    Left_Tool_Bar->addWidget(Space[1]);
    Left_Tool_Bar->addAction(Connect_Action);
    Left_Tool_Bar->addWidget(Space[2]);
    Left_Tool_Bar->addAction(Slave_Action);
    Left_Tool_Bar->addWidget(Space[3]);
}


/*创建主显示区域----------------------------------------------------------------------------*/
void ConsoleWindow::Creat_MasterDisAre()
{
    font.setBold(true);
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(80);

    Top_Group_Box    = new QGroupBox(this);
    //Top_Group_Box->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");
    Top_Group_Box->setFont(font);
    Top_Group_Box->setTitle("COM?");

    for (int i=0; i<NumTestRow; i++)
    {
        NameLabel[i] = new QLabel(Top_Group_Box);
        NameLabel[i]->setFont(font);
        NameLabel[i]->setGeometry(0, i*30+5, 150, 25);
        NameLabel[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
    NameLabel[0]->setText("Noid ID:");
    NameLabel[1]->setText("Transmitting Test:");
    NameLabel[2]->setText("Receiving Test:");
    NameLabel[3]->setText("Transmitting Current:");
    NameLabel[4]->setText("Receiving Current:");
    NameLabel[5]->setText("Sleeping Current:");
    NameLabel[6]->setText("GPIO:");
    NameLabel[7]->setText("Crystal Oscillator:");

    font.setWeight(40);
    for (int i=0; i<NumTestRow; i++)
    {
        NameText[i] = new QLineEdit(Top_Group_Box);
        NameText[i]->setFont(font);
        NameText[i]->setGeometry(160, i*30+5, 250, 25);
        NameText[i]->setAlignment(Qt::AlignLeft);
    }
    NameText[0]->setText("");
    NameText[1]->setText("");
    NameText[2]->setText("");
    NameText[3]->setText("");
    NameText[4]->setText("");
    NameText[5]->setText("");
    NameText[6]->setText("");
    NameText[7]->setText("");

    NamePix_Pixmap[0].load(":/image/blue_arrow.png");
    NamePix_Pixmap[1].load(":/image/ok.png");
    NamePix_Pixmap[2].load(":/image/error.png");
    for (int i=0; i<NumTestRow; i++)
    {
        NamePix[i] = new QLabel(Top_Group_Box);
        NamePix[i]->setAlignment(Qt::AlignVCenter);
        NamePix[i]->setGeometry(420, i*30+5, 25, 25);
        NamePix[i]->setPixmap(NamePix_Pixmap[0]);
    }


    font.setWeight(80);
    font.setPointSize(14);
    StatusText_Str[0] = "WAITING";
    StatusText_Str[1] = "RUNNING";
    StatusText_Str[2] = "SUCCESS";
    StatusText_Str[3] = "FAIL";
    for(int i=0; i<NumTestRow; i++)
    {
        StatusText[i] = new QLabel(Top_Group_Box);
        StatusText[i]->setMinimumWidth(120);
        StatusText[i]->setAlignment(Qt::AlignCenter);
        StatusText[i]->setStyleSheet("color:Green;");
        StatusText[i]->setFont(font);
        StatusText[i]->setText(StatusText_Str[0]);
        StatusText[i]->setGeometry(500, i*30+5, 120, 25);

        if (i == 0)
        {
            StatusText[i]->show();
        }
        else
        {
            StatusText[i]->hide();
        }
    }




    Top_Box_Layout = new QGridLayout(Top_Group_Box);
    for (int i=0; i<NumTestRow; i++)
    {
        Top_Box_Layout->addWidget(NameLabel[i], i, 0, 1, 1);
        Top_Box_Layout->addWidget(NameText[i],  i, 1, 1, 1);
        Top_Box_Layout->addWidget(NamePix[i],  i, 2, 1, 1);
        Top_Box_Layout->addWidget(StatusText[i], i, 3, 1, 1);
    }

}


/*创建从显示区域-----------------------------------------------------------------------------*/
void ConsoleWindow::Creat_SlaveDisAre()
{
    font.setBold(true);
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(80);
    font.setPointSize(9);

    Bottom_Group_Box = new QGroupBox(this);
    //Bottom_Group_Box->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");
    Bottom_Group_Box->setFont(font);

    Bottom_Group_Box->setTitle("COM?");
}



/*创建记录区域------------------------------------------------------------------------------*/
void ConsoleWindow::Creat_RecordDisAre()
{
    Pixmap[0].load(":/image/xbee_loading1.png");
    Pixmap[1].load(":/image/xbee_loading2.png");
    Pixmap[2].load(":/image/xbee_loading3.png");
    Pixmap[3].load(":/image/xbee_loading4.png");
    Pixmap[4].load(":/image/xbee_loading5.png");
    Pixmap[5].load(":/image/xbee_loading6.png");
    Pixmap[6].load(":/image/xbee_loading7.png");
    Pixmap[7].load(":/image/xbee_loading8.png");
    Pixmap[8].load(":/image/xbee_loading9.png");
    Pixmap[9].load(":/image/xbee_loading10.png");
    Pixmap[10].load(":/image/xbee_loading10.png");


    Right_Group_Box   = new QGroupBox(this);
    Right_Group_Box->setMinimumWidth(350);
    Right_Group_Box->setMaximumWidth(350);
    Right_Group_Box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    Right_Group_Box->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");


    Record_Label =  new QLabel(Right_Group_Box);
    Record_Label->setPixmap(Pixmap[0]);
    Record_Label->setGeometry(0, 0, 64, 64);


    Record_Text  = new QTextEdit(Right_Group_Box);
    Record_Text->setGeometry(5, 64, 100, 100);
    Record_Text->setContextMenuPolicy(Qt::CustomContextMenu);

    Record_Clear = new QAction(QIcon(":/image/delete.png"), tr("Clear All"), this);
    connect(Record_Clear, &QAction::triggered, Record_Text, &QTextEdit::clear);
    Record_SelectAll = new QAction(QIcon(":/image/micropython_console.png"), tr("Select All"), this);
    connect(Record_SelectAll, &QAction::triggered, Record_Text, &QTextEdit::selectAll);

    Record_Menu  = new QMenu(Right_Group_Box);
    Record_Menu->addAction(Record_Clear);
    Record_Menu->addAction(Record_SelectAll);

    connect(Record_Text, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(Slot_RecordMenuText_FromRecordText(QPoint)));


    Right_Box_Layout =  new QVBoxLayout(Right_Group_Box);
    Right_Box_Layout->addWidget(Record_Label);
    Right_Box_Layout->addWidget(Record_Text);
}


/*创建布局区域----------------------------------------------------------------------------*/
void ConsoleWindow::Creat_Layout()
{
    Grid_Layout      = new QGridLayout(this);
    Grid_Layout->addWidget(Top_Tool_Bar,  0, 0, 1, 3);
    Grid_Layout->addWidget(Left_Tool_Bar, 1, 0, 2, 1);
    Grid_Layout->addWidget(Top_Group_Box, 1, 1, 1, 1);
    Grid_Layout->addWidget(Bottom_Group_Box, 2 , 1, 1, 1);
    Grid_Layout->addWidget(Right_Group_Box, 1, 2, 2, 1);
}


/*参数初始化----------------------------------------------------------------------------*/
void ConsoleWindow::Init_Para()
{
    Testing_State = false;

    DM_State = false;
    DP_State = false;
}


/*设置Status Text---------------------------------------------------------------------*/
void ConsoleWindow::Set_StatusText(int count, int state)
{
    for (int i=0; i<NumTestRow; i++)
    {
        if (i == count)
        {
            StatusText[i]->show();
            StatusText[i]->setText(StatusText_Str[state]);
        }
        else
        {
            StatusText[i]->hide();
        }
    }
}



/*设置Name Pixmap---------------------------------------------------------------------*/
void ConsoleWindow::Set_NamePix(int count, int state)
{
    NamePix[count]->setPixmap(NamePix_Pixmap[state%3]);
}



/*设置Name Pixmap闪烁------------------------------------------------------------------*/
void ConsoleWindow::Set_NamePixFlicker(int count, int state)
{
   if (state)
   {
        NamePix[count]->show();
   }
   else
   {
       NamePix[count]->hide();
   }
}


/*设置Record_Label--------------------------------------------------------------------*/
void ConsoleWindow::Set_RecordLabel(int count)
{
    Record_Label->setPixmap(Pixmap[count%11]);
}









/*开启测试 槽函数------------------------------------------------------------------------*/
void ConsoleWindow::Slot_StartStopTest_FromStartAction()
{
    if (Testing_State)
    {
        Testing_State = false;
        Start_Action->setIcon(QIcon(":/image/network_start.png"));
    }
    else
    {
        for (int i=0; i<NumTestRow; i++)
        {
            NameText[i]->setText("");
            NamePix[i]->setPixmap(NamePix_Pixmap[0]);

            if (i == 0)
            {
                StatusText[i]->show();
                StatusText[i]->setText(StatusText_Str[0]);
            }
            else
            {
                StatusText[i]->hide();
            }
        }



        Testing_State = true;
        Start_Action->setIcon(QIcon(":/image/network_stop.png"));
    }

    emit this->Signal_StartStopTest_ToMainWin(Testing_State, DM_Port, DP_Port);
}



/*复位清空测试列表 槽函数---------------------------------------------------------------*/
void ConsoleWindow::Slot_RefreshText_FromRefreshAction()
{
    for (int i=0; i<NumTestRow; i++)
    {
        NameText[i]->setText("");
        NamePix[i]->setPixmap(NamePix_Pixmap[0]);

        if (i == 0)
        {
            StatusText[i]->show();
            StatusText[i]->setText(StatusText_Str[0]);
        }
        else
        {
            StatusText[i]->hide();
        }
    }
}



/*通讯显示 槽函数----------------------------------------------------------------------*/
void ConsoleWindow::Slot_CommunicationDisplay_FromMainWin(const QString &str)
{
    Record_Text->insertPlainText(str);
    Record_Text->insertPlainText("\n\n");
    Record_Text->moveCursor(QTextCursor::End);
}



/*TextEdit鼠标右键重写 槽函数----------------------------------------------------------*/
void ConsoleWindow::Slot_RecordMenuText_FromRecordText(QPoint)
{
    Record_Menu->move (cursor().pos());
    Record_Menu->show();
}



/*Module State Change 槽函数--------------------------------------------------------*/
void ConsoleWindow::Slot_ModuleStateChange_FromMainWin(bool add_delete, QString portname, QString noidtype)
{
    if (add_delete)
    {
        if (noidtype == "DM")
        {
            Top_Group_Box->setTitle(portname);
            DM_Port  = portname;
            DM_State = true;
        }
        else
        {
            Bottom_Group_Box->setTitle(portname);
            DP_Port = portname;
            DP_State = true;
        }

        if (DM_State && DP_State)
        {
            Connect_Action->setIcon(QIcon(":/image/disconnect.png"));
        }
    }
    else
    {
        if (noidtype == "DM")
        {
            Top_Group_Box->setTitle("COM?");
            DM_Port  = "COM?";
            DM_State = false;
        }
        else
        {
            Bottom_Group_Box->setTitle("COM?");
            DP_Port  = "COM?";
            DP_State = false;
        }

        if (DM_State && DP_State)
        {

        }
        else
        {
            Connect_Action->setIcon(QIcon(":/image/connect.png"));
        }
    }
}





/*窗体重绘事件--------------------------------------------------------------------------------*/
void ConsoleWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QBrush   brush;
    QPen     pen;
    QPainter painter(this);

    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(215,215,215));

    brush.setColor(QColor(215,215,215));
    brush.setStyle(Qt::SolidPattern);


    //设置背景色
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(Top_Tool_Bar->x(), Top_Tool_Bar->y(), Top_Tool_Bar->width(), Top_Tool_Bar->height());
    painter.drawRect(Left_Tool_Bar->x(), Left_Tool_Bar->y(), Left_Tool_Bar->width(), Left_Tool_Bar->height());
    painter.drawRect(Top_Group_Box->x(), Top_Group_Box->y(), Top_Group_Box->width(), Top_Group_Box->height());
    painter.drawRect(Bottom_Group_Box->x(), Bottom_Group_Box->y(), Bottom_Group_Box->width(), Bottom_Group_Box->height());
    painter.drawRect(Right_Group_Box->x(), Right_Group_Box->y(), Right_Group_Box->width(), Right_Group_Box->height());


    //画连接线
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(72,170,6));
    painter.setPen(pen);
    painter.drawLine(QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Left_Tool_Bar->height()/2),
                     QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Space[1]->y()-24));
    painter.drawLine(QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Left_Tool_Bar->height()/2),
                     QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Space[3]->y()-24));
}
