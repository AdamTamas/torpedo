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
    void prepareToOnlineGame(NewGameData data);
    void newGameData(NewGameData data);
    void connectToHost(QString hostname, quint16 port);
    playerBase* playerOne;
    playerBase* playerTwo;
    modelConnection cModel;
    bool online = false;

private slots:
    void connection_dataRecieved(NewGameData data); // online játék adatok érkezése
    void connection_stepRecieved(Coordinate c);
    void connection_shotResponseRecieved(int hit);
signals:
    void gameWon(int won); // játékos győzelmének eseménye
    void needNewGraphics(); // tábla újrarajzolása
    void needGraphicsUpdate(); // kijelző frissítése

private:
    void stepOffline(Coordinate c);
    void stepOnline(Coordinate c);
    int _shipNum = 4;
    tcpServer _server;
    bool _myTurn = false;
};

#endif // TORPEDOMODEL_H

