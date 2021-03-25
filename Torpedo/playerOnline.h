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
    ~playerOnline();
    virtual Coordinate makeShot() override;
    virtual void getShot(Coordinate c) override;
    virtual void shotResponse(bool hit) override;
    void connect();

public slots:

protected:
    Coordinate _lastShot;
    QTcpSocket *socket;
};

#endif // ONLINEPLAYER_H
