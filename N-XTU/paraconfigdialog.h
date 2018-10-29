#ifndef PARACONFIGDIALOG_H
#define PARACONFIGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QPushButton>
#include <QFrame>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextBrowser>
#include <QPainter>
#include <QSignalMapper>
#include <QTimer>


#define  PER_MIN               0.0
#define  PER_MAX               100.0

#define  RSSI_MIN              -200
#define  RSSI_MAX              -1

#define  MA_MIN                0.000
#define  MA_MAX                200.000



class ParaConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParaConfigDialog(QWidget *parent = 0);
    ~ParaConfigDialog();
    void Read_Para(float *paradatamin, float *paradatamax, int num);

signals:
    void Signal_Para_ToManWin(const float *paradatamin, const float *paradatamax, int num);

private:
    void Para_ReadFromExcel();
    void Creat_StatusDisArea();
    void Creat_MainDisArea();
    void Set_WidgetAttributes();
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;



private slots:
    void Apply_Deal();
    void Cancle_Deal();
    void Default_Deal();
    void Timer_Deal();
    void ParaCfg_Deal(int index);




private:
    enum {NumParaRow = 7};

    QFont           font;
    QFile           File;
    QTimer          Timer;


    QSignalMapper    *SignalMapper;
    QLabel           *TitlePixLabel;
    QLabel           *TitleTextLabel;
    QLabel           *StatusPixLable;
    QTextBrowser     *StatusTextBrowser;
    QFrame           *StatusLine;

    QLabel           *InfoLabel[NumParaRow];
    QLabel           *ParaLabel[NumParaRow];
    QLabel           *SegLabel[NumParaRow];
    QLabel           *DesLabel[NumParaRow];
    QLineEdit        *ParaTextMin[NumParaRow];
    QLineEdit        *ParaTextMax[NumParaRow];
    QFrame           *SpaceLine;
    QPushButton      *ApplyButton;
    QPushButton      *CancelButon;
    QPushButton      *DefaultButton;
    QDoubleValidator *douValidator[NumParaRow];

    float       ParaDataMin[NumParaRow];
    float       ParaDataMax[NumParaRow];

    bool        ParaDataFlag[NumParaRow];
};

#endif // PARACONFIGDIALOG_H
