#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QTcpSocket *socket, QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void connectionResult(bool success);

private:
    QTcpSocket *clientSocket;
};

#endif // MYTHREAD_H
