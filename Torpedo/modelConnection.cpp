#include "modelConnection.h"

#include <QDebug>

modelConnection::modelConnection()
{
    mSocket = new QTcpSocket(this);
    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        auto messengeType = T.readLine();

        if(messengeType == "chat"){
            auto from = T.readLine();
            auto text = T.readAll();
            qDebug() << "client got:" << messengeType + " " + text << " from:" << from;
            msgRecieved(from + text);
        }

        if(messengeType == "step"){
            auto from = T.readLine();
            auto x = T.readLine();
            auto y = T.readLine();
            qDebug() << "client got:" << messengeType + " " + x + " " + y + " from:" + from;
            if(from != nickName){
                Coordinate coordinate = {x.toInt(),y.toInt()};
                //stepRecieved(coordinate);
            }
        }

        if(messengeType == "data"){
            auto from = T.readLine();
            NewGameData data;
            data.areaSize = T.readLine().toInt();
            data.shipNumForSizes[0] = T.readLine().toInt();
            data.shipNumForSizes[1] = T.readLine().toInt();
            data.shipNumForSizes[2] = T.readLine().toInt();
            data.shipNumForSizes[3] = T.readLine().toInt();
            data.online = true;
            qDebug() << "client got:" << messengeType + " from:" + from;
            dataRecieved(data);
        }
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
