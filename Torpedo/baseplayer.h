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
    void rotate(Coordinate c);
    void pickUp(Coordinate c);
    void moveShip(Coordinate c);
    void putDownShip();
    NewGameData _data;

protected:
    std::vector<std::vector<Area>> _gameTable; // saját játéktábla
    std::vector<Ship> _ships; // saját hajók

    // potenciálisan kiemelhetők structba a lenti változók vagy akár külön fileba a mozgatások
    std::vector<Coordinate> _shipInHand;    // az ideiglenesen kézbentartott hajó eredeti helye
    std::vector<Coordinate> _shipInHandNewCoords;    // az ideiglenesen kézbentartott hajó új helye
    int _shipInHandID;    // az ideiglenesen kézbentartott hajó ID-je
};

#endif // BASEPLAYER_H
