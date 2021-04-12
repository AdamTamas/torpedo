#include "modelChat.h"
#include <time.h>

AModelChat::AModelChat(qintptr handle, QObject *parent)
    : QTcpSocket(parent)
{
    setSocketDescriptor(handle);
    connect(this, &AModelChat::readyRead, [&]() {
       emit AReadyRead(this);
    });
    connect(this, &AModelChat::stateChanged, [&](int S){
        emit AStateChanged(this, S);
    });
}

