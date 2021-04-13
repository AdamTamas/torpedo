#include "modelChat.h"


modelChat::modelChat()
{
    mSocket = new QTcpSocket(this);
    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T;
        auto text = T.readAll();
        //_chatWidget->append(text);
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
