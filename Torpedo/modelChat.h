#ifndef MODELCHAT_H
#define MODELCHAT_H

#include <QTcpSocket>

//class QTcpSocket;

class modelChat : public QObject
{
    Q_OBJECT
public:
    modelChat();
    void send(QString);
    void connectToHost(QString hostname, quint16 port);

signals:
    void msgRecieved(QString msg); // játékos győzelmének eseménye

private:
    QTcpSocket *mSocket;
};

#endif // MODELCHAT_H
