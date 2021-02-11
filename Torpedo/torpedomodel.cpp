#include "torpedomodel.h"
#include <stdlib.h>

Torpedomodel::Torpedomodel()
{    
    _gameTable = new Area*[areaSize];
    for (int i = 0; i < areaSize; ++i)
    {
        _gameTable[i] = new Area[areaSize];
    }

}

Torpedomodel::~Torpedomodel()
{
    delete[] _gameTable;
}

void Torpedomodel::newGame()
{
    //saját hajók listája
    int shipNum = 5;
    Ship ships[shipNum];
    for(int i = 2; i < shipNum; i++)
    {
        Ship s;
        s.ID = i-1;
        s.hitPoint = i;
        s.size = i;
        s.isDestroyed = false;
        ships[i-2] = s;
    }
    // üres tábla létrehozása
    for (int i = 0; i < areaSize; ++i)
        for (int j = 0; j < areaSize; ++j)
        { 
            Area a;
            a.shipID = 0;
            a.isShot = false;
            _gameTable[i][j] = a;
        }
    Torpedomodel::randomTable(_gameTable, ships, shipNum);
}
Torpedomodel::Area Torpedomodel::getField(int x, int y) const
{
    return _gameTable[x][y];
}

void Torpedomodel::randomTable(Area** _gameTable, Ship* ships, int shipNum)
{

    for (int i = 0; i < shipNum; i++)
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
                for (int j = 0; j < ships[i].size-1; j++)
                {
                    endrow++;
                }
            }
            else
            {
                for (int j = 0; j < ships[i].size-1; j++)
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
                for(int row = startrow; row <= endrow && row < areaSize; row++)
                    for(int col = startcolumn; col <= endcolumn && col < areaSize; col++)
                        if(_gameTable[row][col].shipID != 0)
                            canBePlaced = false;

            // ha le lehet rakni, akkor elhelyezzük a hajót
            if(canBePlaced)
            {
                for(int row = startrow; row <= endrow; row++)
                {
                    for(int col = startcolumn; col <= endcolumn; col++)
                    {
                        _gameTable[row][col].shipID = ships[i].ID;
                    }
                }
            notPlaced = false;
            }
        }
    }

}
