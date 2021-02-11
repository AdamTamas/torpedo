#ifndef TORPEDOMODEL_H
#define TORPEDOMODEL_H
#include <QObject>
#include <QVector>
#include <QString>

static int areaSize = 8;
class Torpedomodel : public QObject
{
    Q_OBJECT
public:
    struct Area {
        int shipID;
        bool isShot;
    };
    struct Ship {
        bool isDestroyed;
        int size;
        int hitPoint;
        int ID;
    };
    Torpedomodel();
    virtual ~Torpedomodel();
    void newGame();
    void randomTable(Area** _gameTable, Ship* ships, int shipNum);
    Area getField(int x, int y) const; // játékmező lekérdezése

private:
    Area** _gameTable; // játéktábla
};

#endif // TORPEDOMODEL_H

