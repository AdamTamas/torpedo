#include "tcpServer.h"
#include "tcpSocket.h"
#include <QTextStream>
#include <QDebug>

tcpServer::tcpServer(QObject *parent) : QTcpServer(parent)
{
    qDebug() << "Server init...";
}

tcpServer::~tcpServer()
{
    qDebug() << "Server stopped...";
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
        T << "data\nServer\n" << _data.areaSize <<"\n"
          << _data.shipNumForSizes[0] << "\n"
          << _data.shipNumForSizes[1] << "\n"
          << _data.shipNumForSizes[2] << "\n"
          << _data.shipNumForSizes[3] << "\n";
        i->flush();
    }

    connect(socket, &tcpSocket::AReadyRead, [&](tcpSocket *S)
    {
        qDebug() << "readyRead";
        QTextStream T(S);
        auto text = T.readAll();
        qDebug() << "read:" << text;

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


void tcpServer::getData(NewGameData data){
    _data = data;
    qDebug() << "Server got the following new game data:\nareaSize:"
             << data.areaSize <<"\nshipNumbers"
             << data.shipNumForSizes[0] << " "
             << data.shipNumForSizes[1] << " "
             << data.shipNumForSizes[2] << " "
             << data.shipNumForSizes[3] << " ";
}
