#include "cpuplayer.h"

cpuplayer::cpuplayer(int areaSize, int shipNum) : baseplayer(areaSize, shipNum)
{
    initTable();
}

Coordinate cpuplayer::makeShot()
{
    bool foundShot = false;
    Coordinate c;
    while(!foundShot)
    {
        int randX = rand() % _data.areaSize;
        //rácsos lövés
        int randY = ((rand() % _data.areaSize)/2)*2+randX%2;
        if(randY > _data.areaSize)
            continue;
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


void cpuplayer::initTable()
{
    initOneTable(_gameTable);
    initOneTable(_enemyGameTable);
}

void cpuplayer::initOneTable(std::vector<std::vector<Area>> &t)
{
    for (int i = 0; i < _data.areaSize; ++i)
    {
        std::vector<Area> tmpVec;
        for (int j = 0; j < _data.areaSize; ++j)
        {
            Area a;
            a.shipID = 0;
            a.isShot = false;
            tmpVec.push_back(a);
        }
        t.push_back(tmpVec);
    }
}

void cpuplayer::resetTable()
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
