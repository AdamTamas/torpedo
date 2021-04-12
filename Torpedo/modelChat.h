#ifndef MODELCHAT_H
#define MODELCHAT_H

#include <QTcpSocket>

class AModelChat : public QTcpSocket
{
    Q_OBJECT
public:
    AModelChat(qintptr handle, QObject *parent = nullptr);
signals:
    void AReadyRead(AModelChat *);
    void AStateChanged(AModelChat *, int);
};

#endif // MODELCHAT_H
