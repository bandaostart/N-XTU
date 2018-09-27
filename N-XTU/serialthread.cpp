#include "serialthread.h"
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QDebug>



QT_USE_NAMESPACE

//构造函数初始化，调用基类构造函数对基类进行初始化，列表初始化
SerialThread::SerialThread(QObject *parent) : QThread(parent)
{
    connect(&Serial_Port, &QSerialPort::readyRead, this, &SerialThread::SerialRxFlag);
}


SerialThread::~SerialThread()
{
    mutex.lock();

    if (Serial_Port.isOpen())
    {
        Serial_Port.close();
    }

    mutex.unlock();
}



//串口配置启动处理函数
bool SerialThread::SerialOpen(const SerialPortSettings &serail_port_settings)
{
    QMutexLocker locker(&mutex);

    if (Serial_Port.isOpen())
    {
        Serial_Port.close();

        msleep(10);
    }


    m_Serial_Port_Settings.portName        = serail_port_settings.portName;
    m_Serial_Port_Settings.parity          = serail_port_settings.parity;
    m_Serial_Port_Settings.baud            = serail_port_settings.baud;
    m_Serial_Port_Settings.dataBits        = serail_port_settings.dataBits;
    m_Serial_Port_Settings.stopBits        = serail_port_settings.stopBits;
    m_Serial_Port_Settings.flowCtrl        = serail_port_settings.flowCtrl;
    m_Serial_Port_Settings.responseTime    = serail_port_settings.responseTime;
    m_Serial_Port_Settings.numberOfRetries = serail_port_settings.numberOfRetries;

    Serial_Port.setPortName(m_Serial_Port_Settings.portName);
    Serial_Port.setBaudRate((QSerialPort::BaudRate)m_Serial_Port_Settings.baud);
    Serial_Port.setParity((QSerialPort::Parity)m_Serial_Port_Settings.parity);
    Serial_Port.setDataBits((QSerialPort::DataBits)m_Serial_Port_Settings.dataBits);
    Serial_Port.setStopBits((QSerialPort::StopBits)m_Serial_Port_Settings.stopBits);
    Serial_Port.setFlowControl((QSerialPort::FlowControl)m_Serial_Port_Settings.flowCtrl);


    if (!Serial_Port.open(QIODevice::ReadWrite))
    {
        return false;
    }
    else
    {
        return true;
    }
}



void SerialThread::SerialClose(void)
{
    QMutexLocker locker(&mutex);

    if (Serial_Port.isOpen())
    {
        Serial_Port.close();
        msleep(10);
    }
}





void SerialThread::SerialTxData(const unsigned char *tx_data, unsigned short tx_num)
{
    if (Serial_Port.isOpen())
    {
        mutex.lock();

        Tx_Num = tx_num;
        memcpy(Tx_Data, tx_data, Tx_Num);

        Serial_Port.write((const char *)Tx_Data, Tx_Num);

        Serial_Port.waitForBytesWritten(3);

        mutex.unlock();
    }
}



void SerialThread::run()
{
    while (1)
    {
    }
}



void SerialThread::SerialRxFlag()
{
    QByteArray rx_data;

    while (Serial_Port.waitForReadyRead(5))
    {
        rx_data += Serial_Port.readAll();
    }

    Rx_Num  = 0;
    Rx_Num  = rx_data.length();
    memcpy(Rx_Data, rx_data.data(), Rx_Num);

    if (Rx_Num)
    {
        emit this->SerialRxData(m_Serial_Port_Settings.portName, Rx_Data, Rx_Num);
    }
}







