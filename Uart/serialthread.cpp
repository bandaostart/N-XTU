#include "serialthread.h"
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QDebug>



QT_USE_NAMESPACE

//构造函数初始化，调用基类构造函数对基类进行初始化，列表初始化
SerialTxThread::SerialTxThread(QObject *parent) : QThread(parent)
{
    ThreadStatus = true;
    Port_Status   = false;
}


SerialTxThread::~SerialTxThread()
{
    mutex.lock();

    ThreadStatus = false;
    if (Port_Status)
    {
        Serial_Port.close();
        Port_Status = false;
    }

    cond.wakeOne();
    mutex.unlock();

    wait();
}



//串口配置启动处理函数
bool SerialTxThread::SerialOpen(const SerialPortSettings &serail_port_settings)
{
    QMutexLocker locker(&mutex);

    if (Port_Status)
    {
        Serial_Port.close();
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
        Port_Status = false;
        if (isRunning())
        {
            quit();
        }

        return false;
    }
    else
    {
        Port_Status = true;
        if (!isRunning())
        {
            start();
        }

        return true;
    }
}



void SerialTxThread::SerialRequestData(QString &request_data)
{
    if (ThreadStatus && Port_Status)
    {
        mutex.lock();

        Request_Data = request_data.toLocal8Bit();
        cond.wakeOne();

        mutex.unlock();
    }
}




void SerialTxThread::run()
{
    while (ThreadStatus && Port_Status)
    {
        mutex.lock();
        cond.wait(&mutex);

        Serial_Port.write(Request_Data);
        Serial_Port.waitForBytesWritten(3);

        mutex.unlock();
    }
}







