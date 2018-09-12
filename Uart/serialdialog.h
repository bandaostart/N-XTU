#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QListWidgetItem>
#include <QList>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "serialdialog.h"


namespace Ui {
class SerialDialog;
}

struct SerialPortSettings {
    int parity          = QSerialPort::NoParity;
    int baud            = QSerialPort::Baud9600;
    int dataBits        = QSerialPort::Data8;
    int stopBits        = QSerialPort::OneStop;
    int responseTime    = 1000;
    int numberOfRetries = 3;
};


class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialDialog(QWidget *parent = 0);

    ~SerialDialog();


private:
    SerialPortSettings       Serial_Port_Settings;
    QList<QListWidgetItem *> PortListItem;

    void SerivalDiscover();


private slots:
    void on_SelectPort_Radio_clicked();

    void on_ProvidePort_Radio_clicked();

    void on_RefreshPort_Button_clicked();

    void on_Port_ListView_itemClicked(QListWidgetItem *item);

    void on_Port_LineEdit_textChanged(const QString &arg1);

private:
    Ui::SerialDialog *ui;
};

#endif // SERIALDIALOG_H
