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
    Top_Tool_Bar->addAction(Start_Action);
    Top_Tool_Bar->addAction(Record_Action);


    connect(Start_Action, &QAction::triggered, this, &ConsoleWindow::Start_RfTesting);
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
    QFont font;
    font.setBold(true);
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(80);

    Top_Group_Box    = new QGroupBox(this);
    //Top_Group_Box->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");
    Top_Group_Box->setTitle("COM10");

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
    NameText[0]->setText("Noid ID:");
    NameText[1]->setText("Transmitting Test:");
    NameText[2]->setText("Receiving Test:");
    NameText[3]->setText("Transmitting Current:");
    NameText[4]->setText("Receiving Current:");
    NameText[5]->setText("Sleeping Current:");
    NameText[6]->setText("GPIO:");
    NameText[7]->setText("Crystal Oscillator:");

    for (int i=0; i<NumTestRow; i++)
    {
        NamePix[i] = new QLabel(Top_Group_Box);
        NamePix[i]->setAlignment(Qt::AlignVCenter);
        NamePix[i]->setGeometry(420, i*30+5, 25, 25);
        NamePix[i]->setPixmap(QPixmap(":/image/blue_arrow.png"));
    }

    font.setWeight(80);
    font.setPointSize(14);
    StatusText = new QLabel(Top_Group_Box);
    StatusText->setMinimumWidth(120);
    StatusText->setAlignment(Qt::AlignCenter);
    StatusText->setStyleSheet("color:Green;");
    StatusText->setFont(font);
    StatusText->setText("SUCCESS");
    StatusText->setGeometry(500, 5, 120, 25);

    StatusPix  = new QLabel(Top_Group_Box);
    StatusPix->setAlignment(Qt::AlignCenter);
//    StatusPix->setPixmap(QPixmap(":/image/face-smile.png"));
    StatusPix->setGeometry(500, 55, 120, 75);

    Top_Box_Layout = new QGridLayout(Top_Group_Box);
    for (int i=0; i<NumTestRow; i++)
    {
        Top_Box_Layout->addWidget(NameLabel[i], i, 0, 1, 1);
        Top_Box_Layout->addWidget(NameText[i],  i, 1, 1, 1);
        Top_Box_Layout->addWidget(NamePix[i],  i, 2, 1, 1);
    }
    Top_Box_Layout->addWidget(StatusText, 0, 3, 1, 1);
    Top_Box_Layout->addWidget(StatusPix, 1, 3, 3, 1);
}


/*创建从显示区域-----------------------------------------------------------------------------*/
void ConsoleWindow::Creat_SlaveDisAre()
{
    Bottom_Group_Box = new QGroupBox(this);
    //Bottom_Group_Box->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");
    Bottom_Group_Box->setTitle("COM10");
}



/*创建记录区域------------------------------------------------------------------------------*/
void ConsoleWindow::Creat_RecordDisAre()
{
    Right_Group_Box   = new QGroupBox(this);
    Right_Group_Box->setMinimumWidth(330);
    Right_Group_Box->setMaximumWidth(330);
    Right_Group_Box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    Right_Group_Box->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");


    Record_Label =  new QLabel(Right_Group_Box);
    Record_Label->setPixmap(QPixmap(":/image/xbee_loading1.png"));
    Record_Label->setGeometry(0, 0, 64, 64);


    Record_Text  = new QTextEdit(Right_Group_Box);
    Record_Text->setGeometry(5, 64, 100, 100);
    Record_Text->setContextMenuPolicy(Qt::CustomContextMenu);

    Record_Clear = new QAction(QIcon(":/image/delete.png"), tr("Clear Text"), this);
    connect(Record_Clear, &QAction::triggered, Record_Text, &QTextEdit::clear);
    Record_SelectAll = new QAction(QIcon(":/image/micropython_console.png"), tr("Select All"), this);
    connect(Record_SelectAll, &QAction::triggered, Record_Text, &QTextEdit::selectAll);

    Record_Menu  = new QMenu(Right_Group_Box);
    Record_Menu->addAction(Record_Clear);
    Record_Menu->addAction(Record_SelectAll);

    connect(Record_Text, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(Record_MenuText(QPoint)));


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
}








/*开启测试 槽函数------------------------------------------------------------------------*/
void ConsoleWindow::Start_RfTesting()
{
    if (Testing_State)
    {
        Testing_State = false;
        Start_Action->setIcon(QIcon(":/image/network_start.png"));
        Connect_Action->setIcon(QIcon(":/image/connect.png"));
    }
    else
    {
        Testing_State = true;
        Start_Action->setIcon(QIcon(":/image/network_stop.png"));
        Connect_Action->setIcon(QIcon(":/image/disconnect.png"));
    }
    emit this->Signal_Testing_State(Testing_State);
}



/*通讯显示 槽函数----------------------------------------------------------------------*/
void ConsoleWindow::Communication_Display(const QString &str)
{
    Record_Text->insertPlainText(str);
    Record_Text->insertPlainText("\n\n");
    Record_Text->moveCursor(QTextCursor::End);
}



/*TextEdit鼠标右键重写 槽函数----------------------------------------------------------*/
void ConsoleWindow::Record_MenuText(QPoint)
{
    Record_Menu->move (cursor().pos());
    Record_Menu->show();
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


    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(Top_Tool_Bar->x(), Top_Tool_Bar->y(), Top_Tool_Bar->width(), Top_Tool_Bar->height());
    painter.drawRect(Left_Tool_Bar->x(), Left_Tool_Bar->y(), Left_Tool_Bar->width(), Left_Tool_Bar->height());
    painter.drawRect(Top_Group_Box->x(), Top_Group_Box->y(), Top_Group_Box->width(), Top_Group_Box->height());
    painter.drawRect(Bottom_Group_Box->x(), Bottom_Group_Box->y(), Bottom_Group_Box->width(), Bottom_Group_Box->height());
    painter.drawRect(Right_Group_Box->x(), Right_Group_Box->y(), Right_Group_Box->width(), Right_Group_Box->height());

    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(72,170,6));
    painter.setPen(pen);
    painter.drawLine(QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Left_Tool_Bar->height()/2),
                     QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Space[1]->y()-24));
    painter.drawLine(QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Left_Tool_Bar->height()/2),
                     QPoint(Left_Tool_Bar->x()+Left_Tool_Bar->width()/2, Left_Tool_Bar->y()+Space[3]->y()-24));
}
