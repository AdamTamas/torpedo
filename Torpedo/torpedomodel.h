#ifndef TORPEDOMODEL_H
#define TORPEDOMODEL_H
#include <QObject>
#include <QVector>
#include <QString>
#include "baseplayer.h"

class Torpedomodel : public QObject
{
    Q_OBJECT
public:
    int areaSize = 8;
    Torpedomodel();
    ~Torpedomodel();
    void newGame();
    Area getField(int x, int y) const; // saját játékmező lekérdezése
    Area getEnemyField(int x, int y) const; // ellenséges játékmező lekérdezése
    Ship getShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    Ship getEnemyShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    void randomTable(std::vector<std::vector<Area>> &t);
    void initTable(std::vector<std::vector<Area>> &t);
    void resetTable(std::vector<std::vector<Area>> &t);
    void fillShips(std::vector<Ship> &t);
    void resetShips(std::vector<Ship> &t);
    void stepGame(int x, int y);

private:
    int _shipNum = 4;
    baseplayer playerOne = baseplayer(areaSize, _shipNum);
    baseplayer playerTwo = baseplayer(areaSize, _shipNum);
};

#endif // TORPEDOMODEL_H

