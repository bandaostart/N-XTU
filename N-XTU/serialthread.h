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


class  SerialThread :  public QThread
{
    Q_OBJECT

public:
    explicit SerialThread(QObject *parent = nullptr);
    ~SerialThread();

    bool SerialOpen(const SerialPortSettings &serail_port_settings);
    void SerialClose(void);

    void SerialTxData(const unsigned char *tx_data, unsigned short tx_num);
    void run() Q_DECL_OVERRIDE;


signals:
    void SerialRxData(const QString &portname,  unsigned char *rx_data, unsigned short rx_num);
    void Communication_Text(const QString &portname, const QString &str);


private:
    QSerialPort        Serial_Port;
    SerialPortSettings m_Serial_Port_Settings;
    unsigned char      Tx_Data[512];
    qint64             Tx_Num;
    unsigned char      Rx_Data[512];
    qint64             Rx_Num;

private:
    QMutex             mutex;
    QWaitCondition     cond;
    bool               threadquit;
};



#endif // SERIALTHREAD_H
