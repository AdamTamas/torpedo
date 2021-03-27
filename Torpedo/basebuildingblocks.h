#ifndef BASEBUILDINGBLOCKS_H
#define BASEBUILDINGBLOCKS_H

#include <QString>
#include <ctime>

struct Coordinate {
    int x;
    int y;

    bool operator==(const Coordinate &o) const {
        return x == o.x && y == o.y;
    }

    bool operator<(const Coordinate &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};

struct Area {
    int shipID;
    bool isShot;
};

struct Ship {
    int size;
    int hitPoint;
    int
    ID;
};

struct NewGameData {
    int areaSize;
    int shipNumForSizes[4];
    bool online;
};


struct messenge {
    QString sender;
    QString messenge;
    time_t sendTime;
};

#endif // BASEBUILDINGBLOCKS_H
