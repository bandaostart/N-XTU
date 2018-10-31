#include "updatawindow.h"


UpdataWindow::UpdataWindow(QWidget *parent) : QWidget(parent)

{
    QFile File;

    //字体设置
    Font.setBold(true);
    Font.setFamily(QString::fromUtf8("Arial"));
    Font.setWeight(80);

    //设置工具栏
    Top_Tool_Bar = new QToolBar(this);
    Top_Tool_Bar->setIconSize(QSize(48, 48));
    Top_Tool_Bar->setMovable(false);
    Top_Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");

    UpdataFw_Action = new QAction(QIcon(":/image/updatefw.png"), tr("Updata the Radio Firmware Library"), this);
    connect(UpdataFw_Action, &QAction::triggered, this, &UpdataWindow::DownlodFile);
    Top_Tool_Bar->addAction(UpdataFw_Action);



    //设置文件加载项
    Group_Box        = new QGroupBox(this);
    Group_Box_Layout = new QGridLayout(Group_Box);
    for (int i=0; i<NumFileLoad; i++)
    {
        FileLabel[i] = new QLabel(Group_Box);
        FileLabel[i]->setFont(Font);
        FileLabel[i]->setGeometry(0, i*30+5, 150, 25);
        FileLabel[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        Group_Box_Layout->addWidget(FileLabel[i], i, 0, 1, 1);

        FileText[i]  = new QLineEdit(Group_Box);
        FileText[i]->setGeometry(160, i*30+5, 250, 25);
        FileText[i]->setAlignment(Qt::AlignLeft);
        FileText[i]->setReadOnly(true);
        Group_Box_Layout->addWidget(FileText[i], i, 1, 1, 1);

        FileButton[i]  = new QPushButton(Group_Box);
        FileButton[i]->setIcon(QIcon(":/image/load_profile.png"));
        Group_Box_Layout->addWidget(FileButton[i], i, 2, 1, 1);

    }
    FileLabel[0]->setText("Main Code:");
    FileLabel[1]->setText("Test Code:");
    FileLabel[2]->setText("JFlash App:");

    connect(FileButton[0], &QPushButton::clicked, this, &UpdataWindow::MainCodeFileLoad);
    connect(FileButton[1], &QPushButton::clicked, this, &UpdataWindow::TestCodeFileLoad);
    connect(FileButton[2], &QPushButton::clicked, this, &UpdataWindow::JlinkAppFileLoad);

    TextEdit      = new QTextEdit(Group_Box);
    TextEdit->setReadOnly(true);
    Group_Box_Layout->addWidget(TextEdit, NumFileLoad, 0, 1, 3);



    //设置布局
    Vbox_Layout      = new QVBoxLayout(this);
    Vbox_Layout->addWidget(Top_Tool_Bar);
    Vbox_Layout->addWidget(Group_Box);


    //文件路径恢复
    File.setFileName("Log.txt");
    if(File.open(QIODevice::ReadOnly))
    {
        File.seek(0);

        MainCodePath = File.readLine();
        MainCodePath.replace(QString("\n"), QString(""));
        MainCodeName = MainCodePath;
        FileText[0]->setText(MainCodeName);

        TestCodePath = File.readLine();
        TestCodePath.replace(QString("\n"), QString(""));
        TestCodeName = TestCodePath;
        FileText[1]->setText(TestCodeName);

        JLinkAppPath = File.readLine();
        JLinkAppPath.replace(QString("\n"), QString(""));
        JlinkAppName = QDir::fromNativeSeparators(JLinkAppPath);
        FileText[2]->setText(JlinkAppName);


        File.close();
    }
}

UpdataWindow::~UpdataWindow()
{

}





/*主程序文件加载-----------------------------------------------------------------------------*/
void UpdataWindow::MainCodeFileLoad()
{
    MainCodeName = QFileDialog::getOpenFileName(this , tr("Main Code"),MainCodeName, tr("Bin Files (*.bin)"));

    if (!MainCodeName.isEmpty())
    {
        FileText[0]->setText(MainCodeName);
        MainCodePath = MainCodeName;
    }
}


/*测试程序文件加载-----------------------------------------------------------------------------*/
void UpdataWindow::TestCodeFileLoad()
{
    TestCodeName = QFileDialog::getOpenFileName(this , tr("Test Code"),TestCodeName, tr("Bin Files (*.bin)"));

    if (!TestCodeName.isEmpty())
    {
        FileText[1]->setText(TestCodeName);
        TestCodePath = TestCodeName;
    }
}

/*Jlink APP加载-----------------------------------------------------------------------------*/
void UpdataWindow::JlinkAppFileLoad()
{
    JlinkAppName = QFileDialog::getOpenFileName(this , tr("JFlash App"),JlinkAppName, tr("Exe Files (*.exe)"));

    if (!JlinkAppName.isEmpty())
    {
        FileText[2]->setText(JlinkAppName);
        JLinkAppPath  = JlinkAppName;
        JLinkAppPath  =  QDir::toNativeSeparators(JLinkAppPath);
    }
}


/*下载程序-----------------------------------------------------------------------------*/
void UpdataWindow::DownlodFile()
{
    QString  str = "";
    bool     error_state = false;

    //清空列表
    TextEdit->clear();

    if (MainCodePath.isEmpty())
    {
        str = "\r\nNo \"Main Code\" Found                                                                   ";
        error_state = true;
    }

    if (TestCodePath.isEmpty())
    {
        str += "\r\nNo \"Test Code\" Found                                                                  ";
        error_state = true;
    }

    if (JLinkAppPath.isEmpty())
    {
        str += "\r\nNo \"Jlink App\" Found                                                                  ";
        error_state = true;
    }

    if (error_state)
    {
        QMessageBox::critical(NULL, "Error discovering device", str, QMessageBox::Ok);
    }
    else
    {
        QProcess    pro;
        QString     main_code_path, test_code_path, jlink_app_path;
        QFile       File;
        QString     Str;
        QByteArray  byte_array;
        char        *temp_buf;


        //烧写文件
        main_code_path   = "-open"+MainCodePath+",0x0000000";
        test_code_path   = "-open"+TestCodePath+",0x0032000";
        jlink_app_path   = JLinkAppPath;

        pro.execute(jlink_app_path, QStringList()
                           << "-jflashlogLog.txt"
                           << "-connect"       << "-unsecurechip"
                           << "-erasechip"     << "-erasesectors"
                           << main_code_path   << "-programverify"
                           << test_code_path   << "-programverify"
                           << "-startapp"
                           << "-disconnect"
                           << "-exit");


        //显示烧写日志
        File.setFileName("Log.txt");
        if(File.open(QIODevice::ReadOnly))
        {
            File.seek(0);
            while (!File.atEnd())
            {
                Str = File.readLine();
                TextEdit->insertPlainText(Str);
                TextEdit->moveCursor(QTextCursor::End);
            }
            File.close();
        }

        if(File.open(QIODevice::ReadWrite | QIODevice::Append))
        {
            File.seek(0);

            byte_array = MainCodePath.toLatin1();
            temp_buf   = byte_array.data();
            File.write(temp_buf);
            File.write("\n");

            byte_array = TestCodePath.toLatin1();
            temp_buf   = byte_array.data();
            File.write(temp_buf);
            File.write("\n");

            byte_array = JLinkAppPath.toLatin1();
            temp_buf   = byte_array.data();
            File.write(temp_buf);
            File.write("\n");

            File.close();
        }
    }
}




/*窗口关闭事件重写----------------------------------------------------------------------------*/
void UpdataWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

//    QFile       File;
//    QByteArray  byte_array;
//    char        *temp_buf;

//    File.setFileName("Log.txt");
//    if(File.open(QIODevice::ReadWrite | QIODevice::Append))
//    {
//        File.seek(0);

//        byte_array = MainCodePath.toLatin1();
//        temp_buf   = byte_array.data();
//        File.write(temp_buf);
//        File.write("\r\n");

//        byte_array = TestCodePath.toLatin1();
//        temp_buf   = byte_array.data();
//        File.write(temp_buf);
//        File.write("\r\n");

//        byte_array = JLinkAppPath.toLatin1();
//        temp_buf   = byte_array.data();
//        File.write(temp_buf);
//        File.write("\r\n");

//        File.close();
//    }
}




/*窗体重绘事件--------------------------------------------------------------------------------*/
void UpdataWindow::paintEvent(QPaintEvent *event)
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

    painter.drawRect(Group_Box->x(), Group_Box->y(), Group_Box->width(), Group_Box->height());
}
