#include "modulewindow.h"

QT_USE_NAMESPACE

ModuleWindow::ModuleWindow(QVector<QString> &text, QWidget *parent) :
    QWidget(parent)
{
    //创建主显示区域
    Creat_MainDisArea(text);

    //创建工具栏
    Creat_ToolBar();

    //创建布局管理
    Creat_Layout();
}

ModuleWindow::~ModuleWindow()
{
}






/*创建主显示区域-------------------------------------------------------------------------------------------------------*/
void ModuleWindow::Creat_MainDisArea(QVector<QString> &text)
{
    PaintFlag = 0;

    Label = new QLabel(this);
    Label->setGeometry(0,5,60,90);


    QFont font;
    font.setBold(true);
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(80);

    GroupBox = new QGroupBox(this);
    GroupBox->setStyleSheet("QGroupBox{border-width:0;border-style:outset}");
    GroupBox->setGeometry(65,0,300,90);
    for (int i=0; i<NumParaRow; i++)
    {
        Name[i]  = new QLabel(GroupBox);
        Name[i]->setFont(font);
        Name[i]->setGeometry(0, i*21+6, 60, 15);
        Name[i]->setAlignment(Qt::AlignRight);
    }
    Name[0]->setText("Name:");
    Name[1]->setText("Function:");
    Name[2]->setText("Port:");
    Name[3]->setText("MAC:");


    font.setWeight(40);
    for (int i=0; i<NumParaRow; i++)
    {
        Name_Text[i] = new QLabel(GroupBox);
        Name_Text[i]->setFont(font);
        Name_Text[i]->setGeometry(65, i*21+6, 140, 15);
        Name_Text[i]->setAlignment(Qt::AlignLeft);
    }
    Name_Text[0]->setText(text.at(1));
    Name_Text[1]->setText(text.at(2));
    Name_Text[2]->setText(text.at(3));
    Name_Text[3]->setText(text.at(4));
}



/*创建工具栏----------------------------------------------------------------------------------------------------------*/
void ModuleWindow::Creat_ToolBar()
{
        ToolBar =  new QToolBar(this);
        ToolBar->setOrientation( Qt::Vertical);
        ToolBar->setGeometry(370,0,20,90);
        ToolBar->setStyleSheet("QToolBar{border-style:outset}");
        ToolBar->setIconSize(QSize(20,20));

        RemoveAction     = new QAction(QIcon(":/image/delete.png"), tr("Remove this radio module from the list"), this);
        ToolBar->addAction(RemoveAction);

        DiscoverAction   = new QAction(QIcon(":/image/find.png"), tr("Discover radio nodes in the same network"), this);
        ToolBar->addAction(DiscoverAction);

        HideAction       = new QAction(QIcon(":/image/expand.png"), tr("Hdie the remote notes"), this);
        ToolBar->addAction(HideAction);

        connect(RemoveAction,  &QAction::triggered, this, &ModuleWindow::ModuleWindow_Close);
}




/*创建布局管理--------------------------------------------------------------------------------------------------------*/
void ModuleWindow::Creat_Layout()
{
        HboxLayout =  new QHBoxLayout(this);
        HboxLayout->addWidget(Label);
        HboxLayout->addWidget(GroupBox);
        HboxLayout->addWidget(ToolBar);
        HboxLayout->setStretch(1, 10);

        this->setMinimumHeight(100);
        this->setMaximumHeight(100);
        this->resize(350, 100);
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        this->setCursor(QCursor(Qt::PointingHandCursor));
}



/*窗体部件信息设置-----------------------------------------------------------------------------------------------------*/
void ModuleWindow::ModuleInfo_Set()
{
    if (Text_Content[0] == "DM")
    {
      Label->setPixmap(QPixmap(":/image/xbee_digimesh_64.png"));
    }
    else
    {
      Label->setPixmap(QPixmap(":/image/xbee_digipoint_64.png"));
    }

    Name_Text[0]->setText(Text_Content[1]);
    Name_Text[1]->setText(Text_Content[2]);
    Name_Text[2]->setText(Text_Content[3]);
    Name_Text[3]->setText(Text_Content[4]);
}



/*窗口关闭------------------------------------------------------------------------------------------------------------*/
void ModuleWindow::ModuleWindow_Close()
{
    emit this->Signal_ModuleWinClose(Name_Text[2]->text());

    close();
}



/*绘图事件重写---------------------------------------------------------------------------------------------------------*/
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





/*鼠标进入事件重写---------------------------------------------------------------------------------------------------*/
void ModuleWindow::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    PaintFlag = 1;
    QWidget::repaint();
}





/*鼠标退出事件重写--------------------------------------------------------------------------------------------------*/
void ModuleWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    PaintFlag = 0;
    QWidget::repaint();
}



/*鼠标拖拽事件重写-------------------------------------------------------------------------------------------------*/
void ModuleWindow::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
