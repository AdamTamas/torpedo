#include "modelChat.h"

#include <QDebug>

modelChat::modelChat()
{
    mSocket = new QTcpSocket(this);
    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        auto messengeType = T.readLine();
        auto from = T.readLine();
        auto text = T.readAll();
        qDebug() << "client got:" << messengeType + " " + text << " from:" << from;
        if(messengeType == "chat")
            msgRecieved(from + text);
    });

}

void modelChat::send(QString S){
    QTextStream T(mSocket);
    T << "chat\n" << nickName << ":\n" << S;
    mSocket->flush();
}

void modelChat::connectToHost(QString hostname, quint16 port){
    mSocket->connectToHost(hostname, port);
}

void modelChat::setNickName(QString name){
    nickName = name;
}
