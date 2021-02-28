#ifndef TORPEDOMODEL_H
#define TORPEDOMODEL_H
#include <QObject>
#include "baseplayer.h"
#include "basebuildingblocks.h"

class Torpedomodel : public QObject
{
    Q_OBJECT
public:
    int areaSize = 8;
    Torpedomodel();
    ~Torpedomodel();
    void newGame();
    Area getField(Coordinate c) const; // saját játékmező lekérdezése
    Area getEnemyField(Coordinate c) const; // ellenséges játékmező lekérdezése
    Ship getShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    Ship getEnemyShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    void stepGame(Coordinate c);
    void checkGame();
    void newGameData(NewGameData data);
    baseplayer* playerOne;
    baseplayer* playerTwo;

signals:
    void gameWon(int won); // játékos győzelmének eseménye
    void needNewGraphics(); // játékos győzelmének eseménye

private:
    int _shipNum = 4;
};

#endif // TORPEDOMODEL_H

