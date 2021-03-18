#include "baseplayer.h"

baseplayer::baseplayer(NewGameData newdata, QObject *parent) : QObject(parent)
{
    _shipInHandID = 0;
    _data = newdata;
    initTable();
    fillShips();
}

Area baseplayer::getField(Coordinate c) const
{
    return _gameTable[c.x][c.y];
}

Ship baseplayer::getShipByID(int ID) const
{
    return _ships[ID-1];
}

std::vector<Coordinate> baseplayer::getShipInHandCoords() const{
    std::vector<Coordinate> ret;
    for(size_t i = 0; i < _shipInHandNewCoords.size(); i++){
        ret.push_back(_shipInHandNewCoords[i]);
    }
    return ret;
}

void baseplayer::randomTable()
{
    resetTable();
    for (size_t i = 0; i < _ships.size(); i++)
    {
        bool notPlaced = true;
        while (notPlaced)
        {
            int startcolumn = rand() % _data.areaSize;
            int startrow = rand() % _data.areaSize;
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
            if(endrow > _data.areaSize - 1 || endcolumn > _data.areaSize - 1)
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
        _gameTable.push_back(tmpVec);
    }
}

void baseplayer::resetTable()
{
    for (int i = 0; i < _data.areaSize; i++)
    {
        for (int j = 0; j < _data.areaSize; j++)
        {
            _gameTable[i][j].isShot = false;
            _gameTable[i][j].shipID = 0;
        }
    }
}

void baseplayer::fillShips()
{
    int ID = 1;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < _data.shipNumForSizes[i]; j++)
            {
                Ship s;
                s.ID = ID;
                s.hitPoint = i+2;
                s.size = i+2;
                _ships.push_back(s);
                ID++;
            }
}

void baseplayer::resetShips()
{
    for(size_t i = 0; i < _ships.size(); i++)
    {
        _ships[i].hitPoint = _ships[i].size;
    }
}

void baseplayer::getShot(Coordinate c)
{
    _gameTable[c.x][c.y].isShot = true;
    if(_gameTable[c.x][c.y].shipID)
        _ships[_gameTable[c.x][c.y].shipID-1].hitPoint--;
}

void baseplayer::newField(NewGameData data)
{
    _gameTable.clear();
    _ships.clear();
    _data = data;
    initTable();
    fillShips();
    randomTable();
}

void baseplayer::rotate(Coordinate c)
{
    pickUp(c);
    if(_shipInHandID)
    {
        _shipInHandNewCoords.clear();
        // kiválasztott hajó elforgatása a koordináta körül
        for(size_t i = 0; i < _shipInHand.size(); i++)
        {
            _shipInHandNewCoords.push_back(Coordinate{_shipInHand[i].y-c.y+c.x, _shipInHand[i].x-c.x+c.y});
        }
    }
    putDownShip();
}

void baseplayer::pickUp(Coordinate c){
    _shipInHand.clear();
    _shipInHandNewCoords.clear();
    _shipInHandID = _gameTable[c.x][c.y].shipID;
    if(_shipInHandID){
        _previousCoord = c;
        //megkeresi és kiveszi a kiválasztott hajót
        for(int i = 0; i < _data.areaSize; i++)
        {
            for(int j = 0; j < _data.areaSize; j++)
            {
                if(_gameTable[i][j].shipID == _shipInHandID)
                {
                    _shipInHand.push_back(Coordinate{i,j});
                    _shipInHandNewCoords.push_back(Coordinate{i,j});
                    _gameTable[i][j].shipID = 0;
                }
            }
        }
    }
}

void baseplayer::moveShip(Coordinate c){
    for(size_t i = 0; i < _shipInHandNewCoords.size(); i++)
    {
        _shipInHandNewCoords[i].x = _shipInHandNewCoords[i].x + (c.x-_previousCoord.x);
        _shipInHandNewCoords[i].y = _shipInHandNewCoords[i].y + (c.y-_previousCoord.y);
    }
    _previousCoord = c;
}

void baseplayer::putDownShip(){
    if(_shipInHandID){
        // ha kilóg a hajó, akkor visszacsúsztatja a táblára
        int moveX = 0;
        if(_shipInHandNewCoords[0].x<0){
            moveX = _shipInHandNewCoords[0].x;
        }
        if(_shipInHandNewCoords[_shipInHandNewCoords.size()-1].x>=_data.areaSize){
            moveX = _shipInHandNewCoords[_shipInHandNewCoords.size()-1].x-(_data.areaSize-1);
        }
        int moveY = 0;
        if(_shipInHandNewCoords[0].y<0){
            moveY = _shipInHandNewCoords[0].y;
        }
        if(_shipInHandNewCoords[_shipInHandNewCoords.size()-1].y>=_data.areaSize){
            moveY = _shipInHandNewCoords[_shipInHandNewCoords.size()-1].y-(_data.areaSize-1);
        }
        for(size_t i = 0; i < _shipInHandNewCoords.size(); i++)
        {
            _shipInHandNewCoords[i].x = _shipInHandNewCoords[i].x-moveX;
            _shipInHandNewCoords[i].y = _shipInHandNewCoords[i].y-moveY;
        }

        // helykeresés ameddig olyat nem találunk ahol nem ütközik
        bool foundGoodPlace = false;
        // egyre messzebbi pontokban nézzük meg jó e a hely a hajónak
        for(int distance = 0; distance < _data.areaSize && !foundGoodPlace; distance++){
            // x tengelyen elmozdulás
            for(int i = -distance; i <= distance && !foundGoodPlace; i++){
                // y tengelyen elmozdulás
                for(int j = -distance; j <= distance && !foundGoodPlace; j++){
                    // ellenőrizzük, hogy nem lógunk-e ki a tábláról az új helyel
                    if(_shipInHandNewCoords[0].x+i >= 0 && _shipInHandNewCoords[0].y+j >= 0 &&
                        _shipInHandNewCoords[_shipInHandNewCoords.size()-1].x+i < _data.areaSize &&
                        _shipInHandNewCoords[_shipInHandNewCoords.size()-1].y+j < _data.areaSize)
                    {
                        // feltételezzük, hogy az új hely jó és ellenőrizzük
                        foundGoodPlace = true;
                        for(size_t k = 0; k < _shipInHandNewCoords.size() && foundGoodPlace; k++)
                        {
                            if(_gameTable[_shipInHandNewCoords[k].x+i][_shipInHandNewCoords[k].y+j].shipID != 0){
                                foundGoodPlace = false;
                            };
                        }
                        // ha találtunk helyet beállítjuk a koordinátákat
                        if (foundGoodPlace){
                            for(size_t k = 0; k < _shipInHandNewCoords.size() && foundGoodPlace; k++)
                            {
                                _shipInHandNewCoords[k].x = _shipInHandNewCoords[k].x+i;
                                _shipInHandNewCoords[k].y = _shipInHandNewCoords[k].y+j;
                            }
                        }
                    }
                }
            }
        }

        // hajó visszatétele a táblára
        if(foundGoodPlace){
            for(size_t i = 0; i < _shipInHandNewCoords.size(); i++)
            {
                _gameTable[_shipInHandNewCoords[i].x][_shipInHandNewCoords[i].y].shipID = _shipInHandID;
            }
        } else {
            for(size_t i = 0; i < _shipInHandNewCoords.size(); i++)
            {
                _gameTable[_shipInHand[i].x][_shipInHand[i].y].shipID = _shipInHandID;
            }
        }
        _shipInHandID = 0;
        _shipInHand.clear();
        _shipInHandNewCoords.clear();
    }
}
