#include "cpuplayer.h"

cpuplayer::cpuplayer(int areaSize, int shipNum) : baseplayer(areaSize, shipNum)
{
    initTable(_enemyGameTable);
}

Coordinate cpuplayer::makeShot()
{
    bool foundShot = false;
    Coordinate c;
    while(!foundShot)
    {
        int randX = rand() % _data.areaSize;
        int randY = rand() % _data.areaSize;
        if(!_enemyGameTable[randX][randY].isShot)
        {
            c.x = randX;
            c.y = randY;
            foundShot = true;
            _enemyGameTable[randX][randY].isShot = true;
        }
    }
    return c;
}

void cpuplayer::resetTable(std::vector<std::vector<Area>> &t)
{
    resetOneTable(_gameTable);
    resetOneTable(_enemyGameTable);
}

void cpuplayer::resetOneTable(std::vector<std::vector<Area>> &t)
{
    for (int i = 0; i < _data.areaSize; i++)
    {
        for (int j = 0; j < _data.areaSize; j++)
        {
            t[i][j].isShot = false;
            t[i][j].shipID = 0;
        }
    }
}
