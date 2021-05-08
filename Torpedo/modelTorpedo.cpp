#include "modelTorpedo.h"
#include <stdlib.h>
#include "playerCPU.h"
#include "playerOnline.h"

modelTorpedo::modelTorpedo()
{
    areaSize = 8;
    _shipNum = 4;
    NewGameData d;
    d.areaSize = areaSize;
    for(int i = 0; i < _shipNum; i++)
    {
        d.shipNumForSizes[i] = 1;
    }
    d.online = false;
    playerOne = new playerBase(d);
    playerTwo = new playerCPU(d);
    connect(&cModel, SIGNAL(dataRecieved(NewGameData)), this, SLOT(connection_dataRecieved(NewGameData)));
    connect(&cModel, SIGNAL(stepRecieved(Coordinate)), this, SLOT(connection_stepRecieved(Coordinate)));
    connect(&cModel, SIGNAL(shotResponseRecieved(int)), this, SLOT(connection_shotResponseRecieved(int)));
    connect(&cModel, SIGNAL(readyRecieved()), this, SLOT(connection_readyRecieved()));
}

modelTorpedo::~modelTorpedo()
{
}

void modelTorpedo::newGame()
{
    playerOne->resetShips();
    playerTwo->resetShips();
    playerOne->randomTable();
    playerTwo->randomTable();
}

void modelTorpedo::newGameData(NewGameData data)
{
    areaSize = data.areaSize;
    _shipNum = 0;
    for(int i = 0; i < 4; i++)
    {
        _shipNum+= data.shipNumForSizes[i];
    }
    if(data.online){
        _online = true;
        _myTurn = true;
        playerTwo = new playerOnline(data);
        playerOne->newField(data);
        playerTwo->newField(data);
        if(!_server.startServer(3333)){
            qDebug() << "ERROR:" << _server.errorString();
            return;
        }else{
            qDebug() << "Server connected to port 3333";
        }
        qDebug() << "Sending data to server";
        _server.getData(data);
    }else{
        _online = false;
        playerTwo = new playerCPU(data);
        playerOne->newField(data);
        playerTwo->newField(data);
    }
    emit needNewGraphics();
}

Area modelTorpedo::getField(Coordinate c) const
{
    return playerOne->getField(c);
}

Area modelTorpedo::getEnemyField(Coordinate c) const
{
    return playerTwo->getField(c);
}

Ship modelTorpedo::getShipByID(int ID)  const
{
    return playerOne->getShipByID(ID);
}

Ship modelTorpedo::getEnemyShipByID(int ID)  const
{
    return playerTwo->getShipByID(ID);
}

void modelTorpedo::stepGame(Coordinate c)
{
    (_online) ? stepOnline(c) : stepOffline(c);
}

void modelTorpedo::stepOffline(Coordinate c){
    if(!playerTwo->getField(c).isShot)
    {
        playerTwo->getShot(c);
        playerOne->shotResponse(playerTwo->getField(c).shipID);
        Coordinate tmp = playerTwo->makeShot();
        playerOne->getShot(tmp);
        playerTwo->shotResponse(playerOne->getField(tmp).shipID);
    }
    checkGame();
}

void modelTorpedo::stepOnline(Coordinate c){
    if(!playerTwo->getField(c).isShot && _myTurn)
    {
        cModel.sendStep(QString::number(c.x) + "\n" + QString::number(c.y));
        playerTwo->getShot(c);
        _myTurn = false;
    }
    checkGame();
}

void modelTorpedo::checkGame()
{
    bool player1won = true;
    for(int i = 1; i <= _shipNum && player1won; ++i) // ellenőrzések végrehajtása
    {
        if (playerTwo->getShipByID(i).hitPoint)
        {
            player1won = false;
        }
    }
    bool player2won = true;
    for(int i = 1; i <= _shipNum && player2won; ++i) // ellenőrzések végrehajtása
    {
        if (playerOne->getShipByID(i).hitPoint)
            player2won = false;
    }

    if (player1won) // ha a játékos
    {
        emit gameWon(1); // esemény kiváltása
        _myTurn = false;
    }
    else if (player2won) // ha az ellenfél győzött
    {
        emit gameWon(0); // esemény kiváltása
        _myTurn = false;
    }
}

//online játék kiegészítői

void modelTorpedo::connection_dataRecieved(NewGameData data){
    if(cModel.getNickName() != "Player1"){
        qDebug() << "Data:" << data.areaSize
             <<" "<< data.shipNumForSizes[0]
             <<" "<< data.shipNumForSizes[1]
             <<" "<< data.shipNumForSizes[2]
             <<" "<< data.shipNumForSizes[3];
        areaSize = data.areaSize;
        _shipNum = 0;
        for(int i = 0; i < 4; i++)
        {
            _shipNum+= data.shipNumForSizes[i];
        }
        prepareToOnlineGame(data);
        emit needNewGraphics();
        emit gotNewData();
    }
}

void modelTorpedo::connectToHost(QString hostname, quint16 port)
{
    cModel.abort();
    cModel.connectToHost(hostname, port);
}


void modelTorpedo::prepareToOnlineGame(NewGameData data)
{
    _online = true;
    playerTwo = new playerOnline(data);
    playerOne->newField(data);
    playerTwo->newField(data);
}

void modelTorpedo::connection_stepRecieved(Coordinate c){
    playerOne->getShot(c);
    emit needGraphicsUpdate();
    qDebug() << "Elküldött ID: " << playerOne->getField(c).shipID << "\n";
    cModel.sendShotResponse(QString::number(playerOne->getField(c).shipID));
    checkGame();
    _myTurn = true;
}


void modelTorpedo::connection_shotResponseRecieved(int hit){
    qDebug() << "Kapott ID: " << hit << "\n";
    playerTwo->shotResponse(hit);
    emit needGraphicsUpdate();
    checkGame();
}

void modelTorpedo::connection_readyRecieved()
{
    _myTurn = true;
}
