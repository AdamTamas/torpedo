#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class AModelChat;

class ATcpServer : public QTcpServer
{
public:
    ATcpServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
protected:
    void incomingConnection(qintptr handle);
private :
    QList<AModelChat * > mSockets;
};

#endif // TCPSERVER_H
