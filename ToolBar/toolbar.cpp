#include "toolbar.h"
#include <QPainter>
#include <QPen>
#include <QBrush>



ToolBar::ToolBar(QToolBar *parent) : QToolBar(parent)
{
    setFixedHeight(48);
}

ToolBar::~ToolBar()
{

}



void ToolBar::paintEvent(QPaintEvent *event	)
{
        Q_UNUSED(event);

        QBrush   brush;
        QPen     pen;
        QPainter painter(this);

        pen.setStyle(Qt::SolidLine);
        pen.setColor(QColor(0,144,216));

        brush.setColor(QColor(0,144,216));
        brush.setStyle(Qt::SolidPattern);

        painter.setPen(pen);
        painter.setBrush(brush);

        painter.drawRect(120, 0, this->width(), this->height());
}
