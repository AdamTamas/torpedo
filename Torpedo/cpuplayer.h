#ifndef CPUPLAYER_H
#define CPUPLAYER_H
#include "baseplayer.h"
#include <map>

class cpuplayer : public baseplayer
{
public:
    cpuplayer(int areaSize, int shipNum);
    Coordinate makeShot() override;
    virtual void initTable() override;
    void initOneTable(std::vector<std::vector<Area>> &t);
    virtual void resetTable() override;
    void resetOneTable(std::vector<std::vector<Area>> &t);
    virtual void shotResponse(bool hit) override;

protected:
    std::vector<std::vector<Area>> _enemyGameTable; // saját játéktábla
    std::map<Coordinate, bool> _priorityShots;
    Coordinate _lastShot;
};

#endif // CPUPLAYER_H
