#ifndef MODELCHAT_H
#define MODELCHAT_H

#include <QTcpSocket>

class tcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    tcpSocket(qintptr handle, QObject *parent = nullptr);
signals:
    void AReadyRead(tcpSocket *);
    void AStateChanged(tcpSocket *, int);
};

#endif // MODELCHAT_H
