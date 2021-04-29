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
            emit msgRecieved(from + ":" + text);
        }

        if(messengeType == "step"){
            auto from = T.readLine();
            auto x = T.readLine();
            auto y = T.readLine();
            qDebug() << "client got:" << messengeType + " " + x + " " + y + " from:" + from;
            if(from != nickName){
                Coordinate coordinate = {x.toInt(),y.toInt()};
                emit stepRecieved(coordinate);
            }
        }

        if(messengeType == "response"){
            auto from = T.readLine();
            auto ID = T.readLine();
            qDebug() << "client got:" << messengeType + ": " + ID + " from:" + from;
            if(from != nickName){
                emit shotResponseRecieved(ID.toInt());
            }
        }

        if(messengeType == "ready"){
            auto from = T.readLine();
            qDebug() << "client got:" << messengeType + " from:" + from;
            if(from != nickName){
                emit readyRecieved();
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
            emit dataRecieved(data);
        }
    });
}

void modelConnection::sendMessenge(QString S){
    QTextStream T(mSocket);
    T << "chat\n" << nickName << "\n" << S;
    mSocket->flush();
}

void modelConnection::sendStep(QString S){
    QTextStream T(mSocket);
    T << "step\n" << nickName << "\n" << S;
    mSocket->flush();
}

void modelConnection::sendShotResponse(QString S){
    QTextStream T(mSocket);
    T << "response\n" << nickName << "\n" << S;
    mSocket->flush();
}

void modelConnection::sendReady(){
    QTextStream T(mSocket);
    T << "ready\n" << nickName;
    mSocket->flush();
};

void modelConnection::connectToHost(QString hostname, quint16 port){
    mSocket->connectToHost(hostname, port);
}

void modelConnection::setNickName(QString name){
    nickName = name;
}

QString modelConnection::getNickName(){
    return nickName;
}

QTcpSocket* modelConnection::getSocket() const{
    return mSocket;
}
void modelConnection::setSocket(QTcpSocket* S){
    mSocket = S;
}


void modelConnection::abort()
{
    mSocket->abort();
}
