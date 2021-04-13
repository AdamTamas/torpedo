#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class tcpSocket;

class tcpServer : public QTcpServer
{
public:
    tcpServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
protected:
    void incomingConnection(qintptr handle);
private :
    QList<tcpSocket * > mSockets;
};

#endif // TCPSERVER_H
