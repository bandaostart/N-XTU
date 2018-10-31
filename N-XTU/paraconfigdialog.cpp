#include "paraconfigdialog.h"

ParaConfigDialog::ParaConfigDialog(QWidget *parent) : QDialog(parent)
{

    //从配置文件中读取默认参数
    Para_ReadFromExcel();

    //创建状态显示区域
    Creat_StatusDisArea();

    //创建主显示区域
    Creat_MainDisArea();

    //设置窗体属性
    Set_WidgetAttributes();

}



ParaConfigDialog::~ParaConfigDialog()
{

}




/*默认参数读取----------------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Para_ReadFromExcel()
{
    QString file_name, file_path;
    QDir    Dir;


    file_path   = Dir.currentPath();
    file_name   = file_path+"/PARA.dbc";
    File.setFileName(file_name);

    if(!File.open(QIODevice::ReadOnly))
    {
        File.open(QIODevice::ReadWrite | QIODevice::Append);

        ParaDataMin[0] = 99.5;
        ParaDataMin[1] = -40;
        ParaDataMin[2] = 99.5;
        ParaDataMin[3] = -40;
        ParaDataMin[4] = 100.000;
        ParaDataMin[5] = 18.000;
        ParaDataMin[6] = 0.005;

        ParaDataMax[0] = 100.0;
        ParaDataMax[1] = -20;
        ParaDataMax[2] = 100.0;
        ParaDataMax[3] = -20;
        ParaDataMax[4] = 150.000;
        ParaDataMax[5] = 22.000;
        ParaDataMax[6] = 0.020;

        File.seek(0);
        for (int i=0; i<NumParaRow; i++)
        {
            File.write((const char *)&ParaDataMin[i], 4);
            File.write((const char *)&ParaDataMax[i], 4);
        }
        File.close();
    }
    else
    {
        File.seek(0);
        for (int i=0; i<NumParaRow; i++)
        {
            File.read((char *)&ParaDataMin[i], 4);
            File.read((char *)&ParaDataMax[i], 4);
        }
        File.close();
    }
}




/*创建状态显示区域------------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Creat_StatusDisArea()
{
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(80);
    font.setPointSize(12);

    /*状态显示部分布局*/
    TitlePixLabel = new QLabel(this);
    TitlePixLabel->setPixmap(QPixmap(":/image/tools_header_frames_generator.png"));
    TitlePixLabel->setGeometry(370, 0, 130, 80);

    TitleTextLabel = new QLabel(this);
    font.setBold(true);
    TitleTextLabel->setFont(font);
    TitleTextLabel->setText("Parameter Normal Reference Range Setting");
    TitleTextLabel->setGeometry(5, 5, 330, 22);

    StatusPixLable = new QLabel(this);
    StatusPixLable->setPixmap(QPixmap(":/image/error.png"));
    StatusPixLable->setGeometry(10, 32, 16, 16);
    StatusPixLable->hide();

    StatusTextBrowser = new QTextBrowser(this);
    StatusTextBrowser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");
    StatusTextBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    StatusTextBrowser->setText("This tool allows you to change configuration parameters. Just fill in the required files.");
    StatusTextBrowser->setGeometry(29, 31, 350, 31);

    StatusLine = new QFrame(this);
    StatusLine->setFrameShape(QFrame::HLine);
    StatusLine->setFrameShadow(QFrame::Sunken);
    StatusLine->setGeometry(0, 81, 500, 3);
 }






/*创建主显示区域--------------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Creat_MainDisArea()
{
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(80);
    font.setPointSize(9);


    /*参数设置部分布局*/
    for (int i=0; i<NumParaRow; i++)
    {
         InfoLabel[i] = new QLabel(this);
         InfoLabel[i] ->setPixmap(QPixmap(":/image/info.png"));
         InfoLabel[i] ->setGeometry(10, i*60+100, 16, 20);


         ParaLabel[i]    = new QLabel(this);
         font.setBold(true);
         ParaLabel[i]->setFont(font);
         ParaLabel[i]->setGeometry(30, i*60+100, 180, 20);
         ParaLabel[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

         ParaTextMin[i]  = new QLineEdit(this);
         ParaTextMin[i]->setGeometry(200, i*60+100, 120, 20);
         ParaTextMin[i]->setContextMenuPolicy(Qt::CustomContextMenu);
         ParaTextMin[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
         switch (i)
         {
            case 0:
            case 2:
            {
                douValidator[i] = new QDoubleValidator(PER_MIN, PER_MAX, 1, this);
                ParaTextMin[i]->setValidator(douValidator[i]);
                ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',1));

                break;
            }

            case 1:
            case 3:
            {
                douValidator[i] = new QDoubleValidator(RSSI_MIN, RSSI_MAX, 0, this);
                ParaTextMin[i]->setValidator(douValidator[i]);
                ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',0));

                break;
            }

            case 4:
            case 5:
            case 6:
            {
                douValidator[i] = new QDoubleValidator(MA_MIN, MA_MAX, 3, this);
                ParaTextMin[i]->setValidator(douValidator[i]);
                ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',3));

                break;
            }
         }



         SegLabel[i]     = new QLabel(this);
         SegLabel[i]->setFont(font);
         SegLabel[i]->setGeometry(320, i*60+100, 25, 20);
         SegLabel[i]->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
         SegLabel[i]->setText("~");

         ParaTextMax[i]  = new QLineEdit(this);
         ParaTextMax[i]->setGeometry(345, i*60+100, 120, 20);
         ParaTextMax[i]->setContextMenuPolicy(Qt::CustomContextMenu);
         ParaTextMax[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
         switch (i)
         {
            case 0:
            case 2:
            {
                ParaTextMax[i]->setValidator(douValidator[i]);
                ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',1));

                break;
            }

            case 1:
            case 3:
            {
                ParaTextMax[i]->setValidator(douValidator[i]);
                ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',0));

                break;
            }

            case 4:
            case 5:
            case 6:
            {
                ParaTextMax[i]->setValidator(douValidator[i]);
                ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',3));

                break;
            }
         }

         ParaDataFlag[i]            = false;

         DesLabel[i]     = new QLabel(this);
         font.setBold(false);
         DesLabel[i]->setFont(font);
         DesLabel[i]->setGeometry(470, i*60+100, 25, 20);
         DesLabel[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }

    ParaLabel[0]->setText("Transmitting PER Range:");
    ParaLabel[1]->setText("Transmitting RSSI Range:");
    ParaLabel[2]->setText("Receiving PER Range:");
    ParaLabel[3]->setText("Receiving RSSI Range:");
    ParaLabel[4]->setText("Transmitting Current Range:");
    ParaLabel[5]->setText("Receiving Current Range:");
    ParaLabel[6]->setText("Sleeping Current Range:");

    DesLabel[0]->setText("%");
    DesLabel[1]->setText("-");
    DesLabel[2]->setText("%");
    DesLabel[3]->setText("-");
    DesLabel[4]->setText("mA");
    DesLabel[5]->setText("mA");
    DesLabel[6]->setText("mA");

    SpaceLine   = new QFrame(this);
    SpaceLine->setFrameShape(QFrame::HLine);
    SpaceLine->setFrameShadow(QFrame::Sunken);
    SpaceLine->setGeometry(0, 520, 500, 3);

    DefaultButton   = new QPushButton(this);
    DefaultButton->setText("Default");
    DefaultButton->setGeometry(10, 550, 120, 30);
    DefaultButton->setFocusPolicy(Qt::NoFocus);
    ApplyButton     = new QPushButton(this);
    ApplyButton->setText("Apply");
    ApplyButton->setGeometry(230, 550, 120, 30);
    ApplyButton->setFocusPolicy(Qt::NoFocus);
    CancelButon     = new QPushButton(this);
    CancelButon->setText("Cancel");
    CancelButon->setGeometry(370, 550, 120, 30);
}



/*设置窗体属性-------------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Set_WidgetAttributes()
{
    SignalMapper = new QSignalMapper(this);

    for (int i=0; i<NumParaRow; i++)
    {
        connect(ParaTextMin[i], SIGNAL(textChanged(QString)), SignalMapper, SLOT(map()));
        connect(ParaTextMax[i], SIGNAL(textChanged(QString)), SignalMapper, SLOT(map()));

        SignalMapper->setMapping(ParaTextMin[i], i);
        SignalMapper->setMapping(ParaTextMax[i], i+NumParaRow);
    }
    connect(SignalMapper, SIGNAL(mapped(int)),this, SLOT(ParaCfg_Deal(int)));



    connect(DefaultButton, &QPushButton::clicked, this, &ParaConfigDialog::Default_Deal);
    connect(ApplyButton, &QPushButton::clicked, this, &ParaConfigDialog::Apply_Deal);
    connect(CancelButon, &QPushButton::clicked, this, &ParaConfigDialog::Cancle_Deal);


    connect(&Timer, SIGNAL(timeout()), this, SLOT(Timer_Deal()));



    this->setMinimumSize(500, 600);
    this->setWindowTitle("Parameter Normal Reference Range Setting");
    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    this->setWindowModality(Qt::ApplicationModal);
}


/*参数读取----------------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Read_Para(float *paradatamin, float *paradatamax, int num)
{
    for (int i=0; i<num; i++)
    {
        paradatamin[i] = ParaDataMin[i];
        paradatamax[i] = ParaDataMax[i];
    }
}





/*定时器处理函数 槽函数-----------------------------------------------------------------------------------------*/
void ParaConfigDialog::Timer_Deal()
{
    for (int i=0; i<NumParaRow; i++)
    {
        switch (i)
        {
           case 0:
           case 2:
           {
               ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',1));
               ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',1));
               break;
           }

           case 1:
           case 3:
           {
               ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',0));
               ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',0));

               break;
           }

           case 4:
           case 5:
           case 6:
           {
               ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',3));
               ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',3));

               break;
           }
        }
    }

    File.open(QIODevice::ReadWrite | QIODevice::Append);
    File.seek(0);
    for (int i=0; i<NumParaRow; i++)
    {
        File.write((const char *)&ParaDataMin[i], 4);
        File.write((const char *)&ParaDataMax[i], 4);
    }
    File.close();

    Timer.stop();
}



/*参数更改应用 槽函数-------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Apply_Deal()
{
    Timer.start(100);

    for (int i=0; i<NumParaRow; i++)
    {
         ParaDataMin[i] = ParaTextMin[i]->text().toDouble();
         ParaDataMax[i] = ParaTextMax[i]->text().toDouble();
    }

    for (int i=0; i<NumParaRow; i++)
    {
        ParaDataFlag[i] = true;
        ParaTextMax[i]->setText("");
        ParaTextMin[i]->setText("");
    }
    this->update();
    //QDialog::accept();
}


/*恢复默认参数  槽函数------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Default_Deal()
{
    Timer.start(100);

    ParaDataMin[0] = 99.5;
    ParaDataMin[1] = -40;
    ParaDataMin[2] = 99.5;
    ParaDataMin[3] = -40;
    ParaDataMin[4] = 100.000;
    ParaDataMin[5] = 18.000;
    ParaDataMin[6] = 0.005;

    ParaDataMax[0] = 100.0;
    ParaDataMax[1] = -20;
    ParaDataMax[2] = 100.0;
    ParaDataMax[3] = -20;
    ParaDataMax[4] = 150.000;
    ParaDataMax[5] = 22.000;
    ParaDataMax[6] = 0.020;

    for (int i=0; i<NumParaRow; i++)
    {
        ParaDataFlag[i] = true;
        ParaTextMax[i]->setText("");
        ParaTextMin[i]->setText("");
    }
    this->update();
}



/*取消 槽函数--------------------------------------------------------------------------------------------------*/
void ParaConfigDialog::Cancle_Deal()
{
    QDialog::close();
}








/*参数设置处理 槽函数------------------------------------------------------------------------------------------*/
void ParaConfigDialog::ParaCfg_Deal(int index)
{
    int   i = 0;

    switch (index)
    {
        //PER_MIN
        case 0:
        case 2:
        {
            if (ParaTextMin[index]->text() == "")
            {
               ParaDataFlag[index] = true;
            }
            else
            {
                ParaDataMin[index] = ParaTextMin[index]->text().toDouble();
                if ((ParaDataMin[index] > PER_MAX) || (ParaDataMin[index] <PER_MIN) || (ParaDataMin[index] > ParaDataMax[index]))
                {
                    ParaDataFlag[index] = true;
                }
                else
                {
                    ParaDataFlag[index] = false;
                }
            }

            break;
        }

        //RSSI_MIN
        case 1:
        case 3:
        {
            if (ParaTextMin[index]->text() == "")
            {
               ParaDataFlag[index] = true;
            }
            else
            {
                ParaDataMin[index] = ParaTextMin[index]->text().toDouble();
                if ((ParaDataMin[index] > RSSI_MAX) || (ParaDataMin[index] <RSSI_MIN) || (ParaDataMin[index] > ParaDataMax[index]))
                {
                    ParaDataFlag[index] = true;
                }
                else
                {
                    ParaDataFlag[index] = false;
                }
            }

            break;
        }

        //MA_MIN
        case 4:
        case 5:
        case 6:
        {
            if (ParaTextMin[index]->text() == "")
            {
               ParaDataFlag[index] = true;
            }
            else
            {
                ParaDataMin[index] = ParaTextMin[index]->text().toDouble();
                if ((ParaDataMin[index] > MA_MAX) || (ParaDataMin[index] <MA_MIN) || (ParaDataMin[index] > ParaDataMax[index]))
                {
                    ParaDataFlag[index] = true;
                }
                else
                {
                    ParaDataFlag[index] = false;
                }
            }

            break;
        }



        //PER_MAX
        case 7:
        case 9:
        {
            if (ParaTextMax[index-NumParaRow]->text() == "")
            {
               ParaDataFlag[index-NumParaRow] = true;
            }
            else
            {
                ParaDataMax[index-NumParaRow] = ParaTextMax[index-NumParaRow]->text().toDouble();
                if ((ParaDataMax[index-NumParaRow] > PER_MAX) || (ParaDataMax[index-NumParaRow] <PER_MIN) || (ParaDataMin[index-NumParaRow] > ParaDataMax[index-NumParaRow]))
                {
                    ParaDataFlag[index-NumParaRow] = true;
                }
                else
                {
                    ParaDataFlag[index-NumParaRow] = false;
                }
            }
            break;
        }

        //RSSI_MAX
        case 8:
        case 10:
        {
            if (ParaTextMax[index-NumParaRow]->text() == "")
            {
               ParaDataFlag[index-NumParaRow] = true;
            }
            else
            {
                ParaDataMax[index-NumParaRow] = ParaTextMax[index-NumParaRow]->text().toDouble();
                if ((ParaDataMax[index-NumParaRow] > RSSI_MAX) || (ParaDataMax[index-NumParaRow] <RSSI_MIN) || (ParaDataMin[index-NumParaRow] > ParaDataMax[index-NumParaRow]))
                {
                    ParaDataFlag[index-NumParaRow] = true;
                }
                else
                {
                    ParaDataFlag[index-NumParaRow] = false;
                }
            }

            break;
        }

        //MA_MAX
        case 11:
        case 12:
        case 13:
        {
            if (ParaTextMax[index-NumParaRow]->text() == "")
            {
               ParaDataFlag[index-NumParaRow] = true;
            }
            else
            {
                ParaDataMax[index-NumParaRow] = ParaTextMax[index-NumParaRow]->text().toDouble();
                if ((ParaDataMax[index-NumParaRow] > MA_MAX) || (ParaDataMax[index-NumParaRow] <MA_MIN) || (ParaDataMin[index-NumParaRow] > ParaDataMax[index-NumParaRow]))
                {
                    ParaDataFlag[index-NumParaRow] = true;
                }
                else
                {
                    ParaDataFlag[index-NumParaRow] = false;
                }
            }

            break;
        }
    }


    for (i=0; i<NumParaRow; i++)
    {
        if (ParaDataFlag[i])
        {
            break;
        }
    }

    if (i >= NumParaRow)
    {
        ApplyButton->setEnabled(true);
        StatusPixLable->hide();
        StatusTextBrowser->setText("This tool allows you to change configuration parameters. Just fill in the required files.");
    }
    else
    {
        ApplyButton->setEnabled(false);
        StatusPixLable->show();
        StatusTextBrowser->setText("One or more Parameters are not correctly configured!");
    }

    this->update();
}


void ParaConfigDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    Para_ReadFromExcel();

    emit this->Signal_Para_ToManWin(ParaDataMin, ParaDataMax, NumParaRow);
    for (int i=0; i<NumParaRow; i++)
    {
        switch (i)
        {
           case 0:
           case 2:
           {
               ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',1));
               ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',1));
               break;
           }

           case 1:
           case 3:
           {
               ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',0));
               ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',0));

               break;
           }

           case 4:
           case 5:
           case 6:
           {
               ParaTextMin[i]->setText(QString("%1").arg(ParaDataMin[i], 0, 'f',3));
               ParaTextMax[i]->setText(QString("%1").arg(ParaDataMax[i], 0, 'f',3));

               break;
           }
        }
    }
}



void ParaConfigDialog::paintEvent(QPaintEvent *event)
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
    for (int i=0; i<NumParaRow; i++)
    {
        painter.drawRect(InfoLabel[i]->x()-3, InfoLabel[i]->y()-5, 485, 30);
    }


    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(252,159,159));

    brush.setColor(QColor(252,159,159));
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);
    for (int i=0; i<NumParaRow; i++)
    {
        if (ParaDataFlag[i])
        {
            painter.drawRect(InfoLabel[i]->x()-3, InfoLabel[i]->y()-5, 485, 30);
        }
    }
}

















