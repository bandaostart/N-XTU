#include "consolewindow.h"


ConsoleWindow::ConsoleWindow(QWidget *parent) :
    QWidget(parent)
{
    Tool_Bar = new QToolBar(this);
    Tool_Bar->setIconSize(QSize(48, 48));
    Tool_Bar->setMovable(false);
    Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");

    Start_Action   = new QAction(QIcon(":/image/network_start.png"), tr("Start radio test"), this);
    Tool_Bar->addAction(Start_Action);

    Record_Action = new QAction(QIcon(":/image/console_record_start.png"), tr("Start recording the console session"), this);
    Tool_Bar->addAction(Record_Action);

    //addToolBar(Tool_Bar);

    Connect_Label = new QLabel(this);
    Connect_Label->setPixmap(QPixmap(":/image/connect.png"));
    Connect_Label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);


    Top_Group_Box    = new QGroupBox(this);
    Bottom_Group_Box = new QGroupBox(this);
    Left_Group_Box   = new QGroupBox(this);

    Grid_Layout      = new QGridLayout(this);
    Grid_Layout->addWidget(Tool_Bar, 0, 0, 1, 3);
    Grid_Layout->addWidget(Connect_Label, 1, 0, 2, 1);
    Grid_Layout->addWidget(Top_Group_Box, 1, 1, 1, 1);
    Grid_Layout->addWidget(Bottom_Group_Box, 2 , 1, 1, 1);
    Grid_Layout->addWidget(Left_Group_Box, 1, 2, 2, 1);
}


ConsoleWindow::~ConsoleWindow()
{

}



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
    painter.drawRect(Tool_Bar->x(), Tool_Bar->y(), Tool_Bar->width(), Tool_Bar->height());
//    painter.drawRect(0, 0, this->width(),this->height());

//    pen.setStyle(Qt::SolidLine);
//    pen.setColor(QColor(230,230,230));

//    brush.setColor(QColor(230,230,230));
//    brush.setStyle(Qt::SolidPattern);
}
