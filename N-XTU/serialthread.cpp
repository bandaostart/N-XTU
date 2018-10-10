#include "serialthread.h"
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QDebug>



QT_USE_NAMESPACE

//构造函数初始化，调用基类构造函数对基类进行初始化，列表初始化
SerialThread::SerialThread(QObject *parent) : QThread(parent)
{
    threadquit = false;
}


SerialThread::~SerialThread()
{
    mutex.lock();
    threadquit = true;
    mutex.unlock();

    wait();
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
        if (isRunning())
        {
         quit();
        }

        return false;
    }
    else
    {
        if (!isRunning())
        {
            start();
        }

        return true;
    }
}



void SerialThread::SerialClose(void)
{
    QMutexLocker locker(&mutex);

    if (Serial_Port.isOpen())
    {
        Serial_Port.close();
    }
    msleep(10);

    threadquit = true;

    quit();
}





void SerialThread::SerialTxData(const unsigned char *tx_data, unsigned short tx_num)
{
    if (Serial_Port.isOpen())
    {
        mutex.lock();

        Tx_Num = tx_num;
        memcpy(Tx_Data, tx_data, Tx_Num);

        {
            QString str = "TX ";
            for (int i=0; i<Tx_Num; i++)
            {
                if(Tx_Data[i] < 16)
                {
                    str += "0";
                }
                str += QString::number(Tx_Data[i] & 0xFF, 16).toUpper();
                str += " ";
            }
            qDebug() << str;
        }

        Serial_Port.write((const char *)Tx_Data, Tx_Num);

        Serial_Port.waitForBytesWritten(3);

        mutex.unlock();
    }
}



void SerialThread::run()
{
    while (!threadquit)
    {
        if (Serial_Port.isOpen())
        {
            if (Serial_Port.bytesAvailable())
            {
                QByteArray    rx_data;
                unsigned char num = 0;

                while (num <= 20)
                {
                    num++;
                    msleep(1);
                    if(Serial_Port.bytesAvailable())
                    {
                        num = 0;
                        rx_data += Serial_Port.readAll();
                    }
                }

                Rx_Num  = 0;
                Rx_Num  = rx_data.length();
                memcpy(Rx_Data, rx_data.data(), Rx_Num);

                if (Rx_Num)
                {
                    QString str = "RX ";
                    for (int i=0; i<Rx_Num; i++)
                    {
                        if(Rx_Data[i] < 16)
                        {
                            str += "0";
                        }
                        str += QString::number(Rx_Data[i] & 0xFF, 16).toUpper();
                        str += " ";
                    }
                    qDebug() << str;

                    emit this->SerialRxData(m_Serial_Port_Settings.portName, Rx_Data, Rx_Num);
                }
            }
        }
    }
}








