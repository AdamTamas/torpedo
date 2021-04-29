#include "playerOnline.h"

playerOnline::playerOnline(NewGameData newdata) : playerBase(newdata)
{
    _data = newdata;
    initTable();
    fillShips();
}

void playerOnline::shotResponse(int hit)
{
    qDebug() << "ShotResponse:" << shotCoord.x << " " << shotCoord.y <<" ID:" << hit;
    _gameTable[shotCoord.x][shotCoord.y].isShot = true;
    _gameTable[shotCoord.x][shotCoord.y].shipID = hit;
    if(hit)
        _ships[_gameTable[shotCoord.x][shotCoord.y].shipID-1].hitPoint--;
}

void playerOnline::getShot(Coordinate c)
{
    shotCoord = c;
}
