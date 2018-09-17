#include "leftwindow.h"

LeftWindow::LeftWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Tool_Bar   = new QToolBar(this);



    QAction *Find_Action  = new QAction(QIcon(":/image/find_devices.png"), tr("Find radio modules"), this);

    Tool_Menu  = new QMenu(tr("Sort radio module list"), this);
    Tool_Menu->addAction("Sort by Name");
    Tool_Menu->addAction("Sort by Function");
    Tool_Menu->addAction("Sort by Port");
    Tool_Menu->addAction("Sort by MAC address");
    Tool_Bar->addAction(Tool_Menu->menuAction());

    QAction *Sort_Action  = new QAction(QIcon(":/image/sort.png"), tr("Find radio modules"), this);
    QAction *Clear_Action = new QAction(QIcon(":/image/clear_devices.png"), tr("Find radio modules"), this);
    Tool_Bar->addAction(Find_Action);
    Tool_Bar->addAction(Sort_Action);
    Tool_Bar->addAction(Clear_Action);

//    addToolBar(Qt::RightToolBarArea, Tool_Bar);
    addToolBar(Tool_Bar);
}

LeftWindow::~LeftWindow()
{

}
