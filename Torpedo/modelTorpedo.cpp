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
        playerTwo = new playerOnline(data);
        playerOne->newField(data);
        playerTwo->newField(data);
        if(!server.startServer(3333)){
            qDebug() << "ERROR:" << server.errorString();
            return;
        }else{
            qDebug() << "Server connected to port 3333";
        }
        qDebug() << "Sending data to server";
        server.getData(data);
    }else{
        playerTwo = new playerCPU(data);
        playerOne->newField(data);
        playerTwo->newField(data);
    }
    needNewGraphics();
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

void modelTorpedo::checkGame()
{
    bool player1won = true;
    for(int i = 1; i <= _shipNum; ++i) // ellenőrzések végrehajtása
    {
        if (playerTwo->getShipByID(i).hitPoint && player1won)
        {
            player1won = false;
        }
    }
    bool player2won = true;
    for(int i = 1; i <= _shipNum; ++i) // ellenőrzések végrehajtása
    {
        if (playerOne->getShipByID(i).hitPoint && player2won)
            player2won = false;
    }

    if (player1won) // ha a játékos
    {
        gameWon(1); // esemény kiváltása
    }
    else if (player2won) // ha az ellenfél győzött
    {
        gameWon(0); // esemény kiváltása
    }
}
