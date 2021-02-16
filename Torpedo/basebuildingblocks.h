#ifndef BASEBUILDINGBLOCKS_H
#define BASEBUILDINGBLOCKS_H

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

#endif // BASEBUILDINGBLOCKS_H
