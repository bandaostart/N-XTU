#ifndef UPDATAWINDOW_H
#define UPDATAWINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QPen>
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QFont>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>



class UpdataWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UpdataWindow(QWidget *parent = 0);
    ~UpdataWindow();

private:
    QFont       Font;

    QToolBar    *Top_Tool_Bar;
    QAction     *UpdataFw_Action;

    enum{NumFileLoad = 3};
    QLabel      *FileLabel[NumFileLoad];
    QLineEdit   *FileText[NumFileLoad];
    QPushButton *FileButton[NumFileLoad];
    QTextEdit   *TextEdit;
    QGroupBox   *Group_Box;
    QGridLayout *Group_Box_Layout;

    QVBoxLayout *Vbox_Layout;


    QString     MainCodeName;
    QString     MainCodePath;
    QString     TestCodeName;
    QString     TestCodePath;
    QString     JlinkAppName;
    QString     JLinkAppPath;


private:
    void MainCodeFileLoad();
    void TestCodeFileLoad();
    void JlinkAppFileLoad();
    void DownlodFile();
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};

#endif // UPDATAWINDOW_H
