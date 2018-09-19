#include "rightwindow.h"




RightWindow::RightWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Tool_Bar   = new QToolBar(this);
    Tool_Bar->setMovable(false);
    Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");

    QLabel *Device_Pixmap =  new QLabel(this);
    Device_Pixmap->setPixmap(QPixmap(":/image/console.png"));
    Tool_Bar->addWidget(Device_Pixmap);

    QLabel *Device_Text = new QLabel("-", this);
    Tool_Bar->addWidget(Device_Text);
    addToolBar(Tool_Bar);
}



RightWindow::~RightWindow()
{
}


