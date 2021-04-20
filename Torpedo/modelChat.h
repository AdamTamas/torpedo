#ifndef MODELCHAT_H
#define MODELCHAT_H

#include <QTcpSocket>
#include "basebuildingblocks.h"


class modelChat : public QObject
{
    Q_OBJECT
public:
    modelChat();
    void send(QString);
    void connectToHost(QString hostname, quint16 port);
    void setNickName(QString name);

signals:
    void msgRecieved(QString msg); // játékos győzelmének eseménye

private:
    QTcpSocket *mSocket;
    QString nickName;
};

#endif // MODELCHAT_H
