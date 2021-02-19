#ifndef CPUPLAYER_H
#define CPUPLAYER_H
#include "baseplayer.h"

class cpuplayer : public baseplayer
{
public:
    cpuplayer(int areaSize, int shipNum);
    Coordinate makeShot() override;
    virtual void initTable() override;
    void initOneTable(std::vector<std::vector<Area>> &t);
    virtual void resetTable() override;
    void resetOneTable(std::vector<std::vector<Area>> &t);

protected:
    std::vector<std::vector<Area>> _enemyGameTable; // saját játéktábla
};

#endif // CPUPLAYER_H
