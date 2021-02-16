#ifndef BASEPLAYER_H
#define BASEPLAYER_H
#include "basebuildingblocks.h"
#include <QVector>

class baseplayer
{
public:
    baseplayer(int areaSize, int shipNum);
    Area getField(int x, int y) const; // saját játékmező lekérdezése
    Ship getShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    void randomTable();
    void initTable();
    void resetTable();
    void fillShips();
    void resetShips();
    void getShot(int x, int y);
    void newField(NewGameData data);

private:

    std::vector<std::vector<Area>> _gameTable; // saját játéktábla
    std::vector<Ship> _ships; // saját hajók
    NewGameData _data;
};

#endif // BASEPLAYER_H
