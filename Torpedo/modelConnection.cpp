#include "modelConnection.h"

#include <QDebug>

modelConnection::modelConnection()
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

void modelConnection::sendMessenge(QString S){
    QTextStream T(mSocket);
    T << "chat\n" << nickName << ":\n" << S;
    mSocket->flush();
}

void modelConnection::sendStep(QString S){
    QTextStream T(mSocket);
    T << "step\n" << nickName << ":\n" << S;
    mSocket->flush();
}

void modelConnection::connectToHost(QString hostname, quint16 port){
    mSocket->connectToHost(hostname, port);
}

void modelConnection::setNickName(QString name){
    nickName = name;
}

QTcpSocket* modelConnection::getSocket() const{
    return mSocket;
}
void modelConnection::setSocket(QTcpSocket* S){
    mSocket = S;
}
