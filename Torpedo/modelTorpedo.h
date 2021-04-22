#ifndef TORPEDOMODEL_H
#define TORPEDOMODEL_H
#include <QObject>
#include "playerBase.h"
#include "basebuildingblocks.h"
#include "tcpServer.h"
#include "modelConnection.h"

class modelTorpedo : public QObject
{
    Q_OBJECT
public:
    int areaSize = 8;
    modelTorpedo();
    ~modelTorpedo();
    void newGame();
    Area getField(Coordinate c) const; // saját játékmező lekérdezése
    Area getEnemyField(Coordinate c) const; // ellenséges játékmező lekérdezése
    Ship getShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    Ship getEnemyShipByID(int ID) const; // saját hajó adatainak lekérése ID alapján
    void stepGame(Coordinate c);
    void checkGame();
    void newGameData(NewGameData data);
    void connectToHost(QString hostname, quint16 port);
    playerBase* playerOne;
    playerBase* playerTwo;
    modelConnection cModel;

private slots:
    void connection_dataRecieved(NewGameData data); // eseménykezelők a modell eseményeire

signals:
    void gameWon(int won); // játékos győzelmének eseménye
    void needNewGraphics(); // játékos győzelmének eseménye

private:
    int _shipNum = 4;
    tcpServer server;
};

#endif // TORPEDOMODEL_H

