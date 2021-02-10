#include "torpedomodel.h"


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
    for (int i = 0; i < areaSize; ++i)
        for (int j = 0; j < areaSize; ++j)
        { 
            Area a;
            a.shipID = rand() % 2; 
            a.isShot = false;
            _gameTable[i][j] = a; // a játékosok pozícióit töröljük
        }
}
Torpedomodel::Area Torpedomodel::getField(int x, int y) const
{
    return _gameTable[x][y];
}
