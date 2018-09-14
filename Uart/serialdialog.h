#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "serialthread.h"


namespace Ui {
class SerialDialog;
}



class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialDialog(QWidget *parent = 0);

    ~SerialDialog();

    void SerivalDiscover();

private:
    SerialPortSettings              Serial_Port_Settings;
    QList<QListWidgetItem *>        PortListItem;
    QMap<QString, SerialThread *>   Serial_Port_Map;



private slots:
    void on_SelectPort_Radio_clicked();

    void on_ProvidePort_Radio_clicked();

    void on_RefreshPort_Button_clicked();

    void on_Port_ListView_itemClicked(QListWidgetItem *item);

    void on_Port_LineEdit_textChanged(const QString &arg1);

    void on_Finish_Button_clicked();

    void on_SetDefault_Button_clicked();

    void on_Cancel_Button_clicked();

private:
    Ui::SerialDialog *ui;
};

#endif // SERIALDIALOG_H





