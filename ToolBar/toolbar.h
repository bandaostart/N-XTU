#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    ToolBar(QToolBar *parent = 0);
    ~ToolBar();

private:
    void paintEvent(QPaintEvent *event) override;

};


#endif // TOOLBAR_H
