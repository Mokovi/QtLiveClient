#include "mythread.h"



MyThread::MyThread(QTcpSocket *socket, QObject *parent)
    :QThread(parent)
    ,clientSocket(socket)
{

}

void MyThread::run()
{
    if(clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        emit connectionResult(true);
    }
    else {

        clientSocket->connectToHost("127.0.0.1", 13145);
        if(clientSocket->waitForConnected(3000))
        {
            emit connectionResult(true);
        }
        else
        {
            emit connectionResult(false);
        }
    }
}
