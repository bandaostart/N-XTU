#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

struct SerialPortSettings {
    QString portName;
    int     parity          = QSerialPort::NoParity;
    int     baud            = QSerialPort::Baud9600;
    int     dataBits        = QSerialPort::Data8;
    int     stopBits        = QSerialPort::OneStop;
    int     flowCtrl        = QSerialPort::NoFlowControl;
    int     responseTime    = 1000;
    int     numberOfRetries = 3;
};


class  SerialTxThread :  public QThread
{
    Q_OBJECT

public:
    explicit SerialTxThread(QObject *parent = nullptr);
    ~SerialTxThread();

    bool SerialOpen(const SerialPortSettings &serail_port_settings);
    void SerialRequestData(QString &request_data);
    void run() Q_DECL_OVERRIDE;


private:
    bool               Port_Status;
    QSerialPort        Serial_Port;
    SerialPortSettings m_Serial_Port_Settings;
    QByteArray         Request_Data;

private:
    QMutex         mutex;
    QWaitCondition cond;
    bool           ThreadStatus;

};



#endif // SERIALTHREAD_H
