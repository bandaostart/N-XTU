#include "serialthread.h"
#include <QtSerialPort/QSerialPort>
#include <QTime>



QT_USE_NAMESPACE

//构造函数初始化，调用基类构造函数对基类进行初始化，列表初始化
SerialTxThread::SerialTxThread(QObject *parent) : QThread(parent)
{

}


SerialTxThread::~SerialTxThread()
{
    mutex.lock();

    quit = true;
    cond.wakeOne();

    mutex.unlock();

    wait();
}




//串口配置启动处理函数
void SerialTxThread::transaction(const SerialPortSettings serail_port_settings)
{
    QMutexLocker locker(&mutex);

    m_Serial_Port_Settings.parity          = serail_port_settings.parity;
    m_Serial_Port_Settings.baud            = serail_port_settings.baud;
    m_Serial_Port_Settings.dataBits        = serail_port_settings.dataBits;
    m_Serial_Port_Settings.stopBits        = serail_port_settings.stopBits;
    m_Serial_Port_Settings.responseTime    = serail_port_settings.responseTime;
    m_Serial_Port_Settings.numberOfRetries = serail_port_settings.numberOfRetries;

    if (!isRunning())
    {
        start();
    }
    else
    {
        cond.wakeOne();
    }
}



void SerialTxThread::run()
{
//    bool currentPortNameChanged = false;

//    mutex.lock();

//    //! [4] //! [5]
//    QString currentPortName;
//    if (currentPortName != portName)
//    {
//        currentPortName = portName;
//        currentPortNameChanged = true;
//    }

//    int currentWaitTimeout = waitTimeout;
//    QString currentRequest = request;
//    mutex.unlock();

//    //! [5] //! [6]
//    QSerialPort serial;

}







