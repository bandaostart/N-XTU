#include "modulewindow.h"

QT_USE_NAMESPACE

ModuleWindow::ModuleWindow(QWidget *parent) :
    QWidget(parent)
{
    PaintFlag = 0;

    Label = new QLabel(this);
    Label->setGeometry(0,5,60,90);
    Label->setPixmap(QPixmap(":/image/xbee_zigbee_64.png"));

    QFont font;
    font.setBold(true);
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(80);

    GroupBox = new QGroupBox(this);
    GroupBox->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");
    GroupBox->setGeometry(65,0,300,90);

    Name          = new QLabel(GroupBox);
    Name->setFont(font);
    Name->setGeometry(0, 6, 70, 15);
    Name->setAlignment(Qt::AlignRight);
    Name->setText("Name:");
    Function      = new QLabel(GroupBox);
    Function->setFont(font);
    Function->setGeometry(0, 27, 70, 15);
    Function->setAlignment(Qt::AlignRight);
    Function->setText("Function:");
    Port          = new QLabel(GroupBox);
    Port->setFont(font);
    Port->setGeometry(0, 48, 70, 15);
    Port->setAlignment(Qt::AlignRight);
    Port->setText("Port:");
    Mac           = new QLabel(GroupBox);
    Mac->setFont(font);
    Mac->setGeometry(0, 69, 70, 15);
    Mac->setAlignment(Qt::AlignRight);
    Mac->setText("MAC:");

    font.setWeight(40);
    Name_Text     = new QLabel(GroupBox);
    Name_Text->setFont(font);
    Name_Text->setGeometry(80, 6, 140, 15);
    Name_Text->setAlignment(Qt::AlignLeft);
    Name_Text->setText("");
    Function_Text = new QLabel(GroupBox);
    Function_Text->setFont(font);
    Function_Text->setGeometry(80, 27, 140, 15);
    Function_Text->setAlignment(Qt::AlignLeft);
    Function_Text->setText("Zigbee Coordinator API");
    Port_Text     = new QLabel(GroupBox);
    Port_Text->setFont(font);
    Port_Text->setGeometry(80, 48, 140, 15);
    Port_Text->setAlignment(Qt::AlignLeft);
    Port_Text->setText("COM10");
    Mac_Text      = new QLabel(GroupBox);
    Mac_Text->setFont(font);
    Mac_Text->setGeometry(80, 69, 140, 15);
    Mac_Text->setAlignment(Qt::AlignLeft);
    Mac_Text->setText("");


    ToolBar =  new QToolBar(this);
    ToolBar->setOrientation( Qt::Vertical);
    ToolBar->setGeometry(370,0,20,90);
    ToolBar->setStyleSheet("QToolBar{border-style:outset}");
    ToolBar->setIconSize(QSize(20,20));
    QAction *RemoveAction     = new QAction(QIcon(":/image/delete.png"), tr("Remove this radio module from the list"), this);
    ToolBar->addAction(RemoveAction);
    QAction *DiscoverAction   = new QAction(QIcon(":/image/find.png"), tr("Discover radio nodes in the same network"), this);
    ToolBar->addAction(DiscoverAction);
    QAction *HideAction       = new QAction(QIcon(":/image/expand.png"), tr("Hdie the remote notes"), this);
    ToolBar->addAction(HideAction);


    HboxLayout =  new QHBoxLayout(this);

    HboxLayout->addWidget(Label);
    HboxLayout->addWidget(GroupBox);
    HboxLayout->addWidget(ToolBar);
    HboxLayout->setStretch(1, 10);

    this->setMinimumHeight(100);
    this->setMaximumHeight(100);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    this->setCursor(QCursor(Qt::PointingHandCursor));
}

ModuleWindow::~ModuleWindow()
{

}



void ModuleWindow::paintEvent(QPaintEvent *event)
{
        Q_UNUSED(event);

        QBrush   brush;
        QPen     pen;
        QPainter painter(this);

        if (PaintFlag == 1)
        {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(QColor(255,184,61));

            brush.setColor(QColor(255,184,61));
            brush.setStyle(Qt::SolidPattern);
        }
        else
        {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(QColor(215,215,215));

            brush.setColor(QColor(215,215,215));
            brush.setStyle(Qt::SolidPattern);
        }

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(0, 0, this->width(),this->height());


        if (PaintFlag == 1)
        {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(QColor(255,255,190));

            brush.setColor(QColor(255,255,180));
            brush.setStyle(Qt::SolidPattern);
        }
        else
        {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(QColor(230,230,230));

            brush.setColor(QColor(230,230,230));
            brush.setStyle(Qt::SolidPattern);
        }

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(GroupBox->x(), GroupBox->y(), GroupBox->width(), GroupBox->height());
}

//鼠标进入
void ModuleWindow::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    PaintFlag = 1;
    QWidget::repaint();
}

//鼠标退出
void ModuleWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    PaintFlag = 0;
    QWidget::repaint();
}


//鼠标拖拽
void ModuleWindow::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
