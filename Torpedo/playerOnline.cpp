
#include "playerOnline.h"

playerOnline::playerOnline(NewGameData newdata) : playerBase(newdata)
{
    initTable();
    _lastShot.x = 0;
    _lastShot.y = 0;
    socket = new QTcpSocket(this);
}

playerOnline::~playerOnline(){
    if(socket->state() == QTcpSocket::ConnectedState)
        socket->close();
};

void playerOnline::connect(){
    socket->connectToHost("localhost",4747);
    if(socket->waitForConnected(5000)){

    };
}

Coordinate playerOnline::makeShot()
{
    Coordinate c{0,0};
    //socket->read(c);
    _lastShot = c;
    return c;
}


void playerOnline::getShot(Coordinate c){
    char x[3];
    char y[3];
    itoa(c.x,x,10);
    itoa(c.y,y,10);
    socket->write(x);
    socket->write(y);
}

void playerOnline::shotResponse(bool hit)
{
    if(hit)
        _gameTable[_lastShot.x][_lastShot.y].shipID = -1;
}

