#include "leftwindow.h"

QT_USE_NAMESPACE

LeftWindow::LeftWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Tool_Bar   = new QToolBar(this);
    Tool_Bar->setMovable(false);

    QLabel *Device_Pixmap =  new QLabel(this);
    Device_Pixmap->setPixmap(QPixmap(":/image/devices.png"));
    Tool_Bar->addWidget(Device_Pixmap);

    QLabel *Device_Text = new QLabel("Radio Modules", this);
    Tool_Bar->addWidget(Device_Text);

    QWidget *Space = new QWidget(this);
    Space->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    Tool_Bar->addWidget(Space);

    Find_Action   = new QAction(QIcon(":/image/find_devices.png"), tr("Find radio modules"), this);
    Tool_Bar->addAction(Find_Action);

    Tool_Menu  = new QMenu(tr("Sort radio module list"), this);
    Tool_Menu->setIcon(QIcon(":/image/sort.png"));
    Tool_Menu->addAction("Sort by Name");
    Tool_Menu->addAction("Sort by Function");
    Tool_Menu->addAction("Sort by Port");
    Tool_Menu->addAction("Sort by MAC address");
    Tool_Bar->addAction(Tool_Menu->menuAction());

    Clear_Action = new QAction(QIcon(":/image/clear_devices.png"), tr("Clear radio module list"), this);
    Tool_Bar->addAction(Clear_Action);
    Tool_Bar->setStyleSheet("QToolBar{border-style:outset}");
    addToolBar(Tool_Bar);


    Find_Action->setEnabled(false);
    Tool_Menu->setDisabled(true);
    Clear_Action->setEnabled(false);



    Central_Widget = new QWidget(this);
    Vbox_Layout    = new QVBoxLayout(Central_Widget);

    Moduel_Widget  = new ModuleWindow(Central_Widget);
    Vbox_Layout->addWidget(Moduel_Widget);

    verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    Vbox_Layout->addItem(verticalSpacer);

    setCentralWidget(Central_Widget);
}

LeftWindow::~LeftWindow()
{

}
