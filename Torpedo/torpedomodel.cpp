#include "torpedomodel.h"
#include <stdlib.h>


Torpedomodel::Torpedomodel()
{
    areaSize = 8;
    initTable(_gameTable);
    initTable(_enemyGameTable);
    //saját hajók listája
    _shipNum = 4;
    for(int i = 0; i < _shipNum; i++)
    {
        Ship s;
        s.ID = i+1;
        s.hitPoint = i+2;
        s.size = i+2;
        _ships.push_back(s);
    }

}

Torpedomodel::~Torpedomodel()
{
}

void Torpedomodel::newGame()
{

    randomTable(_gameTable);
    randomTable(_enemyGameTable);
}

Torpedomodel::Area Torpedomodel::getField(int x, int y) const
{
    return _gameTable[x][y];
}

Torpedomodel::Area Torpedomodel::getEnemyField(int x, int y) const
{
    return _enemyGameTable[x][y];
}


Torpedomodel::Ship Torpedomodel::getShipByID(int ID)  const
{
    return _ships[ID-1];
}

void Torpedomodel::randomTable(std::vector<std::vector<Torpedomodel::Area>> &t)
{
    for (int i = 0; i < areaSize; i++)
    {
        for (int j = 0; j < areaSize; j++)
        {
            t[i][j].isShot = false;
            t[i][j].shipID = 0;
        }
    }

    for (size_t i = 0; i < _ships.size(); i++)
    {
        bool notPlaced = true;
        while (notPlaced)
        {

            int startcolumn = rand() % areaSize;
            int startrow = rand() % areaSize;
            int endrow = startrow;
            int endcolumn = startcolumn;
            int orientation = rand() % 2;
            bool canBePlaced = true;
            if (orientation == 0)
            {
                for (int j = 0; j < _ships[i].size-1; j++)
                {
                    endrow++;
                }
            }
            else
            {
                for (int j = 0; j < _ships[i].size-1; j++)
                {
                    endcolumn++;
                }
            }
            // ellenőrizzük, kilógunk-e a tábláról
            if(endrow > areaSize - 1 || endcolumn > areaSize - 1)
            {
                canBePlaced = false;
            }

            // ellenőrizzük, hogy foglalt-e egy hely
            if(canBePlaced)
                for(int row = startrow; row <= endrow; row++)
                    for(int col = startcolumn; col <= endcolumn; col++)
                        if(t[row][col].shipID != 0)
                            canBePlaced = false;

            // ha le lehet rakni, akkor elhelyezzük a hajót
            if(canBePlaced)
            {
                for(int row = startrow; row <= endrow; row++)
                {
                    for(int col = startcolumn; col <= endcolumn; col++)
                    {
                        t[row][col].shipID = _ships[i].ID;
                    }
                }
            notPlaced = false;
            }
        }
    }
}

void Torpedomodel::initTable(std::vector<std::vector<Torpedomodel::Area>> &t)
{
    for (int i = 0; i < areaSize; ++i)
    {
        std::vector<Area> tmpVec;
        for (int j = 0; j < areaSize; ++j)
        {
            Area a;
            a.shipID = 0;
            a.isShot = false;
            tmpVec.push_back(a);
        }
        t.push_back(tmpVec);
    }
}

void Torpedomodel::stepGame(int x, int y)
{
    if(!_enemyGameTable[x][y].isShot)
    {
        _enemyGameTable[x][y].isShot = true;
        bool foundShot = false;
        while(!foundShot)
        {
            int randX = rand() % areaSize;
            int randY = rand() % areaSize;
            if(!_gameTable[randX][randY].isShot)
            {
                _gameTable[randX][randY].isShot = true;
                if(_gameTable[randX][randY].shipID != 0)
                {
                    _ships[_gameTable[randX][randY].shipID-1].hitPoint--;
                }
                foundShot = true;
            }
        }
    }
}

