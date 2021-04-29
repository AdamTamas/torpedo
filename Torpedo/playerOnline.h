#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H
#include "playerBase.h"
#include <map>
#include <QTcpSocket>

class playerOnline : public playerBase
{
    Q_OBJECT
public:
    playerOnline(NewGameData newdata);
    virtual void getShot(Coordinate c) override;
    virtual void shotResponse(int hit) override;

private:
    Coordinate shotCoord;
};

#endif // ONLINEPLAYER_H
