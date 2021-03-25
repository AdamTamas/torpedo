#ifndef CPUPLAYER_H
#define CPUPLAYER_H
#include "playerBase.h"
#include <map>

class playerCPU : public playerBase
{
public:
    playerCPU(NewGameData newdata);
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
