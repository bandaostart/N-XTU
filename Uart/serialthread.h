#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "serialdialog.h"



class  SerialTxThread :  public QThread
{
    Q_OBJECT

public:
    explicit SerialTxThread(QObject *parent = nullptr);
    ~SerialTxThread();

    void transaction(const SerialPortSettings serail_port_settings);
    void run() Q_DECL_OVERRIDE;

signals:
//    void response(const QString &s);
//    void error(const QString &s);
//    void timeout(const QString &s);

private:
    QMutex mutex;
    QWaitCondition cond;
    bool quit;

    SerialPortSettings m_Serial_Port_Settings;
};



#endif // SERIALTHREAD_H
