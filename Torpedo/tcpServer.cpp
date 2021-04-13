#include "tcpServer.h"
#include "tcpSocket.h"
#include <QTextStream>
#include <QDebug>

tcpServer::tcpServer(QObject *parent) : QTcpServer(parent)
{
}

bool tcpServer::startServer(quint16 port){
    return listen(QHostAddress::Any, port);
}

void tcpServer::incomingConnection(qintptr handle)
{
    qDebug () << "Client connected with handle: " << handle;
    auto socket = new tcpSocket(handle, this);
    mSockets << socket;

    for(auto i : mSockets){
        QTextStream T(i);
        T << "Server: Connected:" << handle;
        i->flush();
    }

    connect(socket, &tcpSocket::AReadyRead, [&](tcpSocket *S)
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

    connect(socket, &tcpSocket::AStateChanged, [&](tcpSocket *S, int ST){
        qDebug() << "stateChanged with handle: " << S->socketDescriptor();
        if(ST == QTcpSocket::UnconnectedState){
            qDebug() << "unconnected state with handle: " << S->socketDescriptor();
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
