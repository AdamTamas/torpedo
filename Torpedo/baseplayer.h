#ifndef BASEPLAYER_H
#define BASEPLAYER_H
#include "basebuildingblocks.h"
#include <QVector>

class baseplayer
{
public:
    baseplayer(int areaSize, int shipNum);
    Area getField(Coordinate c) const; // saját játékmező lekérdezése
    Ship getShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    void randomTable();
    virtual void initTable();
    virtual void resetTable();
    void fillShips();
    void resetShips();
    void getShot(Coordinate c);
    virtual void newField(NewGameData data);
    virtual Coordinate makeShot(){Coordinate a; a.x = 0; a.y = 0; return a;};
    virtual void shotResponse(bool){};

protected:
    std::vector<std::vector<Area>> _gameTable; // saját játéktábla
    std::vector<Ship> _ships; // saját hajók
    NewGameData _data;
    Coordinate _lastShot;
};

#endif // BASEPLAYER_H
