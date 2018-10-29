#ifndef MODULEWINDOW_H
#define MODULEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QToolBar>
#include <QAction>
#include <QHBoxLayout>
#include <QPainter>
#include <QCursor>
#include <QMouseEvent>
#include <QGroupBox>
#include <QDebug>



class ModuleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleWindow(QVector<QString> &text, QWidget *parent = 0);
    ~ModuleWindow();
    void         ModuleInfo_Set();
    void         ModuleInfo_Clear();


signals:
   void          Signal_ModuleWinClose(const QString &portname);
   void          Signal_MousePress(const QString &portname, const QString &moduletype);


private slots:
   void          ModuleWindow_Close();

private:
    void         Creat_MainDisArea(QVector<QString> &text);
    void         Creat_ToolBar();
    void         Creat_Layout();

    void paintEvent(QPaintEvent *event)         override;
    void mouseMoveEvent(QMouseEvent *event)     override;
    void enterEvent(QEvent *event)              override;
    void leaveEvent(QEvent *event)              override;
    void mousePressEvent(QMouseEvent *event)    override;

private:
    QLabel       *Label;
    QToolBar     *ToolBar;
    QAction      *RemoveAction;
    QAction      *DiscoverAction;
    QAction      *HideAction;
    QHBoxLayout  *HboxLayout;

    enum {NumParaRow = 4};
    QGroupBox    *GroupBox;
    QLabel       *Name[NumParaRow];
    QLabel       *Name_Text[NumParaRow];
    int          PaintFlag;

public:
    QString      Text_Content[NumParaRow+1];
    QString      Node_Type;

    double       Ammeter_Data;
    QString      Ammeter_Text;


};

#endif // MODULEWINDOW_H
