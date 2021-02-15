#include "baseplayer.h"

baseplayer::baseplayer(int areaSize, int shipNum)
{
    _areaSize = areaSize;
    _shipNum = shipNum;
    initTable();
    fillShips();
}

Area baseplayer::getField(int x, int y) const
{
    return _gameTable[x][y];
}

Ship baseplayer::getShipByID(int ID) const
{
    return _ships[ID-1];
}

void baseplayer::randomTable()
{
    resetTable();
    for (int i = 0; i < _shipNum; i++)
    {
        bool notPlaced = true;
        while (notPlaced)
        {
            int startcolumn = rand() % _areaSize;
            int startrow = rand() % _areaSize;
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
            if(endrow > _areaSize - 1 || endcolumn > _areaSize - 1)
            {
                canBePlaced = false;
            }

            // ellenőrizzük, hogy foglalt-e egy hely
            if(canBePlaced)
                for(int row = startrow; row <= endrow; row++)
                    for(int col = startcolumn; col <= endcolumn; col++)
                        if(_gameTable[row][col].shipID != 0)
                            canBePlaced = false;

            // ha le lehet rakni, akkor elhelyezzük a hajót
            if(canBePlaced)
            {
                for(int row = startrow; row <= endrow; row++)
                {
                    for(int col = startcolumn; col <= endcolumn; col++)
                    {
                        _gameTable[row][col].shipID = _ships[i].ID;
                    }
                }
            notPlaced = false;
            }
        }
    }
}

void baseplayer::initTable()
{
    for (int i = 0; i < _areaSize; ++i)
    {
        std::vector<Area> tmpVec;
        for (int j = 0; j < _areaSize; ++j)
        {
            Area a;
            a.shipID = 0;
            a.isShot = false;
            tmpVec.push_back(a);
        }
        _gameTable.push_back(tmpVec);
    }
}

void baseplayer::resetTable()
{
    for (int i = 0; i < _areaSize; i++)
    {
        for (int j = 0; j < _areaSize; j++)
        {
            _gameTable[i][j].isShot = false;
            _gameTable[i][j].shipID = 0;
        }
    }
}

void baseplayer::fillShips()
{
    for(int i = 0; i < _shipNum; i++)
    {
        Ship s;
        s.ID = i+1;
        s.hitPoint = i+2;
        s.size = i+2;
        _ships.push_back(s);
    }
}

void baseplayer::resetShips()
{
    for(size_t i = 0; i < _ships.size(); i++)
    {
        _ships[i].hitPoint = i+2;
    }
}


void baseplayer::getShot(int x, int y)
{
    _gameTable[x][y].isShot = true;
    if(_gameTable[x][y].shipID)
        _ships[_gameTable[x][y].shipID-1].hitPoint--;
}
