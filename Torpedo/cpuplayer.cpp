#include "cpuplayer.h"

cpuplayer::cpuplayer(NewGameData newdata) : baseplayer(newdata)
{
    initTable();
    _lastShot.x = 0;
    _lastShot.y = 0;
}

Coordinate cpuplayer::makeShot()
{
    for (auto x : _priorityShots)
    {
        if(x.second && !_enemyGameTable[x.first.x][x.first.y].isShot)
        {
            _lastShot = x.first;
            _priorityShots[x.first] = false;
            _enemyGameTable[x.first.x][x.first.y].isShot = true;
            return x.first;
        }
    }

    bool foundShot = false;
    while(!foundShot)
    {
        int randX = rand() % _data.areaSize;
        //rácsos lövés
        int randY = ((rand() % _data.areaSize)/2)*2+randX%2;
        if(randY >= _data.areaSize)
            continue;
        if(!_enemyGameTable[randX][randY].isShot)
        {
            _lastShot.x = randX;
            _lastShot.y = randY;
            foundShot = true;
            _enemyGameTable[randX][randY].isShot = true;
        }
    }
    return _lastShot;
}


void cpuplayer::initTable()
{
    _priorityShots.clear();
    initOneTable(_gameTable);
    initOneTable(_enemyGameTable);
}

void cpuplayer::initOneTable(std::vector<std::vector<Area>> &t)
{
    t.clear();
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
    _priorityShots.clear();
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

void cpuplayer::shotResponse(bool hit)
{
    if(hit)
    {
        std::vector<Coordinate> tmpcoords; // ideiglenes koordináták a lehetséges találatoknak

        if(_lastShot.x != 0)
            tmpcoords.push_back(Coordinate{_lastShot.x-1, _lastShot.y});
        if(_lastShot.y != 0)
            tmpcoords.push_back(Coordinate{_lastShot.x, _lastShot.y-1});
        if(_lastShot.x != _data.areaSize-1)
            tmpcoords.push_back(Coordinate{_lastShot.x+1, _lastShot.y});
        if(_lastShot.y != _data.areaSize-1)
            tmpcoords.push_back(Coordinate{_lastShot.x, _lastShot.y+1});

        if (_priorityShots.find(Coordinate{_lastShot.x, _lastShot.y}) == _priorityShots.end())
        {
            std::pair<Coordinate, bool> p(Coordinate{_lastShot.x, _lastShot.y}, false);
            _priorityShots.insert(p);
        }

        for(size_t i = 0; i < tmpcoords.size();i++)
        {
            if (_priorityShots.find(tmpcoords[i]) == _priorityShots.end())
            {
                std::pair<Coordinate, bool> p(tmpcoords[i], true);
                _priorityShots.insert(p);
            }
        }
    }
}
