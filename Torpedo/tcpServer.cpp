#include "tcpServer.h"
#include "modelChat.h"
#include <QTextStream>
#include <QDebug>

ATcpServer::ATcpServer(QObject *parent) : QTcpServer(parent)
{
}

bool ATcpServer::startServer(quint16 port){
    return listen(QHostAddress::Any, port);
}

void ATcpServer::incomingConnection(qintptr handle)
{
    auto socket = new AModelChat(handle, this);
    mSockets << socket;
    connect(socket, &AModelChat::AReadyRead, [&](AModelChat *S)
    {
        qDebug() << "readyRead";
        QTextStream T(S);
        auto text = T.readAll();

        for(auto i : mSockets){
            QTextStream K (i);
            K << text;
            i->flush();
        }
    });

    connect(socket, &AModelChat::AStateChanged, [&](AModelChat *S, int ST){
        qDebug() << "stateChanged";
        if(ST == QTcpSocket::UnconnectedState){
            qDebug() << "unconnected state";
            mSockets.removeOne(S);
            for(auto i :mSockets){
                QTextStream K(i);
                K << "Server: kliens "
                  << S->socketDescriptor()
                  << " Disconnected";
                i->flush();
            }
        }
    });
}
