#include "modelChat.h"

#include <QDebug>

modelChat::modelChat()
{
    mSocket = new QTcpSocket(this);
    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        auto text = T.readAll();
        qDebug() << "client got:" << text << " from:" << mSocket;
        msgRecieved(text);
    });
}

void modelChat::send(QString S){
    QTextStream T(mSocket);
    T << S;
    mSocket->flush();
}

void modelChat::connectToHost(QString hostname, quint16 port){
    mSocket->connectToHost(hostname, port);
}
