#include "tcpSocket.h"
#include <time.h>

tcpSocket::tcpSocket(qintptr handle, QObject *parent)
    : QTcpSocket(parent)
{
    setSocketDescriptor(handle);
    connect(this, &tcpSocket::readyRead, [&]() {
       emit AReadyRead(this);
    });
    connect(this, &tcpSocket::stateChanged, [&](int S){
        emit AStateChanged(this, S);
    });
}

