#include "rightwindow.h"




RightWindow::RightWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //创建工具栏
    Tool_Bar   = new QToolBar(this);
    Tool_Bar->setMovable(false);
    Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");


    Device_Pixmap =  new QLabel(this);
    Device_Pixmap->setPixmap(QPixmap(":/image/console.png"));
    Tool_Bar->addWidget(Device_Pixmap);


    Device_Text = new QLabel("-Radio Modules Test", this);
    Tool_Bar->addWidget(Device_Text);
    addToolBar(Tool_Bar);


    //添加consol window
    Console_Window =  new ConsoleWindow(this);

    //添加 updata window
    Updata_Window  = new UpdataWindow(this);

    //定义分割器
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(Console_Window);
    splitter->addWidget(Updata_Window);
    splitter->setChildrenCollapsible(false);                                           //设置是否最小宽度高度限定
    splitter->setStretchFactor(1, 1);                                                  //设置拉伸:第一参数是 序号  ；第二个参数 大于1支持拉伸
    splitter->setHandleWidth(6);                                                       //设置宽度
    splitter->setStyleSheet("QSplitter::handle { background-color:rgb(215,215,215)}"); //设置颜色
    splitter->showMaximized();

    this->setCentralWidget(splitter);
    Updata_Window->hide();
    Console_Window->show();
}




RightWindow::~RightWindow()
{
}


//窗体选择
void RightWindow::Window_Choose(unsigned char num)
{
    switch (num)
    {
        case 0:
            Device_Pixmap->setPixmap(QPixmap(":/image/console.png"));
            Device_Text->setText("-Radio Modules Test");

            Updata_Window->hide();
            Console_Window->show();

        break;


        case 1:

            Device_Pixmap->setPixmap(QPixmap(":/image/gear.png"));
            Device_Text->setText("-Download the Radio Firmware");

            Console_Window->hide();
            Updata_Window->show();
        break;
    }
}











