#include "torpedomodel.h"
#include <stdlib.h>

Torpedomodel::Torpedomodel()
{
    areaSize = 8;
    _shipNum = 4;
    playerOne = baseplayer(areaSize, _shipNum);
    playerTwo = baseplayer(areaSize, _shipNum);
}

Torpedomodel::~Torpedomodel()
{
}

void Torpedomodel::newGame()
{
    playerOne.resetShips();
    playerTwo.resetShips();
    playerOne.randomTable();
    playerTwo.randomTable();
}

Area Torpedomodel::getField(int x, int y) const
{
    return playerOne.getField(x,y);
}

Area Torpedomodel::getEnemyField(int x, int y) const
{
    return playerTwo.getField(x,y);
}

Ship Torpedomodel::getShipByID(int ID)  const
{
    return playerOne.getShipByID(ID);
}

Ship Torpedomodel::getEnemyShipByID(int ID)  const
{
    return playerTwo.getShipByID(ID);
}

void Torpedomodel::stepGame(int x, int y)
{
    if(!playerTwo.getField(x,y).isShot)
    {
        playerTwo.getShot(x,y);
        bool foundShot = false;
        while(!foundShot)
        {
            int randX = rand() % areaSize;
            int randY = rand() % areaSize;
            if(!playerOne.getField(randX, randY).isShot)
            {
                playerOne.getShot(randX, randY);
                foundShot = true;
            }
        }
    }
    checkGame();
}

void Torpedomodel::checkGame()
{
    bool player1won = true;
    for(int i = 1; i <= _shipNum; ++i) // ellenőrzések végrehajtása
    {
        if (playerTwo.getShipByID(i).hitPoint && player1won)
        {
            player1won = false;
        }
    }
    bool player2won = true;
    for(int i = 1; i <= _shipNum; ++i) // ellenőrzések végrehajtása
    {
        if (playerOne.getShipByID(i).hitPoint && player2won)
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
