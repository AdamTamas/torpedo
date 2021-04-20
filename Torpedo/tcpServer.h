#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "basebuildingblocks.h"

class tcpSocket;

class tcpServer : public QTcpServer
{
public:
    tcpServer(QObject *parent = nullptr);
    ~tcpServer();
    bool startServer(quint16 port);
    void getData(NewGameData data);
protected:
    void incomingConnection(qintptr handle);
private :
    QList<tcpSocket * > mSockets;
    NewGameData _data = {8,{1,1,1,1},true};
};

#endif // TCPSERVER_H
