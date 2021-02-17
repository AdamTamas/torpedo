#include "torpedomodel.h"
#include <stdlib.h>
#include "cpuplayer.h"

Torpedomodel::Torpedomodel()
{
    areaSize = 8;
    _shipNum = 4;
    playerOne = new baseplayer(areaSize, _shipNum);
    playerTwo = new cpuplayer(areaSize, _shipNum);
}

Torpedomodel::~Torpedomodel()
{
}

void Torpedomodel::newGame()
{
    playerOne->resetShips();
    playerTwo->resetShips();
    playerOne->randomTable();
    playerTwo->randomTable();
}

void Torpedomodel::newGameData(NewGameData data)
{
    areaSize = data.areaSize;
    _shipNum = 0;
    for(int i = 0; i < 4; i++)
    {
        _shipNum+= data.shipNumForSizes[i];
    }
    playerOne->newField(data);
    playerTwo->newField(data);
    needNewGraphics();
}

Area Torpedomodel::getField(Coordinate c) const
{
    return playerOne->getField(c);
}

Area Torpedomodel::getEnemyField(Coordinate c) const
{
    return playerTwo->getField(c);
}

Ship Torpedomodel::getShipByID(int ID)  const
{
    return playerOne->getShipByID(ID);
}

Ship Torpedomodel::getEnemyShipByID(int ID)  const
{
    return playerTwo->getShipByID(ID);
}

void Torpedomodel::stepGame(Coordinate c)
{
    if(!playerTwo->getField(c).isShot)
    {
        playerTwo->getShot(c);
        playerOne->getShot(playerTwo->makeShot());
    }
    checkGame();
}

void Torpedomodel::checkGame()
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
