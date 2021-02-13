#ifndef TORPEDOMODEL_H
#define TORPEDOMODEL_H
#include <QObject>
#include <QVector>
#include <QString>

class Torpedomodel : public QObject
{
    Q_OBJECT
public:
    int areaSize;
    struct Area {
        int shipID;
        bool isShot;
    };
    struct Ship {
        int size;
        int hitPoint;
        int ID;
    };
    Torpedomodel();
    virtual ~Torpedomodel();
    void newGame();
    void randomTable(std::vector<std::vector<Torpedomodel::Area>> &t);
    Area getField(int x, int y) const; // saját játékmező lekérdezése
    Area getEnemyField(int x, int y) const; // ellenséges játékmező lekérdezése
    void initTable(std::vector<std::vector<Torpedomodel::Area>> &t);
    void stepGame(int x, int y);

private:
    std::vector<std::vector<Area>> _gameTable; // saját játéktábla
    std::vector<std::vector<Area>> _enemyGameTable; // ellenfél játéktábla
    std::vector<Ship> _ships; // játéktábla
    int _shipNum;
};

#endif // TORPEDOMODEL_H

