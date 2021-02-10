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
    Torpedomodel();
    virtual ~Torpedomodel();
    void newGame();
    Area getField(int x, int y) const; // játékmező lekérdezése

private:
    Area** _gameTable; // játéktábla
};

#endif // TORPEDOMODEL_H

